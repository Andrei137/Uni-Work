using ArticlesApp.Data;
using ArticlesApp.Models;
using Ganss.Xss;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Scaffolding.Metadata;

namespace ArticlesApp.Controllers
{
    [Authorize]
    public class ArticlesController : Controller
    {
        private readonly ApplicationDbContext db;
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly RoleManager<IdentityRole> _roleManager;

        public ArticlesController(ApplicationDbContext context, UserManager<ApplicationUser> userManager,
                                  RoleManager<IdentityRole> roleManager)
        {
            db = context;
            _userManager = userManager;
            _roleManager = roleManager;
        }

        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Index()
        {
            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
                ViewBag.Alert = TempData["messageType"];
            }

            /*
            var articles = from art in db.Articles.Include("Category")
                           orderby art.Date descending
                           select art;
            SAU
            */

            var articles = db.Articles.Include("Category")
                                      .Include("User")
                                      .OrderBy(a => a.Date);
            var search = "";
            if (Convert.ToString(HttpContext.Request.Query["search"]) != null)
            {
                // eliminam spatiile libere
                search = Convert.ToString(HttpContext.Request.Query["search"]).Trim();

                // Cautare in articol (Title si Content)
                List<int> articleIds = db.Articles.Where(at => at.Title.Contains(search) || at.Content.Contains(search))
                                                  .Select(a => a.Id)
                                                  .ToList();

                // Cautare in comentarii (Content)
                List<int> articleIdsOfCommentsWithSearchString = db.Comments.Where(c => c.Content.Contains(search))
                                                                            .Select(c => (int)c.ArticleId)
                                                                            .ToList();

                // Se formeaza o singura lista formata din toate id-urile selectate anterior
                List<int> mergedIds = articleIds.Union(articleIdsOfCommentsWithSearchString).ToList();

                // Lista articolelor care contin cuvantul cautat
                // fie in articol -> Title si Content
                // fie in comentarii -> Content
                articles = db.Articles.Where(article => mergedIds.Contains(article.Id))
                                      .Include("Category")
                                      .Include("User")
                                      .OrderBy(a => a.Date);
            }
            ViewBag.SearchString = search;

            int _perPage = 3;
            int _totalItems = articles.Count();
            var currentPage = Convert.ToInt32(HttpContext.Request.Query["page"]);
            var offset = 0;

            if (!currentPage.Equals(0))
            {
                offset = (currentPage - 1) * _perPage;
            }

            var paginatedArticles = articles.Skip(offset).Take(_perPage);

            ViewBag.lastPage = Math.Ceiling((float)_totalItems / (float)_perPage);
            ViewBag.Articles = paginatedArticles;

            if (search != "")
            {
                ViewBag.PaginationBaseUrl = "/Articles/Index/?search=" + search + "&page";
            }
            else
            {
                ViewBag.PaginationBaseUrl = "/Articles/Index/?page";
            }

            return View();
        }

        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Show(int id)
        {
            Article article = db.Articles.Include("Category")
                                         .Include("User")
                                         .Include("Comments")
                                         .Include("Comments.User")
                                .Where(art => art.Id == id)
                                .First();

            ViewBag.UserBookmarks = db.Bookmarks
                                      .Where(b => b.UserId == _userManager.GetUserId(User))
                                      .ToList();
            SetAccessRights();
            return View(article);
        }

        [Authorize(Roles = "User,Editor,Admin")]
        [HttpPost]
        public IActionResult Show([FromForm] Comment comment)
        {
            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
                ViewBag.Alert = TempData["messageType"];
            }

            comment.Date = DateTime.Now;
            comment.UserId = _userManager.GetUserId(User);

            if (ModelState.IsValid)
            {
                db.Comments.Add(comment);
                db.SaveChanges();
                return Redirect("/Articles/Show/" + comment.ArticleId);
            }
            else
            {
                Article art = db.Articles.Include("Category")
                                         .Include("User")
                                         .Include("Comments")
                                         .Include("Comments.User")
                                         .Where(art => art.Id == comment.ArticleId)
                                         .First();

                ViewBag.UserBookmarks = db.Bookmarks
                                      .Where(b => b.UserId == _userManager.GetUserId(User))
                                      .ToList();

                SetAccessRights();
                return View(art);
            }
        }

        [HttpPost]
        public IActionResult AddBookmark([FromForm] ArticleBookmark articleBookmark)
        {
            // Daca modelul este valid
            if (ModelState.IsValid)
            {
                // Verificam daca avem deja articolul in colectie
                if (db.ArticleBookmarks
                    .Where(ab => ab.ArticleId == articleBookmark.ArticleId)
                    .Where(ab => ab.BookmarkId == articleBookmark.BookmarkId)
                    .Count() > 0)
                {
                    TempData["message"] = "Acest articol este deja adaugat in colectie";
                    TempData["messageType"] = "alert-danger";
                }
                else
                {
                    // Adaugam asocierea intre articol si bookmark 
                    db.ArticleBookmarks.Add(articleBookmark);
                    // Salvam modificarile
                    db.SaveChanges();

                    // Adaugam un mesaj de succes
                    TempData["message"] = "Articolul a fost adaugat in colectia selectata";
                    TempData["messageType"] = "alert-success";
                }

            }
            else
            {
                TempData["message"] = "Nu s-a putut adauga articolul in colectie";
                TempData["messageType"] = "alert-danger";
            }

            // Ne intoarcem la pagina articolului
            return Redirect("/Articles/Show/" + articleBookmark.ArticleId);
        }

        // GET 
        // Afisarea formularului prin care se adauga un articol in baza de date
        [Authorize(Roles = "Editor,Admin")]
        public IActionResult New()
        {
            Article article = new Article();
            article.Categ = GetAllCategories();
            return View(article);
        }

        [Authorize(Roles = "Editor,Admin")]
        [HttpPost]
        public IActionResult New(Article article)
        {
            var sanitizer = new HtmlSanitizer();

            article.Date = DateTime.Now;
            article.UserId = _userManager.GetUserId(User);

            if (ModelState.IsValid)
            {
                article.Content = sanitizer.Sanitize(article.Content);

                db.Articles.Add(article);
                db.SaveChanges();
                TempData["message"] = "Articolul a fost adaugat";
                TempData["messageType"] = "alert-success";
                return RedirectToAction("Index");
            }
            else
            {
                ViewBag.Message = "Nu s-a putut adauga articolul!";
                ViewBag.Alert = "alert-danger";
                article.Categ = GetAllCategories();
                return View(article);
            }
        }

        [Authorize(Roles = "Editor,Admin")]
        public IActionResult Edit(int id)
        {
            Article article = db.Articles.Include("Category")
                                         .Where(art => art.Id == id)
                                         .First();
            article.Categ = GetAllCategories();
            
            if (article.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                return View(article);
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui articol care nu va apartine";
                TempData["messageType"] = "alert-danger";
                return RedirectToAction("Index");
            }
        }

        [Authorize(Roles = "Editor,Admin")]
        [HttpPost]
        public IActionResult Edit(int id, Article requestArticle)
        {
            var sanitizer = new HtmlSanitizer();

            Article article = db.Articles.Find(id);
            if (ModelState.IsValid)
            {
                if (article.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
                {
                    article.Title = requestArticle.Title;
                    requestArticle.Content = sanitizer.Sanitize(requestArticle.Content);
                    article.Content = requestArticle.Content;
                    article.CategoryId = requestArticle.CategoryId;
                    db.SaveChanges();
                    TempData["message"] = "Articolul a fost modificat";
                    TempData["messageType"] = "alert-success";
                    return RedirectToAction("Index");
                }
                else
                {
                    TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui articol care nu va apartine";
                    TempData["messageType"] = "alert-danger";
                    return RedirectToAction("Index");
                }
            }
            else
            {
                ViewBag.Message = "Nu s-a putut modifica articolul!";
                ViewBag.Alert = "alert-danger";
                requestArticle.Categ = GetAllCategories();
                return View(requestArticle);
            }
        }

        [Authorize(Roles = "Editor,Admin")]
        public IActionResult Delete(int id)
        {
            Article article = db.Articles.Include("Comments")
                                .Where(art => art.Id == id)
                                .First();

            if (article.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                db.Articles.Remove(article);
                db.SaveChanges();
                TempData["message"] = "Articolul a fost sters";
                TempData["messageType"] = "alert-success";
                return RedirectToAction("Index");
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui articol care nu va apartine";
                TempData["messageType"] = "alert-danger";
                return RedirectToAction("Index");
            }
        }

        // Conditii de afisare a butoanelor de editare si stergere
        private void SetAccessRights()
        {
            ViewBag.AfisareButoane = false;

            if (User.IsInRole("Editor"))
            {
                ViewBag.AfisareButoane = true;
            }

            ViewBag.EsteAdmin = User.IsInRole("Admin");

            ViewBag.UserCurent = _userManager.GetUserId(User);
        }

        public IEnumerable<SelectListItem> GetAllCategories()
        {
            // generam o lista de tipul SelectListItem fara elemente
            var selectList = new List<SelectListItem>();

            // extragem toate categoriile din baza de date
            var categories = from cat in db.Categories
                             select cat;

            // iteram prin categorii
            foreach (var category in categories)
            {
                // adaugam in lista elementele necesare pentru dropdown
                // id-ul categoriei si denumirea acesteia
                selectList.Add(new SelectListItem
                {
                    Value = category.Id.ToString(),
                    Text = category.CategoryName.ToString()
                });
            }
            /* Sau se poate implementa astfel:
            *
            foreach (var category in categories)
            {
                var listItem = new SelectListItem();
                listItem.Value = category.Id.ToString();
                listItem.Text = category.CategoryName.ToString();
                selectList.Add(listItem);
            }
            */
            // returnam lista de categorii
            return selectList;
        }

    }
}
