#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

// Function to display the main menu
void displayMenu(DrinkCategory menu[], int numCategories) {
	printf("Welcome to Name of the Cafe!\n");
	printf("Menu:\n");

	for (int i = 0; i < numCategories; i++) {
		printf("%d. %s\n", i + 1, menu[i].name);
	}

	printf("Enter the number of your choice: ");
}

// Function to display the drinks in a category
void displayCategory(DrinkCategory category) {
	printf("%s Menu:\n", category.name);

	for (int i = 0; i < category.numDrinks; i++) {
		Drink drink = category.drinks[i];
		printf("%d. %s - %s ($%.2f)\n", i + 1, drink.name, drink.description, drink.price);
	}
}

int main() {
	// Define and initialize the drink categories
	DrinkCategory menu[] = {
		{"Hot Beverages",
			{
				{"Espresso", "Strong and concentrated coffee", 2.50},
				{"Cappuccino", "Espresso with steamed milk and foam", 3.50},
				// Add more hot beverages if needed
			},
			2 // Number of drinks in the category
		},
		{"Non-Alcoholic Drinks",
			{
				{"Cola", "Classic carbonated soft drink", 2.00},
				{"Lemonade", "Refreshing lemon-flavored drink", 3.00},
				// Add more non-alcoholic drinks if needed
			},
			2 // Number of drinks in the category
		},
		// Add more drink categories if needed
	};

	int numCategories = sizeof(menu) / sizeof(menu[0]);

	int choice;
	int categoryChoice;

	do {
		displayMenu(menu, numCategories);
		scanf("%d", &choice);

		if (choice >= 1 && choice <= numCategories) {
			categoryChoice = choice - 1;
			displayCategory(menu[categoryChoice]);
		}
		else {
			printf("Invalid choice. Please enter a number from 1 to %d.\n", numCategories);
		}

		printf("\n");
	} while (choice != 0);

	return 0;
}
