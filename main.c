#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define Y  "\033[33m"
#define RESET       "\x1b[0m"
#define ORANGEE      "\x1b[38;5;208m"
#define REDD         "\x1b[31m"
#define BLUEE        "\x1b[34m"
#define MAGENTAA     "\x1b[35m"
#define VIOLETT      "\x1b[38;5;93m"
#define GREENN       "\x1b[32m"
#define GOLDD        "\x1b[38;5;220m"
#define MAROONN      "\x1b[38;5;88m"
#define O ORANGEE
#define R REDD
#define B BLUEE
#define m MAGENTAA
#define V VIOLETT
#define g GREENN
#define G GOLDD
#define M MAROONN
#define r RESET
#define RESET       "\x1b[0m"
#define BLACK_TEXT  "\x1b[30m"
#define GREEN_TEXT  "\x1b[32m"
#define RED_TEXT    "\x1b[31m"
#define IVORY_BG    "\x1b[48;5;230m"
#define ANSI_COLOR_ORANGE "\x1b[38;2;255;165;0m" // Orange
#define ANSI_COLOR_RESET "\x1b[0m"
#define MAX_ITEMS 300
#define MAX_NAME_LENGTH 50
#define NUM_RESTAURANTS 27
#define INF INT_MAX
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define DATABASE_FILE "data/users.txt"
#define MAX_ENTRIES 100
#define MAX_MENU_ITEMS 100
#define MAX_LENGTH 50
#define FILENAME_LENGTH 500
#define MAX_USERS 100
#define MAX_LINE_LENGTH 1024
#define MIN_SUPPORT 2
#define SUGGESTION_COUNT 3
#define MAX_MENU_ITEMS 100
#define MAX_NAME_LENGTH 50
#define FILENAME_MAX_LENGTH 50
#define WEIGHT_DISTANCE 3.0
#define WEIGHT_RATING 2.0
#define WEIGHT_OFFER 1.5
#define TERMINAL_WIDTH 150
#define MAX_RESTAURANTS 100
#define NAME_LENGTH 50
#define EMERALD_TEXT   "\x1b[38;5;34m"
#define MAX_DRIVERS 100
#define DRIVER_FILE "data/drivers.txt"
#define FLT_MAX 9999999999999999.999999999
#define RESTAURANT_FILE "data/restaurant.txt"
#define EMERALD_BG     "\x1b[48;5;34m" 
#define LIGHT_GREEN "\033[1;32m" 
#define PREMIUM_MEMBERSHIP_COST 500.0
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_STREET_NAME_LEN 100
#define MAX_CITY_NAME_LEN 50

long con(const char *str) {
  char *endptr;
  return strtol(str, &endptr, 10);
}

struct CartItem {
  char id[5];
  char name[50];
  int quantity;
};

// Structure to represent a coordinate
typedef struct {
  int x;
  int y;
} Coordinate;

// Structure to store menu item information
struct MenuItem {
  char name[MAX_NAME_LENGTH];
  char price[10];
  char type[MAX_NAME_LENGTH];
  char id[10];
  char quantity[3];
};
struct MenuItem menu[20];

// Structure to represent a restaurant
typedef struct {
  char name[50];
  int id;
  Coordinate location;
  float rating;
  int offer;
  int order;
} Restaurant;
typedef struct {
  int doorno;
  int streetno;
  char streetname[50];
  char city[50];
} address;

struct Restaurant1 {
    char name[MAX_NAME_LENGTH];
    int id;
    int col1;
    int col2;
    float col3;
    int col4;
    int col5;
   
};

typedef struct {
  char username[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  address address;
  int num_orders;
  double ewallet_money;
  int credit;
  int member;
} User;

void print_center_aligned(const char *text) {
  int len = strlen(text);
  int padding = (TERMINAL_WIDTH - len) / 2;
  for (int i = 0; i < padding; i++) {
    printf(" ");
  }
  printf("%s\n", text);
}

// Function to validate the entered username and password
User *validate_login(const char *username, const char *password) {
  FILE *file = fopen(DATABASE_FILE, "r");
  if (file == NULL) {

    printf("\033[1;31m");
    print_center_aligned("Error opening file.\n");
    return NULL;
  }

  User *user = malloc(sizeof(User));
  if (user == NULL) {
    printf("\033[1;31m");
    print_center_aligned("Memory allocation failed.\n");
    return NULL;
  }

  char db_username[MAX_USERNAME_LENGTH];
  char db_password[MAX_PASSWORD_LENGTH];
  char db_cityname[MAX_ADDRESS_LENGTH];
  int db_dno;
  int db_streetno;
  char db_streetname[MAX_ADDRESS_LENGTH];
  int db_num_orders;
  double db_ewallet_money;
  int db_credit;
  int db_member;

  // Read each line from the file and compare username and password
  while (fscanf(file, "%s %s %d %d %s %s %d %lf %d %d", db_username,
                db_password, &db_dno, &db_streetno, db_streetname, db_cityname,
                &db_num_orders, &db_ewallet_money, &db_credit,
                &db_member) != EOF) {
    if (strcmp(username, db_username) == 0 &&
        strcmp(password, db_password) == 0) {
      strcpy(user->username, db_username);
      strcpy(user->password, db_password);
      user->address.doorno = db_dno;
      user->address.streetno = db_streetno;
      strcpy(user->address.streetname, db_streetname);
      strcpy(user->address.city, db_cityname);
      user->num_orders = db_num_orders;
      user->ewallet_money = db_ewallet_money;
      user->credit = db_credit;
      user->member = db_member;
      fclose(file);
      return user;
    }
  }

  fclose(file);
  free(user);
  return NULL;
}

// Function to create a new account

int username_exists(const char *username) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        return 0; // File does not exist, so username cannot exist
    }

    char existing_username[MAX_USERNAME_LEN];
    while (fscanf(file, "%s", existing_username) != EOF) {
        // Skip the rest of the line
        char buffer[512];
        fgets(buffer, sizeof(buffer), file);

        if (strcmp(existing_username, username) == 0) {
            fclose(file);
            return 1; // Username found
        }
    }

    fclose(file);
    return 0; // Username not found
}

void create_account() {
    User new_user;

    // Prompt the user to enter their username
    
    do {
        printf("\n\n");
        printf("\033[1;34m");
        printf("\t\t\t\tEnter your username: ");
        printf("\033[0m");
        scanf("%s", new_user.username);
        printf("\n\n");

        if (username_exists(new_user.username)) {
            printf("\033[1;31m");
            printf("Username already exists. Please choose a different username.\n");
            printf("\033[0m");
        }
    } while (username_exists(new_user.username));

    printf("\033[1;34m");
    // Prompt the user to enter their password
    printf("\t\t\t\tEnter your password: ");
    printf("\033[0m");
    scanf("%s", new_user.password);
    printf("\n\n");

    // Prompt the user to enter their address
    printf("\033[1;35m");
    print_center_aligned("Enter your address: ");
    printf("\n\n");
    printf("\033[1;34m");
    printf("\t\t\t\tEnter Your Door No : ");
    printf("\033[0m");
    scanf("%d", &new_user.address.doorno);
    printf("\n\n");
    printf("\033[1;34m");
    printf("\t\t\t\tEnter your Street No : ");
    printf("\033[0m");
    scanf("%d", &new_user.address.streetno);
    printf("\n\n");
    printf("\033[1;34m");
    printf("\t\t\t\tEnter your Street Name : ");
    printf("\033[0m");
    scanf("%s", new_user.address.streetname);
    printf("\n\n");
    printf("\033[1;34m");
    printf("\t\t\t\tEnter your City Name : ");
    printf("\033[0m");
    scanf("%s", new_user.address.city);
    printf("\n\n");

    new_user.num_orders = 0;
    new_user.ewallet_money = 10000.00;
    new_user.credit = 0;
    new_user.member = 0; // Set default eWallet money to 10000.00

    // Append the new user details to the database file
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        printf("\033[1;31m");
        printf("Error Opening File!!.\n");
        return;
    }

    fprintf(file, "%s %s %d %d %s %s %d %.2f %d %d\n",
            new_user.username, new_user.password,
            new_user.address.doorno, new_user.address.streetno,
            new_user.address.streetname, new_user.address.city,
            new_user.num_orders, new_user.ewallet_money,
            new_user.credit, new_user.member);
    fclose(file);

    printf("\033[1;32m");
    print_center_aligned("Account created successfully!\n");
}

typedef struct {
  int id;
  char name[MAX_LENGTH];
  float price;
  char type[MAX_LENGTH];
} Item;

typedef struct {
  char name[MAX_LENGTH];
  char menuFileName[FILENAME_LENGTH];
  Item items[MAX_MENU_ITEMS];
  int itemCount;
  char type[MAX_LENGTH];
} Entry;

void toLowerCase(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

void readData(Entry entries[], int *entryCount) {
  FILE *restaurantFile = fopen("data/restaurant.txt", "r");
  if (restaurantFile == NULL) {
    printf("Error opening restaurant file.\n");
    exit(1);
  }

  *entryCount = 0;
  char line[200];
  while (fgets(line, sizeof(line), restaurantFile) != NULL) {
    char name[MAX_LENGTH];
    int menuFileIndex;
    if (sscanf(line, "%49[^,],%d", name, &menuFileIndex) == 2) {
      snprintf(entries[*entryCount].menuFileName, FILENAME_LENGTH,
               "data/%d.csv", menuFileIndex);
      strncpy(entries[*entryCount].name, name, MAX_LENGTH);
      (*entryCount)++;
    }
  }
  fclose(restaurantFile);
}

void readMenuData(Entry *entry) {
  FILE *menuFile = fopen(entry->menuFileName, "r");
  if (menuFile == NULL) {
    printf("Error opening menu file for %s.\n", entry->name);
    return;
  }

  char line[200];
  entry->itemCount = 0;
  while (fgets(line, sizeof(line), menuFile) != NULL) {
    if (sscanf(line, "%d,%49[^,],%f,%49[^\n]\n",
               &entry->items[entry->itemCount].id,
               entry->items[entry->itemCount].name,
               &entry->items[entry->itemCount].price,
               entry->items[entry->itemCount].type) == 4) {
      entry->itemCount++;
    }
  }
  fclose(menuFile);
}

void displayItems(Entry entry) {
  printf("\t\t\t\tItems for %s:\n", entry.name);
  for (int i = 0; i < entry.itemCount; i++) {
    printf("\t\t\t\t\t%d. %s - %.2f, %s\n", entry.items[i].id, entry.items[i].name,
           entry.items[i].price, entry.items[i].type);
  }
}

int getNumericPart(const char *fileName) {
  const char *ptr = fileName;
  while (*ptr && !isdigit(*ptr)) {
    ptr++;
  }
  return atoi(ptr);
}

int searchAndDisplay(Entry entries[], int entryCount, const char *query) {
  int found = 0;
  int serializedIndex = 1;
  char lowerQuery[MAX_LENGTH];
  strcpy(lowerQuery, query);
  toLowerCase(lowerQuery);

  print_center_aligned("Search Results : \n");
  for (int i = 0; i < entryCount; i++) {
    char lowerName[MAX_LENGTH];
    strcpy(lowerName, entries[i].name);
    toLowerCase(lowerName);
    if (strstr(lowerName, lowerQuery)) {
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d. %sEntry: %s%s\n\n", serializedIndex,Y,r,entries[i].name);
      serializedIndex++;
      found = 1;
    }
  }

  for (int i = 0; i < entryCount; i++) {
    for (int j = 0; j < entries[i].itemCount; j++) {
      char lowerItem[MAX_LENGTH];
      strcpy(lowerItem, entries[i].items[j].name);
      toLowerCase(lowerItem);
      if (strstr(lowerItem, lowerQuery)) {
        
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d. %sItem :%s%s in %sEntry : %s%s\n\n", serializedIndex,O,r               ,entries[i].items[j].name,Y,r,entries[i].name);
        serializedIndex++;
        found = 1;
      }
    }
  }

  if (!found) {
    printf(REDD);
    printf("\t\t\t\t\t\t\tNo Results Found for Query: %s\n"r, query);
    return -1;
  }
  printf(M);
  printf("\t\t\t\tEnter the Number Corresponding to the Entry to View its Items (0 to "
         "Exit): ");
  int choice;
  printf(r);
  scanf("%d", &choice);

  if (choice > 0 && choice < serializedIndex) {
    serializedIndex = 1;
    for (int i = 0; i < entryCount; i++) {
      char lowerName[MAX_LENGTH];
      strcpy(lowerName, entries[i].name);
      toLowerCase(lowerName);
      if (strstr(lowerName, lowerQuery)) {
        if (serializedIndex == choice) {
          //displayItems(entries[i]);
          return getNumericPart(entries[i].menuFileName);
        }
        serializedIndex++;
      }
    }
    for (int i = 0; i < entryCount; i++) {
      for (int j = 0; j < entries[i].itemCount; j++) {
        char lowerItem[MAX_LENGTH];
        strcpy(lowerItem, entries[i].items[j].name);
        toLowerCase(lowerItem);
        if (strstr(lowerItem, lowerQuery)) {
          if (serializedIndex == choice) {
            printf("\t\t\t\t\t\t\t\t\t\t\t%sItem: %s%s\n\n", O,r, entries[i].items[j].name);
            //displayItems(entries[i]);
            return getNumericPart(entries[i].menuFileName);
          }
          serializedIndex++;
        }
      }
    }
  } else if (choice != 0) {
    printf(r);
    printf("\t\t\t\tInvalid choice.\n");
  }

  return -1;
}

// Comparison function for qsort
int compareRatings(const void *a, const void *b) {
    Restaurant *restaurantA = (Restaurant *)a;
    Restaurant *restaurantB = (Restaurant *)b;

    // Combine rating and ID into a composite value
    float compositeA = restaurantA->rating + (float)restaurantA->id / 1000.0;
    float compositeB = restaurantB->rating + (float)restaurantB->id / 1000.0;

    // Compare the composite values
    if (compositeA > compositeB) {
        return -1; // restaurantA comes before restaurantB
    } else if (compositeA < compositeB) {
        return 1; // restaurantB comes before restaurantA
    } else {
        return 0; // ratings and IDs are equal
    }
}

// Function to rank and display the top 10 restaurants
void rankAndDisplayRestaurants(Restaurant restaurants[], int numRestaurants) {
    // Sort restaurants by rating
    qsort(restaurants, numRestaurants, sizeof(Restaurant), compareRatings);

    // Display top 10 ranked restaurants
    print_center_aligned("        Top Rated Restaurants \n\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t%-30s %-5s %-10s\n\n", "Restaurant Name", "ID", "Rating");
    char str[50];
    strcpy(str,restaurants[0].name);
    for (int i = 0; i < 10 && i < numRestaurants; i++) {
      if(i>0){
         strcpy(str,restaurants[i].name+1);
      }
        printf("\t\t\t\t\t\t\t\t\t\t\t\t%-30s %s%-5d %s%-10.2f\n\n",
               str,BLUEE,restaurants[i].id,GOLDD ,restaurants[i].rating);
               printf(r);
    }
}
// Function to compare restaurants by their offer percentage (for qsort)
int compareByOffer(const void *a, const void *b) {
  Restaurant *restaurantA = (Restaurant *)a;
  Restaurant *restaurantB = (Restaurant *)b;
  return restaurantB->offer - restaurantA->offer; // Descending order
}

// Function to sort and display restaurant names, IDs, and offers
void sortAndDisplayRestaurants(Restaurant restaurants[]) {
  // Sort restaurants by offer percentage
  qsort(restaurants, NUM_RESTAURANTS, sizeof(Restaurant), compareByOffer);

  // Display the sorted list of restaurant names, IDs, and offers
  print_center_aligned(Y"   Top Offers Around you \n\n\n"r);
  printf("\t\t\t\t\t\t\t\t\t\t\t%-30s %-5s %-10s\n", "Restaurant Name", "ID", "Offer(%)");
  char str[50];
  strcpy(str,restaurants[0].name);
  for (int i = 0; i < 10 && i <  NUM_RESTAURANTS; i++) {
    
       strcpy(str,restaurants[i].name+1);
    
      printf("\t\t\t\t\t\t\t\t\t\t\t%-30s %s%-5d %s%-10d\n\n",
             str,BLUEE,restaurants[i].id,EMERALD_TEXT ,restaurants[i].offer);
             printf(r);
  }
  printf("\n\t\t\t\t\t\t\t\t\t\tT/c : Offer only applicable for orders above 500\n");
}

void addMoneyToEwallet(const char username[], double amount) {
  FILE *file = fopen("data/users.txt", "r+");
  if (!file) {
    perror("Failed to open file");
    return;
  }

  User users[MAX_USERS];
  int userCount = 0;

  // Read users from file
  while (
      fscanf(file, "%s %s %d %d %s %s %d %lf %d %d", users[userCount].username,
             users[userCount].password, &users[userCount].address.doorno,
             &users[userCount].address.streetno,
             users[userCount].address.streetname, users[userCount].address.city,
             &users[userCount].num_orders, &users[userCount].ewallet_money,
             &users[userCount].credit, &users[userCount].member) == 10) {
    userCount++;
  }

  // Find the user and update eWallet money
  for (int i = 0; i < userCount; i++) {
    if (strcmp(users[i].username, username) == 0) {
      users[i].ewallet_money += amount;
      printf("\n\t\t\t\t%sNew eWallet balance:%s %.2f\n",G,r ,users[i].ewallet_money);
      break;
    }
  }

  // Rewrite the file with updated data
  freopen("data/users.txt", "w", file);
  for (int i = 0; i < userCount; i++) {
    fprintf(file, "%s %s %d %d %s %s %d %.2lf %d %d\n", users[i].username,
            users[i].password, users[i].address.doorno,
            users[i].address.streetno, users[i].address.streetname,
            users[i].address.city, users[i].num_orders, users[i].ewallet_money,
            users[i].credit, users[i].member);
  }

  fclose(file);
}
// Custom graph structure to represent the map
typedef struct {
  double edges[NUM_RESTAURANTS]
              [NUM_RESTAURANTS];         // Distance between restaurants
  Coordinate locations[NUM_RESTAURANTS]; // Store restaurant locations
} MapGraph;

void readEdgesFromFile(const char *filename, MapGraph *graph) {
  FILE *file = fopen(filename, "rb"); // Open file for reading in binary mode
  if (file == NULL) {
    printf("Error opening file %s\n", filename);
    return;
  }
  // Read the edges array from the file
  fread(graph->edges, sizeof(double), NUM_RESTAURANTS * NUM_RESTAURANTS, file);

  fclose(file);
}

// Function prototype for alreadyChosen
// int alreadyChosen(int restaurant, int closestRestaurants[], int index);

// Function to calculate Euclidean distance between two points
double calculateDistance(Coordinate point1, Coordinate point2) {
  return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

// Function to implement Dijkstra's algorithm to find the shortest paths from
// source to all vertices
void dijkstra(MapGraph *graph, Coordinate userCoord, double dist[]) {
  int visited[NUM_RESTAURANTS];
  int closestRestaurant = -1;
  double minDist = INF;

  for (int i = 0; i < NUM_RESTAURANTS; i++) {
    dist[i] = INF;
    visited[i] = 0;
    double restaurantDist = calculateDistance(userCoord, graph->locations[i]);
    if (restaurantDist < minDist) {
      minDist = restaurantDist;
      closestRestaurant = i;
    }
  }

  dist[closestRestaurant] = 0;

  for (int count = 0; count < NUM_RESTAURANTS - 1; count++) {
    int u = -1;
    minDist = INF;

    for (int v = 0; v < NUM_RESTAURANTS; v++) {
      if (!visited[v] && dist[v] < minDist) {
        minDist = dist[v];
        u = v;
      }
    }

    visited[u] = 1;

    for (int v = 0; v < NUM_RESTAURANTS; v++) {
      if (!visited[v] && graph->edges[u][v] && dist[u] != INF &&
          dist[u] + graph->edges[u][v] < dist[v]) {
        dist[v] = dist[u] + graph->edges[u][v];
      }
    }
  }
}

// Find the index of the closest restaurant to the user
int findClosestRestaurant(double dist[]) {
  double minDist = INF;
  int closestRestaurant = -1;
  for (int i = 0; i < NUM_RESTAURANTS; i++) {
    if (dist[i] < minDist) {
      minDist = dist[i];
      closestRestaurant = i;
    }
  }
  return closestRestaurant;
}



// Find the closest 10 restaurants to a given restaurant
void findClosestRestaurants(MapGraph *graph, int src, double dist[],
                            int closestRestaurants[]) {
  for (int i = 0; i < 10; i++) {
    double minDist = INF;
    int closestRestaurant = -1;
    for (int j = 0; j < NUM_RESTAURANTS; j++) {
      if (dist[j] < minDist && j != src &&
          !alreadyChosen(j, closestRestaurants, i)) {
        minDist = dist[j];
        closestRestaurant = j;
      }
    }
    closestRestaurants[i] = closestRestaurant;
  }
}

int alreadyChosen(int restaurant, int closestRestaurants[], int index) {
    for (int i = 0; i < index; i++) {
        if (closestRestaurants[i] == restaurant) {
            return 1;
        }
    }
    return 0;
}

void printCenteredText(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", text);
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    
    if ((width - len) % 2 != 0) {
        printf(" ");
    }
}
void printCenteredTextint(int text, int width) {
    int len = 2;
    int padding = (width - len) / 2;
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%d", text);
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    if ((width - len) % 2 != 0) {
        printf(" ");
    }
}

void printMenuItem(struct MenuItem item) {
    // Print a separator line
  
    printf(IVORY_BG BLACK_TEXT);
    printf("\n");
    printf(IVORY_BG BLACK_TEXT);

    // Print ID, Name, Price with black text
    printf(EMERALD_TEXT "| " RESET);
   printf(IVORY_BG BLACK_TEXT);
    printCenteredText(item.id, 7);
   printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | " RESET);
   printf(IVORY_BG BLACK_TEXT);
    printCenteredText(item.name, 70);
   printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | " RESET);
   printf(IVORY_BG BLACK_TEXT);
    printCenteredText(item.price, 8);
   printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | " RESET);
   printf(IVORY_BG BLACK_TEXT);
    // Print Type with color based on type
    if (strcmp(item.type, "Veg") == 0) {
        printf( IVORY_BG GREEN_TEXT);
      
        printCenteredText(item.type, 10);
    } else {
        printf(IVORY_BG RED_TEXT);
        printCenteredText(item.type, 10);
    }
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | " RESET);
    printf(IVORY_BG BLACK_TEXT);
  
   printCenteredText(item.quantity, 8);
  printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " |\n" RESET);
}

void displayMenu(int id) {
  // Create a string to hold the filename
  char filename[20];
  // Assuming the CSV files are named "0.csv" to "26.csv"
  sprintf(filename, "data/%d.csv", id);

  // Open the file for reading
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("\033[1;31m");
    printf(
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tError: Unable to open file %s\n\n",
        filename);
    return;
  }
  printf("\n\n");
  printf("\e[1;36m");
  
  print_center_aligned("`````````````");
  print_center_aligned("Menu");
  print_center_aligned("`````````````\n\n");
  char line[100]; // Assuming a maximum line length of 100 characters
  int i = 0;
  printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT "------------------------------------------------------------------------------------------------------------------------\n" RESET);
   printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT "| ");
   printf(IVORY_BG BLACK_TEXT);
  printCenteredText("Id", 7);
   printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT " | ");
   printf(IVORY_BG BLACK_TEXT);
  printCenteredText("Name", 70);
   printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT " | ");
   printf(IVORY_BG BLACK_TEXT);
  printCenteredText("Price", 8);
   printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT " | ");
   printf(IVORY_BG BLACK_TEXT);
  printCenteredText("Type", 10);
   printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT " | ");
   printf(IVORY_BG BLACK_TEXT);
  printCenteredText("Quantity", 8);
   printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT " |\n" RESET);
  printf(IVORY_BG BLACK_TEXT);
  printf(EMERALD_TEXT "--------------------------------------------------------------------------------------------------------------------------\n" RESET);

  while (fgets(line, sizeof(line), file) != NULL) {
    // Parse the line to extract individual items

    if (i > 0) {
      sscanf(line, "%[^,],%[^,],%[^,],%[^,],%s", menu[i].id, menu[i].name,
             menu[i].price, menu[i].type, menu[i].quantity);
      printMenuItem(menu[i]);
    }
    i++;
  }
  

  // Close the file
  fclose(file);
}

void printMenuItemUser(struct MenuItem item) {
    // Print a separator line
    printf(IVORY_BG BLACK_TEXT);
    printf("\n");
    printf(IVORY_BG BLACK_TEXT);

    // Print ID, Name, Price with black text
    printf(EMERALD_TEXT "| " RESET);
    printf(IVORY_BG BLACK_TEXT);
    printCenteredText(item.id, 7);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | " RESET);
    printf(IVORY_BG BLACK_TEXT);
    printCenteredText(item.name, 70);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | " RESET);
    printf(IVORY_BG BLACK_TEXT);
    printCenteredText(item.price, 8);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | " RESET);
    printf(IVORY_BG BLACK_TEXT);

    // Print Type with color based on type
    if (strcmp(item.type, "Veg") == 0) {
        printf(IVORY_BG GREEN_TEXT);
        printCenteredText(item.type, 10);
    } else {
        printf(IVORY_BG RED_TEXT);
        printCenteredText(item.type, 10);
    }
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " |\n" RESET);
}
void displayMenuUser(int id) {
    // Create a string to hold the filename
    char filename[20];
    // Assuming the CSV files are named "data/0.csv" to "data/26.csv"
    sprintf(filename, "data/%d.csv", id);

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\033[1;31m");
        printf(
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tError: Unable to open file %s\n\n",
            filename);
        return;
    }
    printf("\n\n");
    printf("\e[1;36m");

    print_center_aligned("`````````````");
    print_center_aligned("Menu");
    print_center_aligned("`````````````\n\n");
    char line[100]; // Assuming a maximum line length of 100 characters

    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT "------------------------------------------------------------------------------------------------------------------------\n" RESET);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT "| ");
    printf(IVORY_BG BLACK_TEXT);
    printCenteredText("Id", 7);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | ");
    printf(IVORY_BG BLACK_TEXT);
    printCenteredText("Name", 70);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | ");
    printf(IVORY_BG BLACK_TEXT);
    printCenteredText("Price", 8);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " | ");
    printf(IVORY_BG BLACK_TEXT);
    printCenteredText("Type", 10);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT " |\n" RESET);
    printf(IVORY_BG BLACK_TEXT);
    printf(EMERALD_TEXT "------------------------------------------------------------------------------------------------------------------------\n" RESET);

    // Read and print each line of the CSV file
    while (fgets(line, sizeof(line), file)) {
        struct MenuItem item;
        // Assuming the CSV format is: id,name,price,type
        sscanf(line, "%d,%69[^,],%f,%9s", &item.id, item.name, &item.price, item.type);
        printMenuItem(item);
    }

    // Close the file
    fclose(file);
}


void grant_premium_membership(const char *filename, const char target_username[]) {
 FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Unable to open temporary file");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        User user;
        sscanf(line, "%s %s %d %d %s %s %d %lf %d %d", 
               user.username, user.password, 
               &user.address.doorno, &user.address.streetno, 
               user.address.streetname, user.address.city, 
               &user.num_orders, &user.ewallet_money, 
               &user.credit, &user.member);

        if (strcmp(user.username, target_username) == 0) {
            found = 1;
            if (user.ewallet_money >= PREMIUM_MEMBERSHIP_COST) {
                user.ewallet_money -= PREMIUM_MEMBERSHIP_COST;
                user.member = 50;
                printf("\n\t\t\t\t%sPremium membership granted to %s%s.\n\n\t\t\t\t%sRemaining eWallet balance:%s %.2f\n",GOLDD,r, user.username, g,r,user.ewallet_money);
            } else {
                printf("\n\t\t\t\t%sInsufficient funds in eWallet for %s%s.\n",R,r, user.username);
            }
        }

        fprintf(temp, "%s %s %d %d %s %s %d %.2f %d %d\n", 
                user.username, user.password, 
                user.address.doorno, user.address.streetno, 
                user.address.streetname, user.address.city, 
                user.num_orders, user.ewallet_money, 
                user.credit, user.member);
    }

    if (!found) {
        printf("User %s not found.\n", target_username);
    }

    fclose(file);
    fclose(temp);

    // Replace the original file with the updated file
    remove(filename);
    rename("temp.txt", filename);
}


void updateRestaurant(char *filename, int restaurant_id, float new_rating) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Could not open file");
        return;
    }

    Restaurant restaurants[MAX_RESTAURANTS];
    int count = 0;

    // Read the file into the restaurants array
    while (fscanf(file, "%99[^,],%d,%d,%d,%f,%d,%d\n",
                    restaurants[count].name,
                    &restaurants[count].id,
                    &restaurants[count].location.x,
                    &restaurants[count].location.y,
                    &restaurants[count].rating,
                    &restaurants[count].offer,
                    &restaurants[count].order) == 7) {  // Ensure all fields were successfully read
        count++;
        if (count >= MAX_RESTAURANTS) {
            fprintf(stderr, "Too many restaurants in the file\n");
            fclose(file);
            return;
        }
    }

    if (feof(file)) {
        print_center_aligned(B"\t\tThank you for rating!\n"r);
        printf("\n\n\n");
        print_center_aligned(O"\t\t!!!Order Again Soon !!!");
    } else if (ferror(file)) {
        perror("Error reading file");
    }

    // Find the restaurant with the given id and update its rating and order count
    for (int i = 0; i < count; i++) {
        if (restaurants[i].id == restaurant_id) {
            restaurants[i].rating =
                (restaurants[i].rating * restaurants[i].order + new_rating) /
                (restaurants[i].order + 1);
            restaurants[i].order++;
            break;
        }
    }

    // Rewind the file and write the updated data
    rewind(file);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%d,%d,%.2f,%d,%d\n",
                restaurants[i].name,
                restaurants[i].id,
                restaurants[i].location.x,
                restaurants[i].location.y,
                restaurants[i].rating,
                restaurants[i].offer,
                restaurants[i].order);
    }

    fclose(file);
}



void update_user_details(const char *filename, const char target_username[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Unable to open temporary file");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        User user;
        sscanf(line, "%s %s %d %d %s %s %d %lf %d %d", 
               user.username, user.password, 
               &user.address.doorno, &user.address.streetno, 
               user.address.streetname, user.address.city, 
               &user.num_orders, &user.ewallet_money, 
               &user.credit, &user.member);

        if (strcmp(user.username, target_username) == 0) {
            found = 1;
            printf("\033[1;34m");
            // Prompt the user to enter their password
            printf("\n\n\t\t\t\tEnter your password: ");
            printf("\033[0m");
            scanf("%s", user.password);
            printf("\n\n");

            // Prompt the user to enter their address
            printf("\033[1;35m");
            print_center_aligned("Enter your address: ");
            printf("\n\n");
            printf("\033[1;34m");
            printf("\t\t\t\tEnter Your Door No : ");
            printf("\033[0m");
            scanf("%d", &user.address.doorno);
            printf("\n\n");
            printf("\033[1;34m");
            printf("\t\t\t\tEnter your Street No : ");
            printf("\033[0m");
            scanf("%d", &user.address.streetno);
            printf("\n\n");
            printf("\033[1;34m");
            printf("\t\t\t\tEnter your Street Name : ");
            printf("\033[0m");
            scanf("%s", user.address.streetname);
            printf("\n\n");
            printf("\033[1;34m");
            printf("\t\t\t\tEnter your City Name : ");
            printf("\033[0m");
            scanf("%s", user.address.city);
            printf("\n\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sUpdated details for user%s %s.\n",g,r, user.username);
        }

        fprintf(temp, "%s %s %d %d %s %s %d %.2f %d %d\n", 
                user.username, user.password, 
                user.address.doorno, user.address.streetno, 
                user.address.streetname, user.address.city, 
                user.num_orders, user.ewallet_money, 
                user.credit, user.member);
    }

    if (!found) {
        printf("User %s not found.\n", target_username);
    }

    fclose(file);
    fclose(temp);

    // Replace the original file with the updated file
    remove(filename);
    rename("temp.txt", filename);
}


typedef struct {
  int id;
  char name[50];
  int x, y;
  float rating;
  int num_order;
} Driver;

// Function to calculate the distance between two points
float calculate_distance(int x1, int y1, int x2, int y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Function to find the best driver based on location and rating
int find_best_driver(Driver drivers[], int num_drivers, int delivery_x,
                     int delivery_y) {
  int best_driver_index = -1;
  float min_distance = FLT_MAX;

  for (int i = 0; i < num_drivers; i++) {
    float distance =
        calculate_distance(drivers[i].x, drivers[i].y, delivery_x, delivery_y);
    if (distance < min_distance ||
        (distance == min_distance &&
         drivers[i].rating > drivers[best_driver_index].rating)) {
      min_distance = distance;
      best_driver_index = i;
    }
  }

  return best_driver_index;
}

// Function to read drivers from a file
int read_drivers_from_file(Driver drivers[], const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return -1;
  }

  int num_drivers = 0;
  while (fscanf(file, "%d %49s %d %d %f %d", &drivers[num_drivers].id,
                drivers[num_drivers].name, &drivers[num_drivers].x,
                &drivers[num_drivers].y, &drivers[num_drivers].rating, &drivers[num_drivers].num_order) == 6) {
    num_drivers++;
    if (num_drivers >= MAX_DRIVERS) {
      printf("Maximum number of drivers reached.\n");
      break;
    }
  }

  fclose(file);
  return num_drivers;
}

// Function to write updated drivers to a file
void write_drivers_to_file(Driver drivers[], int num_drivers,
                           const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("Error opening file for writing");
    return;
  }

  for (int i = 0; i < num_drivers; i++) {
    fprintf(file, "%d %s %d %d %.1f %d\n", drivers[i].id, drivers[i].name,
            drivers[i].x, drivers[i].y, drivers[i].rating, drivers[i].num_order);
  }

  fclose(file);
}

int find_coordinates_by_id(int id, Restaurant restaurants[],
                           int num_restaurants, int *x, int *y) {
  for (int i = 0; i < num_restaurants; i++) {
    if (restaurants[i].id == id) {
      *x = restaurants[i].location.x;
      *y = restaurants[i].location.y;
      return 1;
    }
  }
  return 0; // Restaurant not found
}

void filterbyType(Restaurant restaurant[]){
   print_center_aligned(g"Veg Restaurants Near you"r);
   printf("\n\n\n");
   printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%-5s          %-40s\n\n", "ID", "Name");
   for(int i=0;i<27;i++){
     if((restaurant[i].id==0)|(restaurant[i].id==2)|(restaurant[i].id==5)|(restaurant[i].id==17)|(restaurant[i].id==20)){
       char str[20];
       strcpy(str,restaurant[i].name+1);
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%s%-5d%s          %-40s\n\n",G ,restaurant[i].id,r,str );
       
     }
     
   
   }





  
}
// Function to read restaurants from a file
int read_restaurants_from_file(Restaurant restaurants[], const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return -1;
  }

  int num_restaurants = 0;
  while (fscanf(file, "%49[^,],%d,%d,%d,%f,%d,%d",
                restaurants[num_restaurants].name,
                &restaurants[num_restaurants].id,
                &restaurants[num_restaurants].location.x,
                &restaurants[num_restaurants].location.y,
                &restaurants[num_restaurants].rating,
                &restaurants[num_restaurants].offer,
                &restaurants[num_restaurants].order) == 7) {

    num_restaurants++;
    if (num_restaurants >= MAX_RESTAURANTS) {
      printf("Maximum number of restaurants reached.\n");
      break;
    }
  }

  fclose(file);
  return num_restaurants;
}

int driverrun(int id, int delivery_x, int delivery_y) {
  Restaurant restaurants[MAX_RESTAURANTS];
  int num_restaurants;

  // Read restaurants from file
  num_restaurants = read_restaurants_from_file(restaurants, RESTAURANT_FILE);
  if (num_restaurants == -1) {
    return 1;
  }
  int x, y;
  // Find the x and y coordinates of the restaurant
  if (find_coordinates_by_id(id, restaurants, num_restaurants, &x, &y)) {
  } else {
    printf(R"\t\t\t\t\t\t\t\t\t\t\t\t\tRestaurant with ID %d not found.\n"r, id);
  }
  Driver drivers[MAX_DRIVERS];
  int num_drivers;

  // Read drivers from file
  num_drivers = read_drivers_from_file(drivers, DRIVER_FILE);
  if (num_drivers == -1) {
    return 1;
  }
  // Find the best driver
  int best_driver_index = find_best_driver(drivers, num_drivers, x, y);

  if (best_driver_index != -1) {
    // Update the driver's coordinates to the delivery location
    drivers[best_driver_index].x = delivery_x;
    drivers[best_driver_index].y = delivery_y;
    drivers[best_driver_index].num_order = drivers[best_driver_index].num_order + 1;

    // Write updated driver details back to the file
    
    float d_rating; 
    printf("\n\n\t\t\t\tYour driver: %s (ID: %d, Rating : %.1f)\n",
           drivers[best_driver_index].name, drivers[best_driver_index].id,
           drivers[best_driver_index].rating);
    printf(G"\n\t\t\t\tRate your delivery partner out of 5 : "r);
    if (scanf("%f", &d_rating) != 1 || d_rating < 1.0 || d_rating > 5.0) {
        printf(R"\t\t\t\t\tInvalid input. Please enter a rating between 1 and 5.\n"r);
        return 1;
    }

    // Update the driver's rating
    drivers[best_driver_index].rating = ((drivers[best_driver_index].rating * (drivers[best_driver_index].num_order - 1) + d_rating) / drivers[best_driver_index].num_order);

    // Optionally increment the number of orders if it represents completed orders post-rating
    // drivers[best_driver_index].num_order++;
    write_drivers_to_file(drivers, num_drivers, DRIVER_FILE);
  } else {
    printf("No available drivers.\n");
  }

  return 0;
}

void read_users(const char *filename, User users[], int *num_users) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  *num_users = 0;
  while (fscanf(file, "%s %s %d %d %s %s %d %lf %d %d",
                users[*num_users].username, users[*num_users].password,
                &users[*num_users].address.doorno,
                &users[*num_users].address.streetno,
                users[*num_users].address.streetname,
                users[*num_users].address.city, &users[*num_users].num_orders,
                &users[*num_users].ewallet_money, &users[*num_users].credit,
                &users[*num_users].member) == 10) {
    (*num_users)++;
  }

  fclose(file);
}

void write_users(const char *filename, User users[], int num_users) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < num_users; i++) {
    fprintf(file, "%s %s %d %d %s %s %d %.2lf %d %d\n", users[i].username,
            users[i].password, users[i].address.doorno,
            users[i].address.streetno, users[i].address.streetname,
            users[i].address.city, users[i].num_orders, users[i].ewallet_money,
            users[i].credit, users[i].member);
  }

  fclose(file);
}

float perform_operations(User users[], int num_users,
                         const char *target_username, double totalbill,
                         int delivery, int offer1,int *flag) {
    
  
    int offer= offer1;
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, target_username) == 0) {
            int choice;
            int discount_applied = 0;
            int c=users[i].credit;
            users[i].credit += (int)(totalbill / 100);
          
            if (users[i].num_orders == 0 && !discount_applied) {
                printf(G"\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tThere is a 50 percent discount for your first order!\n"r);
                totalbill = totalbill * 0.5;
                discount_applied = 1;
            }
            if (users[i].num_orders % 10 == 0 && users[i].num_orders != 0 && !discount_applied) {
                printf(O"\t\t\t\t\t\t\t\t\t\t\t\t\tThere is a 50 percent discount for your %dth order!\n"r, users[i].num_orders);
                totalbill = totalbill * 0.5;
                discount_applied = 1;
            }
            if ((totalbill >= 500) && (offer1 > 0) && !discount_applied) {
                printf(O"\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tYou are Eligible for the %s%d percent offer\n\n  \t\t\t\t\t\t\t\t\t\t\t\tDo you wish to avail it!!\n"r, G,offer1);
                printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tEnter 1 to avail it : ");
                scanf("%d", &choice);
                if (choice == 1) {
                    print_center_aligned(G"Offer Applied"r);
                    totalbill = totalbill - totalbill * (offer / 100.0);
                    discount_applied = 1;
                }
            }

            if (users[i].credit >= 10) {
                printf(B"\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tYou have %d Credit Points !", users[i].credit);
                printf(O"\n\n\n\t\t\t\t\t\t\t\t\t\t\tDo you want to use 10 credits for a discount of 50 rupees? (1/0) : "r);
                scanf("%d", &choice);
                printf("\n\n\n\n");
                if (choice == 1) {
                  
                   *flag=1; 
                   totalbill = totalbill - 50;
                    users[i].credit -= 10;
                }
            }
            users[i].ewallet_money -= totalbill;
            users[i].num_orders += 1;
           if((users[i].credit-c)>0){
            printf(G"\n\n\n\n\t\t\t\t\t\t\t\t\t\tCredit Earned: %d\n"r,
              users[i].credit-c);
           }
            printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\tCredit balance: %d\n",
                   users[i].credit);

            return totalbill;
        }
    }

    // Return -1 if the user is not found
    return -1;
}

float operationrunner(char username[], double totalbill, int delivery,int offer,int *flag) {

  User users[MAX_USERS];
  int num_users;
  char target_username[50];
  float y;
  read_users("data/users.txt", users, &num_users);
  int flag2;

  y = perform_operations(users, num_users, username, totalbill, delivery,offer,&flag2);
  *flag=flag2;
  

  write_users("data/users.txt", users, num_users);

  return y;
}

int checkmember(char username[]){
  User users[MAX_USERS];
  int num_users;
  read_users("data/users.txt", users, &num_users);
  for (int i = 0; i < num_users; i++) {
    if (strcmp(users[i].username, username) == 0) {
        if (users[i].member > 0) {
              users[i].member -= 1;
              print_center_aligned(G"Free Delivery Due to Membership"r);

              if (users[i].member == 0) {
                  printf(R"\t\t\t\t\t\t\tYour Premium Membership has expired.\n"r);
              }
          return 1;
          }
        }
    }
  return 0;
}

int passwordcheck(char username[]){
    User users[MAX_USERS];
    int num_users;
    read_users("data/users.txt", users, &num_users);
    for (int i = 0; i < num_users; i++) {
      if (strcmp(users[i].username, username) == 0) {
          char password[50];
          printf(B"\t\t\t\tEnter password : "r);
          scanf("%s",password);
          if (strcmp(users[i].password, password) == 0) {
            return 1;
          }
      }
    }
    return 0;
}

void updateOffer(const char *username) {
    FILE *file = fopen("data/restaurant.txt", "r+");
    if (!file) {
        perror(R"\t\t\t\tFailed to open file");
        exit(EXIT_FAILURE);
    }

    struct Restaurant1 restaurant;
    char line[MAX_LINE_LENGTH];
    long pos;
    int found = 0;
    int newOffer;

    // Prompt user for new offer
    printf(B"\t\t\t\tEnter the new offer for '%s': "r, username);
    scanf("%d", &newOffer);

    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character from the line
        line[strcspn(line, "\n")] = 0;

        // Parse the line into struct members
        sscanf(line, "%[^,],%d,%d,%d,%f,%d,%d", 
               restaurant.name, &restaurant.id, &restaurant.col1,
               &restaurant.col2, &restaurant.col3, &restaurant.col4,
               &restaurant.col5);

        // Compare the username with restaurant name
        if (strcmp(restaurant.name, username) == 0) {
            restaurant.col4 = newOffer;

            // Move the file pointer back to the start of the line
            pos = ftell(file);
            fseek(file, pos - strlen(line) - 1, SEEK_SET); // -1 to also overwrite newline

            // Write the updated line back to the file
            fprintf(file, "%s,%d,%d,%d,%.2f,%d,%d\n",
                    restaurant.name, restaurant.id, restaurant.col1,
                    restaurant.col2, restaurant.col3, restaurant.col4,
                    restaurant.col5);
            fflush(file); // Ensure the buffer is written to the file
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf(R"\t\t\t\tRestaurant '%s' not found in the file.\n"r, username);
    } else {
        printf(G"\t\t\t\tOffer for '%s' updated successfully.\n"r, username);
    }
}

void generateBill(char username[], char *password, struct MenuItem menu[],
                  struct CartItem cart[], int cartItemCount, int itemCount,
                  int d, int id, int offer, int x, int y) {
  float totalBill = 0.0;
  float bill = 0;
  printf("\n\n\n\n\n\n\n\n\n");
  print_center_aligned(EMERALD_TEXT"\t\t\t\t\tItem Total:\n\n\n\n"r);
  printf("\t\t\t\t\t\t\t\t\t\t%-50s        %-15s  %-10s       %-7s\n", G"Name",g"Price", G"Quantity", g"SubTotal\n"r);
  for (int i = 0; i < cartItemCount; i++) {
    for (int j = 0; j < itemCount; j++) {
      if (strcmp(cart[i].id, menu[j].id) == 0) {
        float price = atof(menu[j].price);
        float total = price * cart[i].quantity;
        printf("\t\t\t\t\t\t\t\t\t\t%-50s%-15s%-10d   %-7.2f\n\n", cart[i].name, menu[j].price,
               cart[i].quantity, total);
        totalBill += total;
        break;
      }
    }
  }
  int delivery = d * 10;
  // Calculate and display GST
  float gstRate = 0.18; // Assuming GST rate is 18%
  float gstAmount = totalBill * gstRate;
  int total=totalBill;
  float finalbill;
  int flag;
  finalbill = operationrunner(username, totalBill, delivery,offer,&flag);
  int creditusage;
  if (flag==1){creditusage=50;}
  else{creditusage=0;}
  offer=((totalBill-finalbill-creditusage)/totalBill)*100;
  
  if (checkmember(username)==1)
  {delivery=0;}
  printf("\n\n\n\n");
    print_center_aligned("\t\t          Bill:\n");
    printf("\t\t\t\t\t\t\t\t\t\tSub Total                                      :                   ₹%-200.2f\n",totalBill);
    printf("\t\t\t\t\t\t\t\t\t\t%d percent offer applied  on the bill          :                 - ""₹%-200.2f\n ",offer,totalBill-finalbill-creditusage);
    printf("\t\t\t\t\t\t\t\t\t\tCredits  Used (10 credits)                     :                 - ₹%-200d\n",creditusage);

    printf("\t\t\t\t\t\t\t\t\t\tGST  (18 percent)                              :                   ₹%-200.2f\n",gstAmount);
    printf("\t\t\t\t\t\t\t\t\t\tDelivery charges                               :                   ₹%-200.2d\n",delivery);
    printf( "\t\t\t\t\t\t\t\t\t\tTotal Bill (including GST and delivery)        :                   ₹%-200.2f\n",finalbill+gstAmount+delivery);
   printf("\n\n\n\n\n");
 
  label20:
  printf(V"\t\t\t\tDo you want to Check out ? (1/0)  :  "r);
  int choice;
  scanf("%d",&choice);
  printf("\n\n\n\n");
  if (choice==1){
      print_center_aligned(O" E-Wallet Verification ");
      if (passwordcheck(username)!=1){
        print_center_aligned(R"Incorrect Password"r);
        goto label20;
      }
  }
  else{
    print_center_aligned("Do you Want to quit (1/0) ");
    int choice;
    scanf("%d",&choice);
    if (choice==1){
      print_center_aligned("Come Back Sooner");
      exit(0);
    }
    else{
      
    }
    
    
  }
  printf("\n\n");
  print_center_aligned(g"\t\tPayment Sucessfull!!\n\n"r);
  print_center_aligned(g"\t\tThank you for ordering from us!\n\n"r);
  
  driverrun(id, x, y);
  printf(O"\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tYour order will reach you in aproximately %s%.0lf minutes"r,g,d*2.5+15);
  printf(V"\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tJust Relax and Wait\n\n\n\n"r);
  FILE *file = fopen("data/orderhistory.txt", "a");
  if (file == NULL) {
    printf(R"\t\t\t\t\t\t\t\t\t\t\t\tError opening file!\n");
    return;
  }
  fprintf(file, "\n");
  for (int i = 0; i < cartItemCount; i++) {
    for (int q = 0; q < cart[i].quantity; q++) {
      fprintf(file, "%s", cart[i].name);
      if (i < cartItemCount - 1 || q < cart[i].quantity - 1) {
        fprintf(file, ",");
      }
    }
  }
  fclose(file);
  int rating;
  printf(G"\n\n\t\t\t\t\tRate your food out of 5 :"r);
  scanf("%d",&rating);
  updateRestaurant("data/restaurant.txt", id, rating);

  // Update user information based on the generated bill
}

typedef struct {
  char name[50];
  int count;
} MenuItems;

// Define transaction structure
typedef struct {
  MenuItems items[MAX_ITEMS];
  int count;
} Order;

// Function to read transactions from file
int read_orders(const char *filename, Order *orders, int max_orders) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf(R"\t\t\t\tError opening file %s\n", filename);
    return 0;

  }

  char line[MAX_LINE_LENGTH];
  int order_count = 0;

  while (fgets(line, sizeof(line), file)) {
    char *token = strtok(line, ",");
    int item_count = 0;

    while (token != NULL) {
      // Check if item already exists in order
      int existing_item_index = -1;
      for (int i = 0; i < item_count; i++) {
        if (strcmp(orders[order_count].items[i].name, token) == 0) {
          existing_item_index = i;
          break;
        }
      }

      // Increment count if item already exists, otherwise add new item
      if (existing_item_index != -1) {
        orders[order_count].items[existing_item_index].count++;
      } else {
        strcpy(orders[order_count].items[item_count].name, token);
        orders[order_count].items[item_count].count = 1;
        item_count++;
      }

      token = strtok(NULL, ",");
    }

    orders[order_count].count = item_count;
    order_count++;

    if (order_count >= max_orders) {
      break;
    }
  }

  fclose(file);
  return order_count;
}

void trim_whitespace(char *str) {
  char *start = str;
  char *end;

  // Trim leading space
  while (isspace((unsigned char)*start))
    start++;

  // If all spaces or empty, return empty string
  if (*start == 0) {
    *str = 0;
    return;
  }

  // Trim trailing space
  end = start + strlen(start) - 1;
  while (end > start && isspace((unsigned char)*end))
    end--;

  // Write new null terminator
  *(end + 1) = 0;

  // Move trimmed string to the beginning of str
  if (start > str) {
    memmove(str, start,
            end - start + 2); // +1 for null terminator, +1 for inclusive range
  }
}

// Function to find frequent itemsets containing the given item

void print_suggested_item_id(const char item_name[], struct MenuItem menu[],
                             int menu_size) {
  char trimmed_item_name[MAX_NAME_LENGTH];
  strcpy(trimmed_item_name, item_name);
  trim_whitespace(trimmed_item_name);
  for (int i = 0; i < menu_size; i++) {
    char trimmed_menu_name[MAX_NAME_LENGTH];
    strcpy(trimmed_menu_name, menu[i].name);
    trim_whitespace(trimmed_menu_name);
    int cmp_result = strcmp(trimmed_menu_name, trimmed_item_name);
    if (cmp_result == 0) {
      
      printf("\n\t\t\t\t\t\t%sItem: %s, %sID: %s\n",O, menu[i].name,G,menu[i].id);
      return;
    }
  }
  printf(R"\n\t\t\t\t\t\t\t\t\Item: %s not found in menu.\n"r, item_name);
}

void find_frequent_itemsets(Order *orders, int order_count,
                            const char *item_name, int min_support,
                            struct MenuItem menu[]) {
  // Find the order containing the given item
  char trimmed_item_name[MAX_NAME_LENGTH];
  strcpy(trimmed_item_name, item_name);
  trim_whitespace(trimmed_item_name);
  int item_order_index = -1;
  for (int i = 0; i < order_count; i++) {
    for (int j = 0; j < orders[i].count; j++) {
      char trimmed_menu_name[MAX_NAME_LENGTH];
      strcpy(trimmed_menu_name, orders[i].items[j].name);
      trim_whitespace(trimmed_menu_name);
      if (strcmp(trimmed_item_name, trimmed_menu_name) == 0) {
        item_order_index = i;
        break;
      }
    }
    if (item_order_index != -1) {
      break;
    }
  }

  if (item_order_index == -1) {
    print_center_aligned(R"Item not found in orders.\n");
    return;
  }

  // Print suggested items for the given item
  printf("\t\t\t\tSuggested items for %s:\n", trimmed_item_name);
  for (int i = 0; i < orders[item_order_index].count; i++) {
    char trimmed_reccomend_name[MAX_NAME_LENGTH];
    strcpy(trimmed_reccomend_name, orders[item_order_index].items[i].name);
    trim_whitespace(trimmed_reccomend_name);
    if (strcmp(trimmed_reccomend_name, trimmed_item_name) != 0) {
      print_suggested_item_id(trimmed_reccomend_name, menu, 20);
    }
  }
  printf("\n");
}





void deleteItem(int id, char id1[10]) {
    char filename[20];
    char tempFilename[25];
    sprintf(filename, "data/%d.csv", id);
    sprintf(tempFilename, "data/%d_temp.csv", id);

    // Open the original file in read mode
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct MenuItem items[MAX_ITEMS];
    char line[MAX_LINE_LENGTH];
    int itemCount = 0;

    // Read file content into an array of structures
    while (fgets(line, sizeof(line), file) && itemCount < MAX_ITEMS) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        int fieldsRead = sscanf(line, "%9[^,],%49[^,],%9[^,],%49[^,],%9[^\n]", 
                                items[itemCount].id, items[itemCount].name, 
                                items[itemCount].price, items[itemCount].type, 
                                items[itemCount].quantity);
        if (fieldsRead == 5) {
            itemCount++;
        }
    }
    fclose(file);

    // Find and delete the specified item
    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(items[i].id, id1) == 0) {
            found = 1;
            for (int j = i; j < itemCount - 1; j++) {
                items[j] = items[j + 1];
            }
            itemCount--;
            break;
        }
    }

    if (!found) {
        printf("Item with ID %s not found.\n", id1);
        return;
    }

    // Open a temporary file in write mode
    FILE *tempFile = fopen(tempFilename, "w");
    if (!tempFile) {
        perror("Failed to open temporary file for writing");
        exit(EXIT_FAILURE);
    }

    // Write the modified array back to the temporary file
    for (int i = 0; i < itemCount; i++) {
        fprintf(tempFile, "%s,%s,%s,%s,%s\n", items[i].id, items[i].name, 
                items[i].price, items[i].type, items[i].quantity);
    }
    fclose(tempFile);

    // Replace the original file with the temporary file
    if (remove(filename) != 0) {
        perror("Failed to remove the original file");
        exit(EXIT_FAILURE);
    }
    if (rename(tempFilename, filename) != 0) {
        perror("Failed to rename the temporary file");
        exit(EXIT_FAILURE);
    }

    printf("Item with ID %s deleted successfully.\n", id1);
}




void updateQuantity(int id, char id1[10], char *newQuantity) {
    char filename[20];
    sprintf(filename, "data/%d.csv", id);

    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct MenuItem item;
    char line[MAX_LINE_LENGTH];
    long pos;
    int found = 0;

    while ((pos = ftell(file)) != -1 && fgets(line, sizeof(line), file)) {
        // Remove the newline character from the line
        line[strcspn(line, "\n")] = 0;

        sscanf(line, "%9[^,],%49[^,],%9[^,],%49[^,],%3[^\n]", 
               item.id, item.name, item.price, item.type, item.quantity);

        if (strcmp(item.id, id1) == 0) {
            // Update the quantity
            strcpy(item.quantity, newQuantity);

            // Move the file pointer back to the start of the line
            fseek(file, pos, SEEK_SET);

            // Write the updated line back to the file
            fprintf(file, "%s,%s,%s,%s,%s", item.id, item.name, item.price,
                    item.type, item.quantity);
            // Write the newline character
            fprintf(file, "\n");
            fflush(file); // Ensure the buffer is written to the file
            found = 1;
            printf("\n\n\n\n");
            break;
        }
    }

    if (!found) {
        printf("\n\n");
        printf(GREENN);
        print_center_aligned("Item ID not found");
        printf(RESET);
    }

    fclose(file);
}

void updatePrice(int id, char id1[10], char *newPrice) {
    char filename[20];
    sprintf(filename, "data/%d.csv", id);

    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct MenuItem item;
    char line[MAX_LINE_LENGTH];
    long pos;
    int found = 0;

    while ((pos = ftell(file)) != -1 && fgets(line, sizeof(line), file)) {
        // Remove the newline character from the line
        line[strcspn(line, "\n")] = 0;

        sscanf(line, "%9[^,],%49[^,],%9[^,],%49[^,],%3[^\n]", 
               item.id, item.name, item.price, item.type, item.quantity);

        if (strcmp(item.id, id1) == 0) {
            // Update the quantity
            strcpy(item.price, newPrice);

            // Move the file pointer back to the start of the line
            fseek(file, pos, SEEK_SET);

            // Write the updated line back to the file
            fprintf(file, "%s,%s,%s,%s,%s", item.id, item.name, item.price,
                    item.type, item.quantity);
            // Write the newline character
            fprintf(file, "\n");
            fflush(file); // Ensure the buffer is written to the file
            found = 1;

            printf("\n\n");
            printf(GREENN);
            print_center_aligned("Quantity Updated Successfully");
            printf(RESET);
            break;
        }
    }

    if (!found) {
        printf("\n\n");
        printf(GREENN);
        print_center_aligned("Item ID not found");
        printf(RESET);
    }

    fclose(file);
}


// Function to manage the cart

void manageCart(char username[], char password[], struct MenuItem menu[],
                int itemCount, int deliveryCost, int id, int offer, int x,
                int y) {
  struct CartItem cart[MAX_ITEMS];
  int cartItemCount = 0;
  char choice;

  do {
  label10:
  printf("\n\n");
    print_center_aligned("What Do you Want to Do : \n");
    print_center_aligned(Y"Add (A)\n"); 
    print_center_aligned(R"Delete (D)\n"); 
    print_center_aligned(g"Finish (F) managing the cart? ");
    printf(m"\n\t\t\t\tEnter Your Choice : ");
    printf(r);    
    scanf(" %c", &choice);

    if (choice == 'A' || choice == 'a') {
      printf(B"\n\n\t\t\t\tEnter the ID of the Item to Add to Cart : "r);
      char itemId[5];
      scanf("%s", itemId);

      int found = 0;
      for (int i = 0; i <= itemCount; i++) {
        if (strcmp(menu[i].id, itemId) == 0) {
          // Item found, add to cart
          strcpy(cart[cartItemCount].id, itemId);
          strcpy(cart[cartItemCount].name, menu[i].name);
          printf(B"\n\t\t\t\tEnter the quantity of %s%s  :"r ,V,menu[i].name);
          int availableQuantity = atoi(menu[i].quantity);
          int qty;
          scanf("%d", &qty);
          if (qty <= availableQuantity) {
            char newQuantity[5];
            cart[cartItemCount].quantity = qty;
            sprintf(newQuantity, "%d", availableQuantity - qty);

            updateQuantity(id, itemId, newQuantity);
          } else {
            printf(B"\n\n\t\t\t\t\t\t\t\t\t\tSorry only %s%d%s %s available\n"r,R,availableQuantity,V,
                   menu[i].name);
            goto label10;
          }
          Order orders[MAX_ITEMS];
          int order_count =
              read_orders("data/orderhistory.txt", orders, MAX_ITEMS);

          char item_name[50];
          strcpy(item_name, menu[i].name);
          find_frequent_itemsets(orders, order_count, item_name, MIN_SUPPORT,
                                 menu);
          cartItemCount++;
          found = 1;
          break;
        }
      }
      if (!found) {
        printf("\n");
        print_center_aligned(R"Item not Found in the Menu!\n\n");
      }
    } else if (choice == 'D' || choice == 'd') {
      printf(B"\n\nt\t\t\tEnter the ID of the Item to Delete : "r);
      char itemId[5];
      scanf("%s", itemId);

      int found = 0;
      for (int i = 0; i < cartItemCount; i++) {
        if (strcmp(cart[i].id, itemId) == 0) {
          // Item found, ask for deletion type
          printf(B"\n\n\t\t\t\tDelete by Quantity (Q) or Completely (C)? (Q/C) : "r);
          char delChoice;
          scanf(" %c", &delChoice);

          if (delChoice == 'Q' || delChoice == 'q') {
            printf(B"\n\n\t\t\t\tEnter the quantity to Delete : "r);
            int quantityToDelete;
            scanf("%d", &quantityToDelete);

            if (quantityToDelete < cart[i].quantity) {
              cart[i].quantity -= quantityToDelete;
            } else {
              // Remove the entire item from the cart
              for (int j = i; j < cartItemCount - 1; j++) {
                strcpy(cart[j].id, cart[j + 1].id);
                strcpy(cart[j].name, cart[j + 1].name);
                cart[j].quantity = cart[j + 1].quantity;
              }
              cartItemCount--;
            }
          } else if (delChoice == 'C' || delChoice == 'c') {
            // Remove the entire item from the cart
            for (int j = i; j < cartItemCount - 1; j++) {
              strcpy(cart[j].id, cart[j + 1].id);
              strcpy(cart[j].name, cart[j + 1].name);
              cart[j].quantity = cart[j + 1].quantity;
            }
            cartItemCount--;
          } else {
            printf("\n");
            print_center_aligned(R"Invalid choice!\n"r);
          }
          found = 1;
          break;
        }
      }
      if (!found) {
        print_center_aligned(R"Item not found in the Cart!\n"r);
      }
    } else if (choice == 'F' || choice == 'f') {
      break;
    } else {
      print_center_aligned(R"Invalid choice!\n"r);
    }

  } while (1);
  if (cartItemCount==0){print_center_aligned(R"Your Cart is Empty\n"r);
                       goto label10;}
  // Display the items in the cart
  printf("\n\n\n\n\n\n\n\n");
  print_center_aligned(Y"\t\t\t|***********|");
  print_center_aligned(Y"\t\t\t\t|Cart Items:|"r);
  print_center_aligned(Y"\t\t\t\t|***********|\n\n");
  printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%-50s|%s\n", G"Name", G"Quantity"r); // Header
  for (int i = 0; i < cartItemCount; i++) {
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t%-50s|%-3d\n", cart[i].name, cart[i].quantity);
  }

  // Generate bill
  generateBill(username, password, menu, cart, cartItemCount, itemCount,
               deliveryCost, id, offer, x, y);
}

struct RestaurantItem {
  char name[MAX_NAME_LENGTH];
  char price[10];
  char type[MAX_NAME_LENGTH];
  char id[10];
  char quantity[3];
};

// Function to get the maximum item ID from the menu file
int getMaxItemId(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return 0; // If the file doesn't exist, return 0 as the maximum item ID
  }

  int maxId = 0;
  char line[100];
  while (fgets(line, sizeof(line), file) != NULL) {
    char *token = strtok(line, ",");
    int itemId = atoi(token);
    if (itemId > maxId) {
      maxId = itemId;
    }
  }

  fclose(file);
  return maxId;
}

// Function to add a new item to the menu
void addNewItemToMenu(int restaurantID, const struct RestaurantItem newItem) {
  // Create a string to hold the filename
  char filename[FILENAME_MAX_LENGTH];
  // Assuming the CSV files are named "0.csv" to "26.csv"
  sprintf(filename, "data/%d.csv", restaurantID);

  // Open the file for appending
  FILE *file = fopen(filename, "a");
  if (file == NULL) {
    printf("\033[1;31m");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\Error: Unable to open "
           "file %s\n",
           filename);
    return;
  }

  // Write the new item details to the file with the next available ID
  fprintf(file, "%d,%s,%s,%s,%s\n", getMaxItemId(filename) + 1, newItem.name,
          newItem.price, newItem.type, newItem.quantity);

  // Close the file
  fclose(file);
  printf("\033[1;32m");
  print_center_aligned("New item added to the menu successfully!\n");
  printf("\033[0m");
}

struct Restaurant {
  char name[50];
  int id;
  int x_coord;
  int y_coord;
  float rating;
};

int login(char *username, char *password) {
  FILE *userFile = fopen("data/restaurant_users.txt", "r");
  if (userFile == NULL) {
    printf("File not found.\n");
    return 0;
  }

  Restaurant restaurant;
  char fileUsername[50], filePassword[50];
  while (fscanf(userFile, "%s %s\n", fileUsername, filePassword) == 2) {
    if (strcmp(fileUsername, username) == 0 &&
        strcmp(filePassword, password) == 0) {
      fclose(userFile);
      return 1;
    }
  }

  fclose(userFile);
  return 0;
}

int findRestaurant(char *username, Restaurant *restaurant) {
  FILE *restaurantFile = fopen("data/restaurant.txt", "r");
  if (restaurantFile == NULL) {
    printf("File not found.\n");
    return 0;
  }

  while (fscanf(restaurantFile, "%[^,],%d,%d,%d,%f,%d,%d\n", restaurant->name,
                &restaurant->id, &restaurant->location.x,
                &restaurant->location.y, &restaurant->rating,
                &restaurant->offer, &restaurant->order) == 7) {
    if (strcmp(restaurant->name, username) == 0) {
      fclose(restaurantFile);
      return 1;
    }
  }

  fclose(restaurantFile);
  return 0;
}
double userToRestaurantDistances[NUM_RESTAURANTS];

void displayRestaurantDetails(const Restaurant *restaurant) {

  printf("\033[38;5;208m");
  print_center_aligned("Restaurant Details:\n\n");

  printf(ANSI_COLOR_ORANGE
         "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tName              :   %s%s\n",
         ANSI_COLOR_RESET, restaurant->name);
  printf(ANSI_COLOR_ORANGE
         "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tID                :   %s%d\n",
         ANSI_COLOR_RESET, restaurant->id);
  printf(ANSI_COLOR_ORANGE
         "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tX Coord           :   %s%d\n",
         ANSI_COLOR_RESET, restaurant->location.x);
  printf(ANSI_COLOR_ORANGE
         "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tY Coord           :   %s%d\n",
         ANSI_COLOR_RESET, restaurant->location.y);
  printf(ANSI_COLOR_ORANGE
         "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tRating            :   %s%.1f\n",
         ANSI_COLOR_RESET, restaurant->rating);
  printf(ANSI_COLOR_ORANGE
         "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tOffer             :   %s%d\n",
         ANSI_COLOR_RESET, restaurant->offer);
  printf(ANSI_COLOR_ORANGE
         "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tNumber of Orders  :   %s%d\n",
         ANSI_COLOR_RESET, restaurant->order);
}
double calculate_score(double distance, float rating, int offer) {
    return 3.0 * distance + 2.0 * rating + 1.5 * offer;
}
// Print a separator line

  




void printCenteredTextInt(int value, int width) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", value);
    printCenteredText(buffer, width);
}

void printCenteredTextFloat(float value, int width) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.1f", value);
    printCenteredText(buffer, width);
}
 
closestRestaurants[NUM_RESTAURANTS];
void sortAndDisplayRestaurants1(Restaurant restaurants[], int numRestaurants,
                                int closestRestaurants[]) {
  // Sort restaurants based on distance, rating, and offer
   for (int i = 0; i < numRestaurants - 1; i++) {
          for (int j = 0; j < numRestaurants - i - 1; j++) {
              double distance1 = userToRestaurantDistances[closestRestaurants[restaurants[j].id - 1] - 1];
              double distance2 = userToRestaurantDistances[closestRestaurants[restaurants[j + 1].id - 1] - 1];

              double score1 = calculate_score(distance1, restaurants[j].rating, restaurants[j].offer);
              double score2 = calculate_score(distance2, restaurants[j + 1].rating, restaurants[j + 1].offer);

              if (score1 > score2) {
                  Restaurant temp = restaurants[j];
                  restaurants[j] = restaurants[j + 1];
                  restaurants[j + 1] = temp;
              }
          }
      }
  

  
  // Display sorted restaurants
  printf(O);
  printf("\n\n");
  print_center_aligned("----------------------\n");
  printf(Y);
  print_center_aligned("|IN THE SPOTLIGHT!!!!|");
  printf(O);
  print_center_aligned("----------------------\n");
  printf(r);
  printf("\t\t\t\t\t\t\t\tID");
  printf("\t\tRestaurant Name\t\t\t");
  printf("\t\t\tRating ");
  printf("\t\t\tOFFER\n\n");
 
  for (int i = numRestaurants - 1; i > 14; i--) {
   
    char sub_string[30]; 
    strcpy(sub_string, restaurants[i].name + 1);
    
      printf("\t\t\t\t\t\t\t\t%s%-5d%s\t%-30s\t\t\x1b[38;5;220m%-5.2f%s\t\t\t\x1b[38;5;34m %-5d\n\n",
             V,restaurants[i].id, r,sub_string, restaurants[i].rating, RESET, restaurants[i].offer);
     
      printf(r);
    
    
      
  }

}

int main() {
  int offer;
  Coordinate userCoord;
  char id1[100];
  char newQuantity[100];
  char newPrice[100];
  
  Restaurant restaurant1;
  int choice;
  char username[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  struct RestaurantItem newItem;

  const char *message = "Welcome to Food Delivery System";
  int len = strlen(message);
  int padding = (TERMINAL_WIDTH - len) / 2;

  // ANSI escape code for bold red text
  printf("\033[1;31m");

  // Print leading spaces for center alignment
  for (int i = 0; i < padding; i++) {
    printf(" ");
  }

  // Print the message
  printf("%s\n", message);

  // Reset to default color
  printf("\033[0m");

label3:
  printf("\033[1m");
  printf("\n\n\n");

label1:
  // Print each line center-aligned
  print_center_aligned("1. Login           ");
  print_center_aligned("2. Create Account  ");
  print_center_aligned("3. Restaurant Login");

  // ANSI escape code for bold green text
  printf("\033[1;32m");
  printf("\n\n");
  // Print the left-aligned line
  printf("\t\t\t\tEnter your choice : ");

  // Reset to default style
  printf("\033[0m");

  // Reset to default style
  printf("\033[0m");
  scanf("%d", &choice);

  if (choice == 1) {

    // Prompt the user to enter their username

    // ANSI escape code for bold blue text
    printf("\033[1;34m");
    printf("\n\n");
    printf("\033[1;31m");
    printf("\033[1;31m");
    print_center_aligned("Verify User Credentials\n\n");
    // Print the left-aligned line in bold blue
    printf("\033[1;34m");
    printf("\t\t\t\tEnter Your Username : ");
    printf("\033[0m");
    scanf("%s", username);
    printf("\n\n");
    // ANSI escape code for bold blue text
    printf("\033[1;34m");

    // Prompt the user to enter their password
    printf("\t\t\t\tEnter Your Password : ");
    printf("\033[0m");
    scanf("%s", password);
    printf("\n\n");

    // Validate the entered username and password
    User *user = validate_login(username, password);
    if (user != NULL) {
      printf("\033[1;32m");
      print_center_aligned("Login Successful!\n");
      // ANSI escape code for bold magenta text
      const char *magenta_color_code = "\033[1;35m";
      char *yellow_bg = "\033[43m";

      const char *royalblue = "\033[38;5;63m";
      // ANSI escape code to reset text color to default
      const char *reset_color_code = "\033[0m";

      // Print the user information with specified color formatting
      // Print the user information with specified color formatting
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sUsername           :    %s%s\n\n\n",
             magenta_color_code, reset_color_code, user->username);
      printf("\033[1;35m");
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\tAddress                       \n\n");
      printf("%s", reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t        "
             "╔═══════════════════════════════════════════════════════╗%s\n",
             reset_color_code);

      // Print the address details
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sDoor NO          |     %s%-20d      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.doorno,
             reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sStreet NO        |     %s%-20d      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.streetno,
             reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sStreet Name      |     %s%-20s      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.streetname,
             reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sCity             |     %s%-20s      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.city, reset_color_code);

      printf("\t\t\t\t\t\t\t\t\t\t\t        "
             "╚═══════════════════════════════════════════════════════╝%s\n",
             reset_color_code);

      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sNumber of Orders   :    %s%d\n",
             magenta_color_code, reset_color_code, user->num_orders);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%seWallet Money      :    %s%.2f\n",
             magenta_color_code, reset_color_code, user->ewallet_money);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sCredits            :    %s%d\n",
             magenta_color_code, reset_color_code, user->credit);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sMembership Status  :    %s%d\n",
             magenta_color_code, reset_color_code, user->member);
      userCoord.x = user->address.doorno;
      userCoord.y = user->address.streetno;
      free(user);
    } else {
      // ANSI escape code for bold red text
      printf("\033[1;31m");
      print_center_aligned(
          "Login failed !!. Invalid username or password.\n\n");
      printf("\033[0m");
      goto label1;
      return 0;
    }
  } else if (choice == 2) {
  
    create_account();
    label2:
    // Prompt the user to enter their username
    printf("\033[38;5;208m");
  
    printf("\033[0m");
    // ANSI escape code for bold blue text
    printf("\033[1;34m");
    printf("\n\n");
    printf("\033[1;31m");
    printf("\033[1;31m");
    print_center_aligned("Verify User Credentials\n\n");
    // Print the left-aligned line in bold blue
    printf("\033[1;34m");
    printf("\t\t\t\tEnter Your Username : ");
    printf("\033[0m");
    scanf("%s", username);
    printf("\n\n");
    // ANSI escape code for bold blue text
    printf("\033[1;34m");

    // Prompt the user to enter their password
    printf("\t\t\t\tEnter Your Password : ");
    printf("\033[0m");
    scanf("%s", password);
    printf("\n\n");

    // Validate the entered username and password
    User *user = validate_login(username, password);
    if (user != NULL) {
      printf("\033[1;32m");
      print_center_aligned("Login Successful!\n");
      // ANSI escape code for bold magenta text
      const char *magenta_color_code = "\033[1;35m";
      const char *royalblue = "\033[38;5;63m";
      // ANSI escape code to reset text color to default
      const char *reset_color_code = "\033[0m";
      char *yellow_bg = "\033[43m";

      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sUsername           :    %s%s\n\n\n",
             magenta_color_code, reset_color_code, user->username);
      printf("\033[1;35m");
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\tAddress                       \n\n");
      printf("%s", reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t        "
             "╔═══════════════════════════════════════════════════════╗%s\n",
             reset_color_code);

      // Print the address details
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sDoor NO          |     %s%-20d      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.doorno,
             reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sStreet NO        |     %s%-20d      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.streetno,
             reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sStreet Name      |     %s%-20s      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.streetname,
             reset_color_code);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t║%sCity             |     %s%-20s      "
             "      ║%s\n",
             royalblue, reset_color_code, user->address.city, reset_color_code);

      printf("\t\t\t\t\t\t\t\t\t\t\t        "
             "╚═══════════════════════════════════════════════════════╝%s\n",
             reset_color_code);

      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sNumber of Orders   :    %s%d\n",
             magenta_color_code, reset_color_code, user->num_orders);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%seWallet Money      :    %s%.2f\n",
             magenta_color_code, reset_color_code, user->ewallet_money);
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sCredits            :    %s%d\n",
             magenta_color_code, reset_color_code, user->credit);
      
      printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sMembership Status  :    %s%d\n",
             magenta_color_code, reset_color_code, user->member);
      userCoord.x = user->address.doorno;
      userCoord.y = user->address.streetno;
      free(user);
    } else {
      // ANSI escape code for bold red text
      printf("\033[1;31m");
      print_center_aligned(
          "Login failed !!. Invalid username or password.\n\n");
      printf("\033[0m");
      goto label2;
    }
  } else if (choice == 3) {
  label4:
    printf("\033[1;31m");
    print_center_aligned("Verify Your Credentials\n\n");
    printf("\033[1;34m");
    printf("\t\t\t\tEnter Username  : ");
    printf("\033[0m");
    scanf("%s", username);
    printf("\033[1;34m");
    printf("\n\n\t\t\t\tEnter password :  ");
    printf("\033[0m");
    scanf("%s", password);

    if (!login(username, password)) {
      printf("\033[1;31m");
      print_center_aligned(R"Login failed !!. Invalid username or password.\n\n"r);
      printf("\033[0m");
      goto label4;
    }

    if (!findRestaurant(username, &restaurant1)) {
      printf("\033[1;31m");
      print_center_aligned("\n\nRestaurant not found.\nn");
      printf("\033[0m");
      goto label4;
    }
    printf("\033[1;32m");
    print_center_aligned("Login Sucessfull\n\n");
    printf("\033[0m");
    displayRestaurantDetails(&restaurant1);

    int choice1;
   
    do {
      printf("\n\n");
      printf("\e[1;36m");
      print_center_aligned("\tMenu \n");
      printf("\033[0m");
      print_center_aligned("1. Add a new item          \n");
      print_center_aligned("2. Update quantity of items\n");
      print_center_aligned("3. Update Offer            \n");
      print_center_aligned("4. Update Price            \n");
      print_center_aligned("5. Delete an item          \n");
      print_center_aligned("6. Exit                    \n");
      printf("\033[1;34m");
      printf("\t\t\t\tEnter your choice  : ");
      printf("\033[0m");
      scanf("%d", &choice1);

      switch (choice1) {
      case 1:
        // Get details of the new item from the user
        printf("\033[1;34m");
        printf("\n\t\t\t\tEnter name of the item: ");
        printf("\033[0m");
        scanf(" %[^\n]", newItem.name);
        printf("\033[1;34m");
        printf("\n\t\t\t\tEnter price of the item: ");
        printf("\033[0m");
        scanf("%s", newItem.price);
        printf("\033[1;34m");
        printf("\n\t\t\t\tEnter type of the item: ");
        printf("\033[0m");
        scanf(" %[^\n]", newItem.type);
        printf("\033[1;34m");
        while (getchar() != '\n');
        printf("\n\t\t\t\tEnter quantity of the item: ");
        printf("\033[0m");
        scanf("%[^\n]", newItem.quantity);
        printf("\n\n");

        // Add the new item to the menu
        addNewItemToMenu(restaurant1.id, newItem);
        

        break;
      case 2:
        printf("\e[0;35m");
        print_center_aligned("Updating Quantity For Menu Items\n\n");
        displayMenu(restaurant1.id);
        printf("\033[1;34m");
        printf("\n\t\t\t\tEnter the ID of the item you want to update: ");
        printf("\033[0m");
        scanf("%s", id1);
        printf("\033[1;34m");
        printf("\n\n\n\t\t\t\tEnter the new quantity: ");
        printf("\033[0m");
        scanf("%s", newQuantity);
        updateQuantity(restaurant1.id, id1, newQuantity);
        
        break;
      case 6:
        printf("\033[1;31m");
        print_center_aligned("Exiting program.\n");
        abort();
        printf("\033[0m");
        break;
      case 3:
       print_center_aligned(M"Updating Offer");
       updateOffer(username);
       
      break;
      case 4:
        printf("\e[0;35m");
        print_center_aligned("Updating Price For Menu Items\n\n");
        displayMenu(restaurant1.id);
        printf("\033[1;34m");
        printf("\n\t\t\t\tEnter the ID of the item you want to update: ");
        printf("\033[0m");
        scanf("%s", id1);
        printf("\033[1;34m");
        printf("\n\n\n\t\t\t\tEnter the new Price: ");
        printf("\033[0m");
        scanf("%s", newPrice);
        updatePrice(restaurant1.id, id1, newPrice);
        
        break;
        
      case 5:
        displayMenu(restaurant1.id);
        printf("\033[1;34m");
        printf("\n\t\t\t\tEnter the ID of the item you want to delete: ");
        printf("\033[0m");
        scanf("%s", id1);
        deleteItem(restaurant1.id, id1);
        
        break;




        
      default:
        printf("\033[1;31m");
        printf("\nInvalid choice. Please try again.\n");
        printf("\033[0m");
      }
    } while (choice1 != 6);

  } else {
    printf("\033[1;31m");
    print_center_aligned(R"Invalid choice.\n"r);
    printf("\033[0m");
    
    return 0;
  }

  FILE *file;
  file = fopen("data/restaurant.txt", "r");
  if (file == NULL) {
    printf("File not opened");
    return 1;
  }
  Restaurant restaurant[NUM_RESTAURANTS];
  int read = 0;
  int records = 0;
  do {
    read = fscanf(file, "%49[^,],%d,%d,%d,%f,%d,%d", restaurant[records].name,
                  &restaurant[records].id, &restaurant[records].location.x,
                  &restaurant[records].location.y, &restaurant[records].rating,
                  &restaurant[records].offer, &restaurant[records].order);

    if (read == 7)
      records++;
    if (read != 7 && !feof(file)) {
      printf("File format incorrect.\n");
      return 1;
    }
    if (ferror(file)) {
      printf("Error reading file.\n");
      return 1;
    }
  } while (!feof(file));
  fclose(file);
  sortAndDisplayRestaurants1(restaurant, 27,closestRestaurants);
  // Create the map graph and initialize all edge distances
  MapGraph map;

  readEdgesFromFile("data/edge.bin", &map);

  // Store restaurant locations in the map graph
  for (int i = 0; i < NUM_RESTAURANTS; i++) {
    map.locations[i] = restaurant[i].location;
  }

  
  // Calculate distances from the user to all restaurants
 
  dijkstra(&map, userCoord, userToRestaurantDistances);

  // Find the closest restaurant to the user
  int closestRestaurantIndex = findClosestRestaurant(userToRestaurantDistances);

  // Find and print the closest 10 restaurants from the closest restaurant
  
  findClosestRestaurants(&map, closestRestaurantIndex,userToRestaurantDistances, closestRestaurants);
  
 
  // Calculate the number of restaurants



int numRestaurants = records;
labelN:
while(choice!=8){
  printf(O);  
  printf("\n");
  print_center_aligned("Whats In Your Mind ??\n\n");
  printf(r);
  print_center_aligned("1.Rank Restaurant by Distance\n"); 
  print_center_aligned("2.Rank Restaurant by Rating\n"); 
  print_center_aligned("3.Search by Offer\n"); 
  print_center_aligned("4.Search for Restaurant or Food\n");
  print_center_aligned("5. Add money to e-Wallet\n"); 
  print_center_aligned("6.Purchase Premium Membership\n"); 
  print_center_aligned("7.Change User Details\n"); 
  print_center_aligned("8.Filter By Veg Restauarnts\n");
  print_center_aligned("9.Exit\n\n\n");
  printf(V"\n\t\t\t\tEnter Your Choice:");
  printf(r);
  scanf("%d", &choice);

  if (choice == 1) {
    // Display the 10 closest restaurants to the user
    
    
    printf("\n\t\t\t\t\t\t\t\t----------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\tID");
    printf("\t\tRestaurant Name\t\t\t");
    printf("\t\t\tDistance\n");
    printf("\t\t\t\t\t\t\t\t------------------------------------------------------\n");
    for (int i = 0; i < 10; i++) {
      int restaurantID = restaurant[closestRestaurants[i]].id;
      char *restaurantName = restaurant[closestRestaurants[i]].name;
      double distance = userToRestaurantDistances[closestRestaurants[i]];
      char sub_string[30]; // Assuming a maximum substring length

      // Extract "staurant" from "restaurant1"
      strcpy(sub_string, restaurantName + 1); // Start from index 3, copy 7 characters
      printf("\t\t\t\t\t\t\t\t%-5d\t%-30s\t\t%-.2lf\n",
             restaurantID,sub_string ,distance );
      printf("\t\t\t\t\t\t\t\t--------------------------------------------------------\n");
      printf(r);
      
  }
    printf("\n\n\n\n\n\n\n\n\n\n");
    int choice3;
    printf(BLUEE"\t\t\t\tDo you want to Filter Again?(1/0) : "r);
    scanf("%d",&choice3);
    if (choice3 == 1){goto labelN;}
  }

 
  
  else if (choice == 2){
    // Rank and display restaurants by rating
    FILE *file;
    file = fopen("data/restaurant.txt", "r");
    if (file == NULL) {
      printf("File not opened");
      return 1;
    }
    Restaurant restaurant[NUM_RESTAURANTS];
    int read = 0;
    int records = 0;
    do {
      read = fscanf(file, "%49[^,],%d,%d,%d,%f,%d,%d", restaurant[records].name,
                    &restaurant[records].id, &restaurant[records].location.x,
                    &restaurant[records].location.y, &restaurant[records].rating,
                    &restaurant[records].offer, &restaurant[records].order);

      if (read == 7)
        records++;
      if (read != 7 && !feof(file)) {
        printf("File format incorrect.\n");
        return 1;
      }
      if (ferror(file)) {
        printf("Error reading file.\n");
        return 1;
      }
    } while (!feof(file));
    fclose(file);
    
    
    rankAndDisplayRestaurants(restaurant, 27);
    printf("\n\n\n\n\n\n\n\n\n\n");
    int choice3;
    printf(BLUEE"\t\t\t\tDo you want to Filter Again?(1/0) : "r);
    scanf("%d",&choice3);
    if (choice3 == 1){goto labelN;}
  }

  else if (choice == 4) {
    Entry entries[MAX_ENTRIES];
    int entryCount;

    readData(entries, &entryCount);

    for (int i = 0; i < entryCount; i++) {
      readMenuData(&entries[i]);
    }

    char searchQuery[MAX_LENGTH];

    getchar();
    printf(BLUEE);
    printf("\n\n\n\t\t\t\tEnter search query (Name/Item): ");
    printf(r);
    fgets(searchQuery, MAX_LENGTH, stdin);
    searchQuery[strcspn(searchQuery, "\n")] = 0;

    int menuFile = searchAndDisplay(entries, entryCount, searchQuery);
    if (menuFile != -1) {
      printf("\n\n");
    }

    if (menuFile >= 0) {
      int distance;
      for (int i = 0; i < 10; i++) {
        restaurant[closestRestaurants[i]].id == menuFile;
        distance = userToRestaurantDistances[closestRestaurants[i]];
        offer = restaurant[closestRestaurants[i]].offer;
      }
      displayMenu(menuFile);
      manageCart(username, password, menu, 20, distance, menuFile, offer,
                 userCoord.x, userCoord.y);
      choice=8;
    }
  }

  else if (choice == 3) {
    sortAndDisplayRestaurants(restaurant);
    printf("\n\n\n\n\n\n\n\n");
    int choice3;
    printf(BLUEE"\t\t\t\tDo you want to Filter Again?(1/0) : "r);
    scanf("%d",&choice3);
    if (choice3 == 1){goto labelN;}
  } else if (choice == 5) {
    double moneyinp;
    printf(B"\n\t\t\t\tEnter the amount of money to add: ");
    printf(r);
    scanf("%lf", &moneyinp);
    addMoneyToEwallet(username, moneyinp);
  } else if (choice == 6) {grant_premium_membership("data/users.txt", username);
  } else if (choice == 7) {update_user_details("data/users.txt", username);
  }else if (choice == 8) {
    filterbyType(restaurant);
  }else if (choice == 9) {
    return 0;
  } else {
    printf("Invalid choice.\n");
  }
  if (choice == 1 | choice == 2 | choice == 3 | choice==8) {
    printf(O);
    printf("\n\n\n\t\t\t\tEnter the Restaurant ID you'd like to view the Menu of : ");
    int selectedRestaurantID;
    printf(r);
    scanf("%d", &selectedRestaurantID);

    // Find the index of the selected restaurant
    int selectedRestaurantIndex = -1;
    for (int i = 0; i < NUM_RESTAURANTS; i++) {
      if (restaurant[i].id == selectedRestaurantID) {
        selectedRestaurantIndex = i;
        offer = restaurant[i].offer;
        break;
      }
    }

    // Display menu for the selected restaurant
    if (selectedRestaurantIndex != -1) {
      printf(m);
      char str[50];
      strcpy(str,restaurant[selectedRestaurantIndex].name+1);
      printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\tDisplaying menu for the selected restaurant : %s",
             str);

      // Calculate the distance to the selected restaurant
      int distanceToSelected =
          userToRestaurantDistances[selectedRestaurantIndex];
      double distanceToSelectedInKm = distanceToSelected;
      displayMenu(selectedRestaurantID);
      // Manage cart for the selected restaurant
      manageCart(username, password, menu, 20, distanceToSelectedInKm,
                 selectedRestaurantID, offer, userCoord.x, userCoord.y);
      choice=8;
    } else {
      printf(r);
      print_center_aligned(R"Invalid Restaurant ID !.\n"r);
    }
  }
}
  return 0;
}
