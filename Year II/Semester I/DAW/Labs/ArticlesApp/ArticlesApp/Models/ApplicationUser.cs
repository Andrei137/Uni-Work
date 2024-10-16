using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.ComponentModel.DataAnnotations.Schema;

namespace ArticlesApp.Models
{
    // PASUL 1 - useri si roluri
    public class ApplicationUser : IdentityUser
    {
        // un user posteaza mai multe comentarii
        public virtual ICollection<Comment>? Comments { get; set; }

        // un user posteaza mai multe articole
        public virtual ICollection<Article>? Articles { get; set; }

        // un user are mai multe bookmark-uri
        public virtual ICollection<Bookmark>? Bookmarks { get; set; }

        public string? FirstName { get; set; }

        public string? LastName { get; set; }

        [NotMapped]
        public IEnumerable<SelectListItem>? AllRoles { get; set; }
    }
}
