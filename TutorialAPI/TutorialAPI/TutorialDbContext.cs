using Microsoft.EntityFrameworkCore;
using System.Reflection;

namespace TutorialAPI
{
    public class TutorialDbContext : DbContext
    {
        public DbSet<User>? Users { get; set; }

        public TutorialDbContext(DbContextOptions options)
            : base(options)
        {
            // nothing to do here
        }

        protected override void OnConfiguring(DbContextOptionsBuilder builder)
        {
            if (!builder.IsConfigured)
            {
                builder.UseSqlServer("name=TutorialConnectionString").UseQueryTrackingBehavior(QueryTrackingBehavior.NoTracking);
            }
        }

        protected override void ConfigureConventions(ModelConfigurationBuilder builder)
        {
            builder.Properties<DateTime>().HaveColumnType("date");
        }

        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);
            builder.ApplyConfigurationsFromAssembly(Assembly.GetExecutingAssembly());

            foreach (var entityType in builder.Model.GetEntityTypes())
            {
                foreach (var property in entityType.GetProperties())
                {
                    if (property.ClrType == typeof(string) && property.Name.Contains("URL", StringComparison.CurrentCultureIgnoreCase))
                    {
                        property.SetIsUnicode(false);
                        property.SetMaxLength(500);
                    }
                }
            }
        }
    }
}
