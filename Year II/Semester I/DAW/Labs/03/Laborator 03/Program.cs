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

// Exercitiul 1
// 1
app.MapControllerRoute(
    name: "concatenare",
    pattern: "concatenare/{str1}/{str2}",
    defaults: new { controller = "Examples", action = "Concatenare" });

// 2
app.MapControllerRoute(
    name: "produs",
    pattern: "produs/{nr1}/{nr2?}",
    defaults: new { controller = "Examples", action = "Produs" });

// 3
app.MapControllerRoute(
    name: "operatie",
    pattern: "operatie/{nr1}/{nr2}/{str}",
    defaults: new { controller = "Examples", action = "Operatie" });

// Exercitiul 2
app.MapControllerRoute(
    name: "operatie",
    pattern: "operatie/{nr1}/{nr2}/{str}",
    defaults: new { controller = "Examples", action = "Operatie" });

app.MapControllerRoute(
    name: "StudentsAll",
    pattern: "students/all",
    defaults: new { controller = "Students", action = "Index" });

app.MapControllerRoute(
    name: "StudentShow",
    pattern: "students/{id?}/show",
    defaults: new { controller = "Students", action = "Show" });

app.MapControllerRoute(
    name: "StudentCreate",
    pattern: "students/new",
    defaults: new { controller = "Students", action = "Create" });

app.MapControllerRoute(
    name: "StudentEdit",
    pattern: "students/{id?}/edit",
    defaults: new { controller = "Students", action = "Edit" });

app.MapControllerRoute(
    name: "StudentDelete",
    pattern: "students/{id?}/delete",
    defaults: new { controller = "Students", action = "Delete" });

// Exercitiul 3
app.MapControllerRoute(
    name: "NrTelefon",
    pattern: "search/telefon/{telef:regex(^[0][0-9]{{9}})?}",
    defaults: new { controller = "Search", action = "NumarTelefon" });

// ruta default
app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
