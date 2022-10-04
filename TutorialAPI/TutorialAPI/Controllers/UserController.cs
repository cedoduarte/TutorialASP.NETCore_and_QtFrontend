using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace TutorialAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class UserController : ControllerBase
    {
        private readonly TutorialDbContext _context;

        public UserController(TutorialDbContext context)
        {
            _context = context;
        }

        [HttpGet("{id:int}")]
        public async Task<ActionResult<User>> Get([FromRoute] int id)
        {
            try
            {
                var user = await _context.Users!.FindAsync(id);
                if (user is not null)
                {
                    return Ok(user);
                }
                return NotFound();
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpGet]
        public async Task<ActionResult<IEnumerable<User>>> Get()
        {
            try
            {
                var users = await _context.Users!.ToListAsync();
                if (users is not null)
                {
                    return Ok(users);
                }
                return NotFound();
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpPost]
        public async Task<ActionResult<User>> Post([FromBody] User user)
        {
            try
            {
                if (user is null)
                {
                    return NotFound();
                }
                using var transaction = await _context.Database.BeginTransactionAsync();
                await _context.AddAsync(user);
                await _context.SaveChangesAsync();
                await transaction.CommitAsync();
                return Ok(user);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpPut("{id:int}")]
        public async Task<ActionResult<User>> Put([FromRoute] int id, [FromBody] User user)
        {
            try
            {
                if (id != user.Id)
                {
                    return NotFound();
                }
                using var transaction = await _context.Database.BeginTransactionAsync();
                _context.Entry(user).State = EntityState.Modified;
                await _context.SaveChangesAsync();
                await transaction.CommitAsync();
                return Ok(user);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpDelete("{id:int}")]
        public async Task<ActionResult<User>> Delete([FromRoute] int id)
        {
            try
            {
                using var transaction = await _context.Database.BeginTransactionAsync();
                var user = await _context.Users!.FindAsync(id);
                if (user is not null)
                {
                    _context.Remove(user);
                    await _context.SaveChangesAsync();
                    await transaction.CommitAsync();
                    return Ok(user);
                }
                return NotFound();
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }
    }
}
