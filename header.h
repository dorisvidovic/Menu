#pragma once

typedef struct {
    char name[50];
    char description[100];
    float price;
} Drink;

typedef struct {
    char name[50];
    Drink drinks[10];
    int numDrinks;
} DrinkCategory;

void displayMenu(DrinkCategory menu[], int numDrinkCategories);
void displayCategory(DrinkCategory category);
float getTotal(Drink order[], int orderSize);
