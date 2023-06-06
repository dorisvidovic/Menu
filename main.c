#define _CRT_SECURE_NO_WARNINGS 
  
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "header.h" 
  
#define MAX_ORDER_SIZE 10 
  
int main() { 
    addUser("admin", "admin123", ADMIN); 
    addUser("moderator", "moderator123", MODERATOR); 
    addUser("guest", "guest123", GUEST); 
  
  
    char username[50]; 
    char password[50]; 
  
    printf("Welcome to the System\n"); 
  
    while (1) { 
        printf("Username: "); 
        fgets(username, sizeof(username), stdin); 
        username[strcspn(username, "\n")] = '\0'; // Remove newline character 
  
        printf("Password: "); 
        fgets(password, sizeof(password), stdin); 
        password[strcspn(password, "\n")] = '\0'; // Remove newline character 
  
        User* loggedInUser = loginUser(username, password); 
  
        if (loggedInUser != NULL) { 
            switch (loggedInUser->authority) { 
            case ADMIN: 
                printf("Logged in as Admin.\n"); 
                // Implement admin functionality 
                break; 
            case MODERATOR: 
                printf("Logged in as Moderator.\n"); 
                // Implement moderator functionality 
                break; 
            case GUEST: 
                printf("Logged in as Guest.\n"); 
                // Implement guest functionality 
                break; 
            } 
            break; 
        } 
    } 
  
    DrinkCategory menu[] = { 
        // Category 1: Hot Beverages  
        { 
            "Hot Beverages", 
            { 
                {"Espresso", "Strong and concentrated coffee", 2.50}, 
                {"Cappuccino", "Espresso with steamed milk and foam", 3.50}, 
                {"Latte", "Espresso with steamed milk", 3.00}, 
            }, 
            3 // Number of drinks in the category  
        }, 
        // Category 2: Non-Alcoholic Drinks  
        { 
            "Non-Alcoholic Drinks", 
            { 
                {"Cola", "Classic carbonated soft drink", 2.00}, 
                {"Lemonade", "Refreshing lemon-flavored drink", 3.00}, 
                {"Iced Tea", "Chilled tea with lemon and sugar", 2.50}, 
            }, 
            3 // Number of drinks in the category  
        }, 
        // Add more drink categories if needed  
    }; 
  
    int numDrinkCategories = sizeof(menu) / sizeof(DrinkCategory); 
  
    // Define an array to store the user's drink order  
    Drink order[MAX_ORDER_SIZE]; 
    int orderSize = 0; 
    char input[100]; 
  
  
    // Display the menu and prompt for user input  
    do { 
        displayMenu(menu, numDrinkCategories); 
  
        // Read the user's menu choice  
        char input[100]; 
        fgets(input, sizeof(input), stdin); 
        int categoryChoice = atoi(input); 
  
        // Check if the user wants to exit  
        if (categoryChoice == 0) { 
            printf("Thank you for your order!\n"); 
            break; 
        } 
  
        // Validate the menu choice  
        if (categoryChoice < 1 || categoryChoice > numDrinkCategories) { 
            printf("Invalid menu choice. Please try again.\n"); 
            continue; 
        } 
  
        // Get the selected category  
        DrinkCategory selectedCategory = menu[categoryChoice - 1]; 
  
        // Display the drinks in the category and prompt for user input  
        displayCategory(selectedCategory); 
  
        do { 
            printf("Enter the number of the drink you want to order (0 to finish): "); 
  
            // Read the user's drink choice  
            fgets(input, sizeof(input), stdin); 
            int drinkChoice = atoi(input); 
  
            // Check if the user wants to finish the order  
            if (drinkChoice == 0) { 
                printf("Your order is complete. Thank you!\n"); 
                break; 
            } 
  
            // Validate the drink choice  
            if (drinkChoice < 1 || drinkChoice > selectedCategory.numDrinks) { 
                printf("Invalid drink choice. Please try again.\n"); 
                continue; 
            } 
  
            // Add the selected drink to the order  
            Drink selectedDrink = selectedCategory.drinks[drinkChoice - 1]; 
  
            if (orderSize >= MAX_ORDER_SIZE) { 
                printf("Your order is full. Please finish your order or remove a drink.\n"); 
            } 
            else { 
                order[orderSize] = selectedDrink; 
                orderSize++; 
                printf("%s added to your order.\n", selectedDrink.name); 
            } 
  
        } while (1); 
  
    } while (1); 
  
    // Display the bill  
    printf("\n\n********** BILL **********\n\n"); 
    printf("Item\t\tPrice\n"); 
    printf("----\t\t-----\n"); 
    for (int i = 0; i < orderSize; i++) { 
        printf("%s\t\t$%.2f\n", order[i].name, order[i].price); 
    } 
    printf("\nTotal\t\t$%.2f\n", getTotal(order, orderSize)); 
  
    // Handle the user's order using a switch statement  
    int choice; 
  
    do { 
        printf("\nWhat would you like to do?\n"); 
        printf("1. Add a drink to the order\n"); 
        printf("2. Remove a drink from the order\n"); 
        printf("3. View the bill\n"); 
        printf("4. Exit\n"); 
  
        // Read the user's choice  
        fgets(input, sizeof(input), stdin); 
        choice = atoi(input); 
  
        switch (choice) { 
        case 1: 
            // Add a drink to the order  
            if (orderSize < MAX_ORDER_SIZE) { 
                printf("Please select a category and a drink:\n"); 
                // Same code as before to display the menu and prompt for user input  
                // ... 
            } 
            else { 
                printf("Your order is full. Please remove a drink first.\n"); 
            } 
            break; 
  
        case 2: 
            // Remove a drink from the order  
            if (orderSize > 0) { 
                printf("Enter the number of the drink you want to remove: "); 
                fgets(input, sizeof(input), stdin); 
                int removeChoice = atoi(input); 
  
                if (removeChoice < 1 || removeChoice > orderSize) { 
                    printf("Invalid drink choice. Please try again.\n"); 
                } 
                else { 
                    printf("%s removed from your order.\n", order[removeChoice - 1].name); 
                    // Shift the remaining drinks in the order to fill the gap  
                    for (int i = removeChoice; i < orderSize; i++) { 
                        order[i - 1] = order[i]; 
                    } 
                    orderSize--; 
                } 
            } 
            else { 
                printf("Your order is empty. Please add a drink first.\n"); 
            } 
            break; 
  
        case 3: 
            // View the bill  
            printf("\n\n********** BILL **********\n\n"); 
            printf("Item\t\tPrice\n"); 
            printf("----\t\t-----\n"); 
            for (int i = 0; i < orderSize; i++) { 
                printf("%s\t\t$%.2f\n", order[i].name, order[i].price); 
            } 
            printf("\nTotal\t\t$%.2f\n", getTotal(order, orderSize)); 
            break; 
  
        case 4: 
            // Exit the program  
            printf("Thank you for your order!\n"); 
            exit(0); 
  
        default: 
            // Invalid input  
            printf("Invalid input. Please try again.\n"); 
            break; 
        } 
    } while (1); 
  
    return 0; 
} 
