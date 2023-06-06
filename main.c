// main.c
#define MAX_ORDER_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
	addUser("admin", "admin123", ADMIN);
	addUser("moderator", "moderator123", MODERATOR);
	addUser("guest", "guest123", GUEST);

	char username[50];
	char password[50];

	printf("Dobrodosli u sustav\n");

	while (1) {
		printf("Korisnicko ime: ");
		fgets(username, sizeof(username), stdin);
		username[strcspn(username, "\n")] = '\0'; // Ukloni znak za novi red

		printf("Lozinka: ");
		fgets(password, sizeof(password), stdin);
		password[strcspn(password, "\n")] = '\0'; // Ukloni znak za novi red

		User* loggedInUser = loginUser(username, password);

		if (loggedInUser != NULL) {
			switch (loggedInUser->authority) {
			case ADMIN:
				printf("Prijavljeni ste kao administrator.\n");
				// Implementiraj funkcionalnosti administratora
				break;
			case MODERATOR:
				printf("Prijavljeni ste kao moderator.\n");
				// Implementiraj funkcionalnosti moderatora
				break;
			case GUEST:
				printf("Prijavljeni ste kao gost.\n");
				// Implementiraj funkcionalnosti gosta
				break;
			}
			break;
		}
		else {
			printf("Neispravno korisnicko ime ili lozinka. Molimo pokusajte ponovno.\n");
		}
	}

	DrinkCategory menu[] = {
		// Kategorija 1: Tople napitke
		{
			"Topli napitci",
			{
				{"Espresso", "Jaka aroma, bogati ukus i kremasta tekstura", 2.50},
				{"Cappuccino", "Espresso s toplom mlijecnom pjenom", 3.50},
				{"Latte", "Espresso s mlijekom, blaga aroma", 3.00},
			},
			3 // Broj pica u kategoriji
		},
		// Kategorija 2: Bezalkoholna pica
		{
			"Bezalkoholna pica",
			{
				{"Coca-Cola", "Taste the feeling", 2.00},
				{"Limonada", "Kada ti život da limun, napravi limunadu.", 3.00},
				{"Ledena caj", "Ohladeni caj s limunom i secerom", 2.50},
			},
			3 // Broj pica u kategoriji
		},
		// Dodajte jos kategorija pica po potrebi
	};

	int numDrinkCategories = sizeof(menu) / sizeof(DrinkCategory);

	// Definirajte polje za spremanje narudzbe korisnika
	Drink order[MAX_ORDER_SIZE];
	int orderSize = 0;
	char input[100];

	// Prikaz izbornika i upit korisnika za unos
	do {
		displayMenu(menu, numDrinkCategories);

		// Procitaj odabir korisnika
		fgets(input, sizeof(input), stdin);
		int categoryChoice = atoi(input);

		// Provjeri zeli li korisnik izaci
		if (categoryChoice == 0) {
			printf("Hvala na narudzbi!\n");
			break;
		}

		// Provjeri ispravnost odabira izbornika
		if (categoryChoice < 1 || categoryChoice > numDrinkCategories) {
			printf("Neispravan odabir izbornika. Molimo pokusajte ponovno.\n");
			continue;
		}

		// Dohvati odabranu kategoriju
		DrinkCategory selectedCategory = menu[categoryChoice - 1];

		// Prikaz pica u odabranoj kategoriji i upit korisnika za unos
		displayCategory(selectedCategory);

		do {
			printf("Unesite broj pica koje zelite naruciti (0 za zavrsetak): ");

			// Procitaj odabir korisnika za pice
			fgets(input, sizeof(input), stdin);
			int drinkChoice = atoi(input);

			// Provjeri zeli li korisnik zavrsiti narudzbu
			if (drinkChoice == 0) {
				printf("Vasa narudzba je zavrsena. Hvala!\n");
				break;
			}

			// Provjeri ispravnost odabira pica
			if (drinkChoice < 1 || drinkChoice > selectedCategory.numDrinks) {
				printf("Neispravan odabir pica. Molimo pokusajte ponovno.\n");
				continue;
			}

			// Dodaj odabrano pice u narudzbu
			Drink selectedDrink = selectedCategory.drinks[drinkChoice - 1];

			if (orderSize >= MAX_ORDER_SIZE) {
				printf("Vasa narudzba je puna. Molimo zavrsite narudzbu ili uklonite pice.\n");
			}
			else {
				order[orderSize] = selectedDrink;
				orderSize++;
				printf("%s dodano u vasu narudzbu.\n", selectedDrink.name);
			}
		} while (1);
	} while (1);

	// Prikaz racuna
	printf("\n\n********** RACUN **********\n\n");
	printf("Stavka\t\tCijena\n");
	printf("------\t\t------\n");
	for (int i = 0; i < orderSize; i++) {
		printf("%s\t\t%.2f kn\n", order[i].name, order[i].price);
	}
	printf("\nUkupno\t\t%.2f kn\n", getTotal(order, orderSize));

	// Obrada narudzbe korisnika koristenjem naredbe switch
	int choice;

	do {
		printf("\nsto zelite napraviti?\n");
		printf("1. Dodaj pice u narudzbu\n");
		printf("2. Ukloni pice iz narudzbe\n");
		printf("3. Pregledaj racun\n");
		printf("4. Izlaz\n");

		// Procitaj odabir korisnika
		fgets(input, sizeof(input), stdin);
		choice = atoi(input);

		switch (choice) {
		case 1:
			// Dodaj pice u narudzbu
			if (orderSize < MAX_ORDER_SIZE) {
				printf("Molimo odaberite kategoriju i pice:\n");
				// Ista koda kao i prije za prikaz izbornika i unos narudzbe
				break;
			}
			else {
				printf("Vasa narudzba je puna. Molimo zavrsite narudzbu ili uklonite pice.\n");
			}
			break;
		case 2:
			// Ukloni pice iz narudzbe
			if (orderSize > 0) {
				printf("Odaberite redni broj pica koje zelite ukloniti:\n");
				// Ista koda kao i prije za prikaz narudzbe i odabir pica za brisanje
				break;
			}
			else {
				printf("Narudzba je prazna. Molimo dodajte pice prije nego sto ga uklonite.\n");
			}
			break;
		case 3:
			// Pregledaj racun
			printf("\n\n********** RACUN **********\n\n");
			printf("Stavka\t\tCijena\n");
			printf("------\t\t------\n");
			// Ista koda kao i prije za prikaz racuna
			printf("Ukupno\t\t%.2f kn\n", getTotal(order, orderSize));
			break;
		case 4:
			// Izlaz iz programa
			printf("Hvala na posjetu. Dovidenja!\n");
			break;
		default:
			printf("Neispravan odabir. Molimo pokusajte ponovno.\n");
			break;
		}
	} while (choice != 4);

	return 0;
}
