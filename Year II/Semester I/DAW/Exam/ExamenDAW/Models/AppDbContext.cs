using Microsoft.EntityFrameworkCore;

namespace ExamenDAW.Models
{
    public class AppDbContext : DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options)
        {
        }

        public DbSet<Membership> Memberships { get; set; }
        public DbSet<Gym> Gyms { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            modelBuilder.Entity<Membership>()
                        .HasOne(m => m.Gym)
                        .WithMany(m => m.Memberships)
                        .HasForeignKey(m => m.GymId);
        }
    }
}
