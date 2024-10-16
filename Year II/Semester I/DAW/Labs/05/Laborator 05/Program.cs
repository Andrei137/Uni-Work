using Laborator_05.Models;
using Microsoft.EntityFrameworkCore;
using System;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllersWithViews();

var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
builder.Services.AddDbContext<AppDbContext>(options => options.UseSqlServer(connectionString));

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
    pattern: "{controller=Articles}/{action=Index}/{id?}");

app.MapControllerRoute(
    name: "ArticlesShow",
    pattern: "Articles/Show/{id?}",
    defaults: new { controller = "Articles", action = "Show" });

app.MapControllerRoute(
    name: "ArticlesNew",
    pattern: "Articles/New",
    defaults: new { controller = "Articles", action = "New" });

app.MapControllerRoute(
    name: "ArticlesEdit",
    pattern: "Articles/Edit/{id?}",
    defaults: new { controller = "Articles", action = "Edit" });

app.MapControllerRoute(
    name: "ArticlesDelete",
    pattern: "Articles/Delete/{id?}",
    defaults: new { controller = "Articles", action = "Delete" });

app.MapControllerRoute(
    name: "CategoriesIndex",
    pattern: "Categories/Show/{id?}",
    defaults: new { controller = "Categories", action = "Show" });

app.MapControllerRoute(
    name: "CategoriesShow",
    pattern: "Categories/Show/{id?}",
    defaults: new { controller = "Categories", action = "Show" });

app.MapControllerRoute(
    name: "CategoriesNew",
    pattern: "Categories/New",
    defaults: new { controller = "Categories", action = "New" });

app.MapControllerRoute(
    name: "CategoriesEdit",
    pattern: "Categories/Edit/{id?}",
    defaults: new { controller = "Categories", action = "Edit" });

app.MapControllerRoute(
    name: "CategoriesDelete",
    pattern: "Categories/Delete/{id?}",
    defaults: new { controller = "Categories", action = "Delete" });

app.Run();
