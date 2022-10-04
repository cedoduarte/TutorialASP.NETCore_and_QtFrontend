using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace TutorialAPI.Migrations
{
    public partial class NewMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Users",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(type: "nvarchar(128)", maxLength: 128, nullable: false, defaultValue: "No name"),
                    Email = table.Column<string>(type: "nvarchar(128)", maxLength: 128, nullable: false, defaultValue: "No email"),
                    Age = table.Column<int>(type: "int", nullable: false, defaultValue: 0),
                    Salary = table.Column<double>(type: "float", nullable: false, defaultValue: 0.0)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Users", x => x.Id);
                });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Users");
        }
    }
}
