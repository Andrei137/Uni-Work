using System.ComponentModel.DataAnnotations;

namespace ExamenDAW.Models
{
    public class Membership
    {
        // PK
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Titlul abonamentului este obligatoriu")]
        public string Titlu { get; set; }

        [Required(ErrorMessage = "Valoarea abonamentului este obligatorie")]
        [Range(1, int.MaxValue, ErrorMessage = "Valoarea abonamentului trebuie sa fie pozitiva")]
        public int Valoare { get; set; }

        [Required(ErrorMessage = "Data emiterii este obligatorie")]
        public DateTime DataEmitere { get; set; }

        [Required(ErrorMessage = "Data expirarii este obligatorie")]
        public DateTime DataExpirare { get; set; } = DateTime.Now.AddDays(1);

        [Required]
        // FK
        public int GymId { get; set; }

        // The membership belongs to a gym
        public virtual Gym? Gym { get; set; }
    }
}
