using System.ComponentModel.DataAnnotations;

namespace ExamenDAW.Models
{
    public class Gym
    {
        // PK
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Numele salii este obligatoriu")]
        public string Nume { get; set; }

        // The gym has several memberships
        public virtual ICollection<Membership>? Memberships { get; set; }
    }
}
