#include "header.h"

// Function to display the drinks in a category
void displayCategory(DrinkCategory category) {
    int drinkCount = 0;

    printf("%s Menu:\n", category.name);

    for (int i = 0; i < category.numDrinks; i++) {
        Drink drink = category.drinks[i];
        printf("%d. %s - %s ($%.2f)\n", i + 1, drink.name, drink.description, drink.price);
        drinkCount++;
    }

    printf("Total drinks in category: %d\n\n", drinkCount);
}


// Function to display the main menu
void displayMenu(DrinkCategory menu[], int numDrinkCategories) {
    printf("Welcome to Name of the Cafe!\n");
    printf("Menu:\n");

    for (int i = 0; i < numDrinkCategories; i++) {
        printf("%d. %s\n", i + 1, menu[i].name);
    }

    printf("Enter the number of your choice (0 to exit): ");
}

// Function to calculate the total cost of the order
float getTotal(Drink order[], int orderSize) {
    float total = 0;
    for (int i = 0; i < orderSize; i++) {
        total += order[i].price;
    }
    return total;
}
