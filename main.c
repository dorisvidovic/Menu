// main.c
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    int choice;
    int numItems = 0;
    Drink* order = malloc(MAX_ORDER_SIZE * sizeof(Drink));
    if (order == NULL) {
        printf("Dodjela memorije nije uspjela. Izlazak iz programa.\n");
        return 1;
    }

    // Inicijalizacija numCategories i kategorija
    numCategories = 2;
    categories = malloc(numCategories * sizeof(Category));
    if (categories == NULL) {
        printf("Dodjela memorije nije uspjela. Izlazak iz programa.\n");
        free(order);
        return 1;
    }

    //Popunjavanje kategorija
    Category category1;
    strcpy(category1.name, "Topli");
    category1.numDrinks = 3;
    category1.drinks = malloc(category1.numDrinks * sizeof(Drink));
    if (category1.drinks == NULL) {
        printf("Dodjela memorije nije uspjela. Izlazak iz programa.\n");
        free(order);
        free(categories);
        return 1;
    }
    strcpy(category1.drinks[0].name, "Espresso");
    strcpy(category1.drinks[0].description, "Jaka aroma");
    category1.drinks[0].price = 2.99;
    strcpy(category1.drinks[1].name, "Cappuccino");
    strcpy(category1.drinks[1].description, "Espresso s toplom mlijecnom pjenom");
    category1.drinks[1].price = 3.99;
    strcpy(category1.drinks[2].name, "Latte");
    strcpy(category1.drinks[2].description, "Espresso s mlijekom");
    category1.drinks[2].price = 4.99;

    Category category2;
    strcpy(category2.name, "Bezalkoholni");
    category2.numDrinks = 2;
    category2.drinks = malloc(category2.numDrinks * sizeof(Drink));
    if (category2.drinks == NULL) {
        printf("Dodjela memorije nije uspjela. Izlazak iz programa.\n");
        free(order);
        free(categories);
        free(category1.drinks);
        return 1;
    }
    strcpy(category2.drinks[0].name, "Coca-Cola");
    strcpy(category2.drinks[0].description, "Taste the feeling");
    category2.drinks[0].price = 1.99;
    strcpy(category2.drinks[1].name, "Limunada");
    strcpy(category2.drinks[1].description, "Kada ti zivot da limun napravi limunadu");
    category2.drinks[1].price = 2.99;

    categories[0] = category1;
    categories[1] = category2;

    do {
        printMenu();
        printf("Unesi svoj izbor: ");
        if (scanf("%d", &choice) != 1) {
            printf("Pogrešan unos. Unesite valjanu opciju.\n");
            while (getchar() != '\n'); // ciscenje ulaznog medjuspremnika
            continue; // Ponovno pokrenite petlju da bi se dobio vazeci unos
        }

        switch (choice) {
        case 1:
            displayMenu();
            break;

        case 2:
            if (numItems >= MAX_ORDER_SIZE) {
                printf("Narudzba je vec puna.\n");
            }
            else {
                printf("\nIzaberi vrstu napitka: \n");
                for (int i = 0; i < numCategories; i++) {
                    printf("%d. %s\n", i + 1, categories[i].name);
                }

                int categoryChoice;
                printf("Unesi broj kategorije koji zelis dodati u narudzbu: ");
                if (scanf("%d", &categoryChoice) != 1 || categoryChoice < 1 || categoryChoice > numCategories) {
                    printf("Pogresan unos. Unesite vazeci broj.\n");
                    while (getchar() != '\n'); 
                    continue; 
                }

                Category selectedCategory = categories[categoryChoice - 1];
                printf("\n%s Napitci:\n", selectedCategory.name);
                for (int i = 0; i < selectedCategory.numDrinks; i++) {
                    printf("%d. %s - %s (%.2fkn)\n", i + 1, selectedCategory.drinks[i].name,
                        selectedCategory.drinks[i].description, selectedCategory.drinks[i].price);
                }

                int drinkChoice;
                printf("Unesi broj napitka koji zelis dodati u narudzbu: ");
                if (scanf("%d", &drinkChoice) != 1 || drinkChoice < 1 || drinkChoice > selectedCategory.numDrinks) {
                    printf("Pogresan unos. Unesite vazeci broj.\n");
                    while (getchar() != '\n'); 
                    continue; 
                }

                Drink selectedDrink = selectedCategory.drinks[drinkChoice - 1];
                addDrinkToOrder(selectedDrink, order, &numItems);
                printf("Dodano u narudzbu.\n");
            }
            break;

        case 3:
            if (numItems == 0) {
                printf("Narudzba je prazna.\n");
            }
            else {
                printf("\nOdaberite napitak koji zelite ukloniti: \n");
                for (int i = 0; i < numItems; i++) {
                    printf("%d. %s\n", i + 1, order[i].name);
                }

                int removeChoice;
                printf("Unesite njegov broj: ");
                if (scanf("%d", &removeChoice) != 1 || removeChoice < 1 || removeChoice > numItems) {
                    printf("Pogresan unos. Unesite vazeci broj.\n");
                    while (getchar() != '\n'); 
                    continue; 
                }

                removeDrinkFromOrder(removeChoice - 1, order, &numItems);
                printf("Uspjesno uklonjeno.\n");
            }
            break;

        case 4:
            if (numItems == 0) {
                printf("Narudzba je prazna.\n");
            }
            else {
                viewOrder(order, numItems);
            }
            break;

        case 5:
            if (numItems < 2) {
                printf("Nema dovoljno stavki za sortiranje..\n");
            }
            else {
                sortOrder(order, numItems);
                printf("Narudzba sortirana.\n");
            }
            break;

        case 6:
            saveOrderToFileText(order, numItems);
            break;

        case 7:
            saveOrderToFileBinary(order, numItems);
            break;

        case 8:
            loadOrderFromFileText(&order, &numItems);
            break;

        case 9:
            loadOrderFromFileBinary(&order, &numItems);
            break;
          
        case 10:
            if (numItems == 0) {
                printf("Narudzba je prazna.\n");
            }
            else {
                printf("=====================================\n");
                printf("           R A C U N\n");
                printf("=====================================\n");
                float total = 0.0;
                for (int i = 0; i < numItems; i++) {
                    printf("%d. %s - %s (%.2fkn)\n", i + 1, order[i].name, order[i].description, order[i].price);
                    total += order[i].price;
                }
                printf("-------------------------------------\n");
                printf("Ukupno: %.2fkn\n", total);
                printf("-------------------------------------\n");
                printf("Dodite nam opet :)\n");
            }
            break;

        case 11:
            free(order);
            printf("Izlaz iz programa...\n");
            return 0;

        default:
            printf("Pogresan unos. Pokusaj ponovo.\n");
            break;
        }

        while (getchar() != '\n'); // ciscenje ulaznog medjuspremnika
        printf("\n");
    } while (choice != 11);

    // Oslobadanje alocirane memorije
    free(order);
    for (int i = 0; i < numCategories; i++) {
        free(categories[i].drinks);
    }
    free(categories);

    return 0;
}
