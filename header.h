#ifndef HEADER_H
#define HEADER_H

// Structure to represent a drink
typedef struct {
	char name[50];
	char description[100];
	float price;
} Drink;

// Structure to represent a drink category
typedef struct {
	char name[50];
	Drink drinks[10]; // Assuming a maximum of 10 drinks per category
	int numDrinks;
} DrinkCategory;

// Function to display the main menu
void displayMenu(DrinkCategory menu[], int numCategories);

// Function to display the drinks in a category
void displayCategory(DrinkCategory category);

#endif
