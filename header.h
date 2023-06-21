// header.h

#ifndef HEADER_H
#define HEADER_H

#define MAX_NAME_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_ORDER_SIZE 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    float price;
} Drink;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Drink* drinks;
    int numDrinks;
} Category;

extern Category* categories;
extern int numCategories;

void printMenu();
void displayMenu();
void addDrinkToOrder(Drink drink, Drink* order, int* numItems);
void removeDrinkFromOrder(int index, Drink* order, int* numItems);
void viewOrder(Drink* order, int numItems);
void sortOrder(Drink* order, int numItems);
void saveOrderToFileText(Drink* order, int numItems);
void saveOrderToFileBinary(Drink* order, int numItems);
void loadOrderFromFileText(Drink** order, int* numItems);
void loadOrderFromFileBinary(Drink** order, int* numItems);
//void searchForDrink(Drink* order, int numItems);

#endif
