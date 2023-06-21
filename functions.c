// functions.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Category* categories;
int numCategories;

void printMenu() {
    printf("Dobar dan, izvolite\n");
    printf("1. Dodaj stavku\n");
    printf("2. Izbaci stavku\n");
    printf("3. Ispisi sadrzaj narudzbe\n");
    printf("4. Ispisi ukupan iznos\n");
    printf("5. Ispisi broj stavki\n");
    printf("6. Obrisi narudzbu\n");
    printf("7. Promijeni naziv stavke\n");
    printf("8. Promijeni opis stavke\n");
    printf("9. Promijeni cijenu stavke\n");
    printf("10. Prikazi racun\n");
    printf("11. Izlaz\n");
}


void displayMenu() {
    printf("\nMenu:\n");
    for (int i = 0; i < numCategories; i++) {
        printf("\n%s napitci: \n", categories[i].name);
        for (int j = 0; j < categories[i].numDrinks; j++) {
            printf("%d. %s - %s (%.2fkn)\n", j + 1, categories[i].drinks[j].name,
                categories[i].drinks[j].description, categories[i].drinks[j].price);
        }
    }
}


void addDrinkToOrder(Drink drink, Drink* order, int* numItems) {
    if (*numItems < MAX_ORDER_SIZE) {
        order[*numItems] = drink;
        (*numItems)++;
        printf("\n");
    }
    else {
        printf("Narudzba je puna\n");
    }
}


void removeDrinkFromOrder(int index, Drink* order, int* numItems) {
    for (int i = index; i < *numItems - 1; i++) {
        order[i] = order[i + 1];
    }
    (*numItems)--;
}

void viewOrder(Drink* order, int numItems) {
    printf("Narudzba: \n");
    for (int i = 0; i < numItems; i++) {
        printf("%d. %s - %s (%.2fkn)\n", i + 1, order[i].name, order[i].description, order[i].price);
    }
}

void sortOrder(Drink* order, int numItems) {
    for (int i = 0; i < numItems - 1; i++) {
        for (int j = 0; j < numItems - i - 1; j++) {
            if (order[j].price > order[j + 1].price) {
                Drink temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }
}

void saveOrderToFileText(Drink* order, int numItems) {
    FILE* file = fopen("order.txt", "w");
    if (file == NULL) {
        printf("Pogreska pri otvaranju datoteke za pisanje\n");
        return;
    }

    for (int i = 0; i < numItems; i++) {
        fprintf(file, "%s,%s,%.2f\n", order[i].name, order[i].description, order[i].price);
    }

    fclose(file);
    printf("Narudžba je spremljena u datoteku (Tekst).\n");
}

void saveOrderToFileBinary(Drink* order, int numItems) {
    FILE* file = fopen("order.bin", "wb");
    if (file == NULL) {
        printf("Pogreska pri otvaranju datoteke za pisanje\n");
        return;
    }

    size_t objectsWritten = fwrite(order, sizeof(Drink), numItems, file);
    if (objectsWritten != numItems) {
        printf("Pogreska u pisanju.\n");
        fclose(file);
        return;
    }

    fclose(file);
    printf("Narudžba je spremljena u datoteku (Binarno).\n");
}


void loadOrderFromFileText(Drink** order, int* numItems) {
    FILE* file = fopen("order.txt", "r");
    if (file == NULL) {
        printf("Pogreska pri otvaranju datoteke za citanje.\n");
        return;
    }

    Drink* newOrder = NULL;
    int newSize = 0;
    char line[MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH + 10];

    while (fgets(line, sizeof(line), file) != NULL) {
        char name[MAX_NAME_LENGTH];
        char description[MAX_DESCRIPTION_LENGTH];
        float price;

        if (sscanf(line, "%[^,],%[^,],%f\n", name, description, &price) != 3) {
            printf("Pogreska pri analizi retka: %s\n", line);
            fclose(file);
            return;
        }

        name[MAX_NAME_LENGTH - 1] = '\0';  //null termination
        description[MAX_DESCRIPTION_LENGTH - 1] = '\0';  

        Drink drink;
        strcpy(drink.name, name);
        strcpy(drink.description, description);
        drink.price = price;

        newSize++;
        Drink* temp = realloc(newOrder, newSize * sizeof(Drink));
        if (temp == NULL) {
            printf("Pogreska pri dodjeli memorije.\n");
            free(newOrder); 
            fclose(file);
            return;
        }
        newOrder = temp;
        newOrder[newSize - 1] = drink;
    }

    fclose(file);

    if (newOrder != NULL) {
        free(*order);
        *order = newOrder;
        *numItems = newSize;
        printf("Narudzba ucitana iz datoteke (Tekst).\n");
    }
    else {
        printf("Pogreska pri ucitavanju narudzbe iz datoteke (Tekst).\n");
    }
}

void loadOrderFromFileBinary(Drink** order, int* numItems) {
    FILE* file = fopen("order.bin", "rb");
    if (file == NULL) {
        printf("Pogreska pri otvaranju datoteke za citanje.\n");
        return;
    }

    Drink* newOrder = NULL;
    int newSize = 0;

    Drink drink;
    while (fread(&drink, sizeof(Drink), 1, file) == 1) {
        newSize++;
        Drink* temp = realloc(newOrder, newSize * sizeof(Drink));
        if (temp == NULL) {
            // Handle allocation failure
            printf("Pogreska pri dodjeli memorije.\n");
            free(newOrder); // Free the original memory block
            fclose(file);
            return;
        }
        newOrder = temp;
        newOrder[newSize - 1] = drink;
    }

    fclose(file);

    if (newOrder != NULL) {
        free(*order);
        *order = newOrder;
        *numItems = newSize;
        printf("Narudzba ucitana iz datoteke (Binarno).\n");
    }
    else {
        printf("Pogreska pri ucitavanju narudzbe iz datoteke (Binarno).\n");
    }
}
