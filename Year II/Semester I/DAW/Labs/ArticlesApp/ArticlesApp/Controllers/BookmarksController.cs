using ArticlesApp.Data;
using ArticlesApp.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace ArticlesApp.Controllers
{
    [Authorize]
    public class BookmarksController : Controller
    {
        private readonly ApplicationDbContext db;

        private readonly UserManager<ApplicationUser> _userManager;

        private readonly RoleManager<IdentityRole> _roleManager;

        public BookmarksController
            (
            ApplicationDbContext context,
            UserManager<ApplicationUser> userManager,
            RoleManager<IdentityRole> roleManager
            )
        {
            db = context;

            _userManager = userManager;

            _roleManager = roleManager;
        }


        // toti utilizatorii pot vedea Bookmark-urile existente in platforma
        // fiecare utilizator vede bookmark-urile pe care le-a creat
        // HttpGet - implicit
        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Index()
        {
            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
                ViewBag.Alert = TempData["messageType"];
            }

            SetAccessRights();

            if (User.IsInRole("User") || User.IsInRole("Editor"))
            {
                var bookmarks = from bookmark in db.Bookmarks.Include("User")
                                .Where(b => b.UserId == _userManager.GetUserId(User))
                                select bookmark;

                ViewBag.Bookmarks = bookmarks;

                return View();
            }
            else 
            if(User.IsInRole("Admin"))
            {
                var bookmarks = from bookmark in db.Bookmarks.Include("User")
                                select bookmark;

                ViewBag.Bookmarks = bookmarks;

                return View();
            }

            else
            {
                TempData["message"] = "Nu aveti drepturi asupra colectiei";
                TempData["messageType"] = "alert-danger";
                return RedirectToAction("Index", "Articles");
            }
            
        }

        // Afisarea tuturor articolelor pe care utilizatorul le-a salvat in 
        // bookmark-ul sau 
        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Show(int id)
        {
            SetAccessRights();

            if (User.IsInRole("User") || User.IsInRole("Editor"))
            {
                var bookmarks = db.Bookmarks
                                  .Include("ArticleBookmarks.Article.Category")
                                  .Include("ArticleBookmarks.Article.User")
                                  .Include("User")
                                  .Where(b => b.Id == id)
                                  .Where(b => b.UserId == _userManager.GetUserId(User))
                                  .FirstOrDefault();
                
                if(bookmarks == null)
                {
                    TempData["message"] = "Nu aveti drepturi";
                    TempData["messageType"] = "alert-danger";
                    return RedirectToAction("Index", "Articles");
                }

                return View(bookmarks);
            }

            else 
            if (User.IsInRole("Admin"))
            {
                var bookmarks = db.Bookmarks
                                  .Include("ArticleBookmarks.Article.Category")
                                  .Include("ArticleBookmarks.Article.User")
                                  .Include("User")
                                  .Where(b => b.Id == id)
                                  .FirstOrDefault();


                if (bookmarks == null)
                {
                    TempData["message"] = "Resursa cautata nu poate fi gasita";
                    TempData["messageType"] = "alert-danger";
                    return RedirectToAction("Index", "Articles");
                }


                return View(bookmarks);
            }

            else
            {
                TempData["message"] = "Nu aveti drepturi";
                TempData["messageType"] = "alert-danger";
                return RedirectToAction("Index", "Articles");
            }  
        }


        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult New()
        {
            return View();
        }

        [HttpPost]
        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult New(Bookmark bm)
        {
            bm.UserId = _userManager.GetUserId(User);

            if (ModelState.IsValid)
            {
                db.Bookmarks.Add(bm);
                db.SaveChanges();
                TempData["message"] = "Colectia a fost adaugata";
                TempData["messageType"] = "alert-success";
                return RedirectToAction("Index");
            }

            else
            {
                return View(bm);
            }
        }

        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Edit(int id)
        {
            var bookmark = db.Bookmarks.Find(id);
            if (bookmark.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                return View(bookmark);
            }
            else 
            {
                TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unei colectii care nu va apartine";
                TempData["messageType"] = "alert-danger";
                return RedirectToAction("Index");
            }
            return View();
        }

        [Authorize(Roles = "User,Editor,Admin")]
        [HttpPost]
        public IActionResult Edit(int id, Bookmark requestBookmark)
        {
            Bookmark bookmark = db.Bookmarks.Find(id);
            if (ModelState.IsValid)
            {
                if (bookmark.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
                {
                    bookmark.Name = requestBookmark.Name;
                    db.SaveChanges();
                    TempData["message"] = "Colectia a fost modificata";
                    TempData["messageType"] = "alert-success";
                    return RedirectToAction("Index");
                }
                else
                {
                    TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unei colectii care nu va apartine";
                    TempData["messageType"] = "alert-danger";
                    return RedirectToAction("Index");
                }
            }
            else
            {
                ViewBag.Message = "Nu s-a putut modifica colectia!";
                ViewBag.Alert = "alert-danger";
                return View(requestBookmark);
            }
        }

        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Delete(int id)
        {
            Bookmark bookmark = db.Bookmarks.Find(id);

            if (bookmark.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                db.Bookmarks.Remove(bookmark);
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

        // Conditiile de afisare a butoanelor de editare si stergere
        private void SetAccessRights()
        {
            ViewBag.AfisareButoane = false;

            if (User.IsInRole("Editor") || User.IsInRole("User"))
            {
                ViewBag.AfisareButoane = true;
            }

            ViewBag.EsteAdmin = User.IsInRole("Admin");

            ViewBag.UserCurent = _userManager.GetUserId(User);
        }
    }
}
