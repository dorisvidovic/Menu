#include "header.h"

static User users[MAX_USERS] = {
	{"admin", "admin123", ADMIN},
	{"moderator", "mod123", MODERATOR},
	{"guest", "guest123", GUEST}
};

static int numUsers = sizeof(users) / sizeof(User);

static Article articles[MAX_ARTICLES];
static int numArticles = 0;

void addUser(const char* username, const char* password, Authority authority) {
	if (numUsers >= MAX_USERS) {
		printf("Maximum number of users reached.\n");
		return;
	}

	User newUser;
	strcpy(newUser.username, username);
	strcpy(newUser.password, password);
	newUser.authority = authority;

	users[numUsers] = newUser;
	numUsers++;

	printf("User added successfully.\n");
}

User* loginUser(const char* username, const char* password) {
	for (int i = 0; i < numUsers; i++) {
		if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
			return &users[i];
		}
	}
	return NULL; // User not found or incorrect credentials 
}

void addArticle(const char* title, const char* content, User* user) {
	if (user->authority == GUEST) {
		printf("Guest users are not allowed to add articles.\n");
		return;
	}

	if (numArticles >= MAX_ARTICLES) {
		printf("Maximum number of articles reached.\n");
		return;
	}

	Article newArticle;
	strcpy(newArticle.title, title);
	strcpy(newArticle.content, content);

	articles[numArticles] = newArticle;
	numArticles++;

	printf("Article added successfully.\n");
}

void displayMenu(DrinkCategory menu[], int numDrinkCategories) {
	printf("Izaberite kategoriju pica:\n");
	for (int i = 0; i < numDrinkCategories; i++) {
		printf("%d. %s\n", i + 1, menu[i].name);
	}
	printf("0. Izlaz\n");
}

void displayCategory(DrinkCategory category) {
	printf("Kategorija: %s\n", category.name);
	printf("------------------------\n");
	for (int i = 0; i < category.numDrinks; i++) {
		Drink drink = category.drinks[i];
		printf("%d. %s - %.2f kn\n", i + 1, drink.name, drink.price);
	}
	printf("\n");
}

float getTotal(Drink* order, int orderSize) {
	float total = 0.0;
	for (int i = 0; i < orderSize; i++) {
		total += order[i].price;
	}
	return total;
}
