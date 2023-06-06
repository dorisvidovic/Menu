#pragma once 
  
#define MAX_USERS 10 
  
extern int numUsers;  // Declare the variable as extern 
  
typedef enum { 
    ADMIN, 
    MODERATOR, 
    GUEST 
} Authority; 
  
typedef struct { 
    char username[50]; 
    char password[50]; 
    Authority authority; 
} User; 
  
extern User users[MAX_USERS];  // Declare the users array as extern 
  
User users[MAX_USERS] = { 
    {"admin", "admin123", ADMIN}, 
    {"moderator", "mod123", MODERATOR}, 
    {"guest", "guest123", GUEST} 
}; 
  
int numUsers = sizeof(users) / sizeof(User); 
  
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
 
