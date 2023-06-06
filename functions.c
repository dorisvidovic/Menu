#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
#define MAX_USERS 10 
#define MAX_ARTICLES 100 
  
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
  
typedef struct { 
    char title[100]; 
    char content[500]; 
} Article; 
  
User users[MAX_USERS]; 
int numUsers = 0; 
  
Article articles[MAX_ARTICLES]; 
int numArticles = 0; 
  
void addUser(const char* username, const char* password, Authority authority) { 
    if (numUsers >= MAX_USERS) { 
        printf("Maximum number of users reached.\n"); 
        return; 
    } 
  
    User newUser; 
    strcpy_s(newUser.username, sizeof(newUser.username), username); 
    strcpy_s(newUser.password, sizeof(newUser.password), password); 
    newUser.authority = authority; 
  
    users[numUsers] = newUser; 
    numUsers++; 
  
    printf("User added successfully.\n"); 
} 
  
User* loginUser(const char* username, const char* password) { 
    for (int i = 0; i < numUsers; i++) { 
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) { 
            return &users[i]; 
        } 
    } 
    return NULL; // User not found or incorrect credentials 
} 
  
void addArticle(const char* title, const char* content, User* user) { 
    if (user->authority == GUEST) { 
        printf("Guest users are not allowed to add articles.\n"); 
        return; 
    } 
  
    if (numArticles >= MAX_ARTICLES) { 
        printf("Maximum number of articles reached.\n"); 
        return; 
    } 
  
    Article newArticle; 
    strcpy_s(newArticle.title, sizeof(newArticle.title), title); 
    strcpy_s(newArticle.content, sizeof(newArticle.content), content); 
  
    articles[numArticles] = newArticle; 
    numArticles++; 
  
    printf("Article added successfully.\n"); 
} 
