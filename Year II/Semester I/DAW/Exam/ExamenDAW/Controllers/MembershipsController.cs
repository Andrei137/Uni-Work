using Microsoft.AspNetCore.Mvc;
using ExamenDAW.Models;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;

namespace ExamenDAW.Controllers
{
    public class MembershipsController : Controller
    {
        private readonly AppDbContext db;
        public MembershipsController(AppDbContext context)
        {
            db = context;
        }

        // [ActionName("afisareAbonamente")]
        public IActionResult Index()
        {
            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
                ViewBag.Alert   = TempData["alert"];
            }

            var memberships = db.Memberships.Include("Gym");

            ViewBag.Memberships = memberships;
            ViewBag.Count       = memberships.Count();

            return View();
        }

        public IActionResult Show(int id)
        {
            Membership membership = db.Memberships.Include("Gym")
                                                  .Where(m => m.Id == id)
                                                  .First();

            return View(membership);

        }

        // Get
        public IActionResult New()
        {
            Membership membership = new Membership();

            ViewBag.Gyms = GetAllGyms(null);

            return View(membership);
        }

        [HttpPost]
        public IActionResult New(Membership membership)
        {
            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
                ViewBag.Alert   = TempData["alert"];
            }

            if (ModelState.IsValid) // Add the membership to the database
            {
                db.Memberships.Add(membership);
                db.SaveChanges();

                TempData["message"] = "Abonamentul a fost adaugat cu succes!";
                TempData["alert"]   = "alert-success";

                return RedirectToAction("Index");
            }
            else // Invalid model state
            {
                ViewBag.Message = "Abonamentul nu a putut fi adaugat!";
                ViewBag.Alert   = "alert-danger";

                return View(membership);
            }
        }

        // Get
        public IActionResult Edit(int id)
        {
            Membership membership = db.Memberships.Find(id);

            ViewBag.Gyms = GetAllGyms(membership);

            return View(membership);
        }

        [HttpPost]
        public IActionResult Edit(int id, Membership requestMembership)
        {
            Membership membership = db.Memberships.Find(id);

            if (ModelState.IsValid) // Add the membership to the database
            {
                membership.Titlu        = requestMembership.Titlu;
                membership.Valoare      = requestMembership.Valoare;
                membership.DataEmitere  = requestMembership.DataEmitere;
                membership.DataExpirare = requestMembership.DataExpirare;
                membership.GymId        = requestMembership.GymId;

                db.SaveChanges();

                TempData["message"] = "Abonamentul a fost modificat cu succes!";
                TempData["alert"]   = "alert-success";

                return RedirectToAction("Index");
            }
            else // Invalid model state
            {
                ViewBag.Message = "Abonamentul nu a putut fi modificat!";
                ViewBag.Alert   = "alert-danger";

                return View(membership);
            }
        }

        public IActionResult Delete(int id)
        {
            Membership membership = db.Memberships.Find(id);
            db.Memberships.Remove(membership);
            db.SaveChanges();

            TempData["message"] = "Abonamentul a fost sters cu succes!";
            TempData["alert"]   = "alert-success";

            return RedirectToAction("Index");
        }

        // Get
        public IActionResult Search()
        {
            var memberships = from membership in db.Memberships
                              select membership;

            // var search = Convert.ToString(HttpContext.Request.Query["search"]).Trim();
            // var date1 = Prima data din search
            // var date2 = A doua data din search
            // memberships = memberships.Where(m => m.DataExpirare >= date1 && m.DataExpirare <= date2)

            return View();
        }

        [NonAction]
        private IEnumerable<SelectListItem> GetAllGyms(Membership? membership)
        {
            var selectList = new List<SelectListItem>();

            foreach (var gym in db.Gyms.ToList())
            {
                if (membership == null || membership.GymId != gym.Id)
                {
                    selectList.Add(new SelectListItem
                    {
                        Value = gym.Id.ToString(),
                        Text = gym.Nume
                    });
                }
            }

            return selectList;
        }
    }
}
