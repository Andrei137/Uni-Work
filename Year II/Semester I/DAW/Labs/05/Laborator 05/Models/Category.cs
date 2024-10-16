using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations;

namespace Laborator_05.Models
{
    public class Category
    {
        [Key]
        public int Id { get; set; }
        public string CategoryName { get; set; }
    }
}
