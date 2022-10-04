using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace TutorialAPI
{
    public class UserConfig : IEntityTypeConfiguration<User>
    {
        public void Configure(EntityTypeBuilder<User> builder)
        {
            builder.HasKey(x => x.Id);
            builder.Property(x => x.Name)
                   .IsRequired(true)
                   .HasMaxLength(128)
                   .HasDefaultValue("No name");
            builder.Property(x => x.Email)
                   .IsRequired(true)
                   .HasMaxLength(128)
                   .HasDefaultValue("No email");
            builder.Property(x => x.Age)
                   .IsRequired(true)
                   .HasDefaultValue(0);
            builder.Property(x => x.Salary)
                   .IsRequired(true)
                   .HasDefaultValue(0.0);
        }
    }
}
