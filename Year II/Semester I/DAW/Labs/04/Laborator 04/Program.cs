var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllersWithViews();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Articles}/{action=listare}/{id?}");

app.MapControllerRoute(
    name: "ArticleShow",
    pattern: "Articles/Show/{id?}",
    defaults: new { controller = "Articles", action = "Show" });

app.MapControllerRoute(
    name: "ArticleNew",
    pattern: "Articles/New",
    defaults: new { controller = "Articles", action = "New" });

app.MapControllerRoute(
    name: "ArticleEdit",
    pattern: "Articles/Edit/{id?}",
    defaults: new { controller = "Articles", action = "Edit" });

app.MapControllerRoute(
    name: "ArticleDelete",
    pattern: "Articles/Delete/{id?}",
    defaults: new { controller = "Articles", action = "Delete" });

app.Run();
