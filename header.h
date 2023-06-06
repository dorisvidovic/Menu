#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_ARTICLES 100
#define MAX_DRINKS 10
#define MAX_DRINK_CATEGORIES 10


typedef enum {
	ADMIN,
	MODERATOR,
	GUEST
} Authority;

typedef struct {
	char name[50];
	char description[100];
	float price;
} Drink;

typedef struct {
	char name[50];
	Drink drinks[MAX_DRINKS];
	int numDrinks;
} DrinkCategory;

// Typedef for DrinkCategory structure
typedef DrinkCategory Category;

extern Category menu[MAX_DRINK_CATEGORIES];
extern int numDrinkCategories;

typedef struct {
	char username[50];
	char password[50];
	Authority authority;
} User;

extern User users[MAX_USERS];
extern int numUsers;

typedef struct {
	char title[100];
	char content[500];
} Article;

extern Article articles[MAX_ARTICLES];
extern int numArticles;

void displayMenu(Category* menu, int numDrinkCategories);
void displayCategory(Category category);
float getTotal(Drink* order, int orderSize);

void addUser(const char* username, const char* password, Authority authority);
User* loginUser(const char* username, const char* password);
void addArticle(const char* title, const char* content, User* user);

#endif
