using Microsoft.AspNetCore.Mvc.Rendering;
using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using static Humanizer.On;

namespace ArticlesApp.Models
{
    public class Article
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Titlul este obligatoriu")]
        [MinLength(5, ErrorMessage = "Titlul trebuie sa aiba minim 5 caractere")]
        [StringLength(10, ErrorMessage = "Titlul nu poate avea mai mult de 10 de caractere")]
        public string Title { get; set; }

        [Required(ErrorMessage = "Continutul articolului este obligatoriu")]
        public string Content { get; set; }

        public DateTime Date { get; set; }

        // un articol se afla intr-o categorie - FK
        [Required(ErrorMessage = "Categoria este obligatorie")]
        public int CategoryId { get; set; }

        // un articol este postat de un utilizator - FK
        public string? UserId { get; set; }

        // PASUL 6 - useri si roluri
        public virtual ApplicationUser? User { get; set; }

        public virtual Category? Category { get; set; }

        public virtual ICollection<Comment>? Comments { get; set; }

        [NotMapped]
        public IEnumerable<SelectListItem>? Categ { get; set; }

        public virtual ICollection<ArticleBookmark>? ArticleBookmarks { get; set; }

    }
}
