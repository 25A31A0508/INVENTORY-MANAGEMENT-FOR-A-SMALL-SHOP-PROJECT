#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define FILE_NAME "inventory.txt"

// Structure to define an item
typedef struct {
    int id;
    char name[50];
    int quantity;
    double price;
} Item;

// Global array to hold items during runtime
Item inventory[MAX_ITEMS];
int itemCount = 0;

// Function Declarations
void loadInventory();
void saveInventory();
void addItem();
void displayInventory();
void searchItem();
void updateItem();
void deleteItem();
void showMenu();

int main() {
    int choice;
    
    // Load existing database records when starting the program
    loadInventory();

    do {
        showMenu();
        printf("Enter your selection (1-6): ");
        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid choice! Please enter a number.\n");
            // Clear input buffer to prevent infinite loop
            while (getchar() != '\n');
            continue;
        }
        getchar(); // Clear trailing newline from buffer

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayInventory(); break;
            case 3: searchItem(); break;
            case 4: updateItem(); break;
            case 5: deleteItem(); break;
            case 6: 
                printf("\nExiting system and saving records. Goodbye!\n"); 
                break;
            default: 
                printf("\nInvalid choice! Please select a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}

// 1. Display System Dashboard Menu
void showMenu() {
    printf("\n============================================\n");
    printf("         SMALL SHOP INVENTORY SYSTEM         \n");
    printf("============================================\n");
    printf("1. Add New Product\n");
    printf("2. Display Current Inventory\n");
    printf("3. Search Product by ID\n");
    printf("4. Update Product Stock / Price\n");
    printf("5. Delete Product Record\n");
    printf("6. Save & Exit\n");
    printf("--------------------------------------------\n");
}

// 2. Load Inventory Records from File
void loadInventory() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        itemCount = 0; // No file exists yet, starting fresh
        return;
    }

    itemCount = 0;
    // Read clean attributes separated by spacing and newlines
    while (fscanf(file, "%d %49s %d %lf\n", 
           &inventory[itemCount].id, 
           inventory[itemCount].name, 
           &inventory[itemCount].quantity, 
           &inventory[itemCount].price) != EOF) {
        itemCount++;
        if (itemCount >= MAX_ITEMS) break;
    }
    fclose(file);
}

// 3. Save Inventory Records to File
void saveInventory() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("\n[Error] Could not open data file for writing!\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%d %s %d %.2f\n", 
                inventory[i].id, 
                inventory[i].name, 
                inventory[i].quantity, 
                inventory[i].price);
    }
    fclose(file);
}

// 4. Add a New Product Record
void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("\n[Warning] Inventory database full! Cannot add more items.\n");
        return;
    }

    Item newItem;
    printf("\n--- Add New Product ---\n");
    printf("Enter Unique Product ID (Number): ");
    if (scanf("%d", &newItem.id) != 1) {
        printf("[Error] ID must be a number.\n");
        while (getchar() != '\n');
        return;
    }
    getchar(); // Clear buffer

    // Check if ID is a duplicate
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == newItem.id) {
            printf("\n[Error] A product with ID %d already exists!\n", newItem.id);
            return;
        }
    }

    printf("Enter Product Name (No spaces): ");
    scanf("%49s", newItem.name);
    
    printf("Enter Initial Stock Quantity: ");
    scanf("%d", &newItem.quantity);
    
    printf("Enter Unit Selling Price: $");
    scanf("%lf", &newItem.price);

    // Commit to runtime array memory block
    inventory[itemCount] = newItem;
    itemCount++;
    
    // Automatically save updates to file storage
    saveInventory();
    printf("\n[Success] Product added successfully!\n");
}

// 5. Display Complete Current Inventory
void displayInventory() {
    if (itemCount == 0) {
        printf("\n[Notice] No stock entries found in inventory database.\n");
        return;
    }

    printf("\n----------------------------------------------------------- \n");
    printf("%-10s %-25s %-12s %-10s\n", "Item ID", "Product Name", "Stock Qty", "Price");
    printf("----------------------------------------------------------- \n");
    
    for (int i = 0; i < itemCount; i++) {
        printf("%-10d %-25s %-12d $%-10.2f\n", 
               inventory[i].id, 
               inventory[i].name, 
               inventory[i].quantity, 
               inventory[i].price);
    }
    printf("----------------------------------------------------------- \n");
}

// 6. Search Product by ID
void searchItem() {
    int searchId;
    printf("\nEnter Product ID to look up: ");
    scanf("%d", &searchId);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == searchId) {
            printf("\n--- Product Found ---\n");
            printf("ID:       %d\n", inventory[i].id);
            printf("Name:     %s\n", inventory[i].name);
            printf("In-Stock: %d units\n", inventory[i].quantity);
            printf("Price:    $%.2f\n", inventory[i].price);
            return;
        }
    }
    printf("\n[Info] Product with ID %d not found in database.\n", searchId);
}

// 7. Update Product Stock / Price
void updateItem() {
    int targetId, foundIndex = -1;
    printf("\nEnter Product ID to update: ");
    scanf("%d", &targetId);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == targetId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\n[Error] Product with ID %d not found.\n", targetId);
        return;
    }

    printf("\nRecord Found! (Current: %s | Qty: %d | Price: $%.2f)\n", 
           inventory[foundIndex].name, inventory[foundIndex].quantity, inventory[foundIndex].price);
    
    printf("Enter New Stock Quantity: ");
    scanf("%d", &inventory[foundIndex].quantity);
    
    printf("Enter New Unit Price: $");
    scanf("%lf", &inventory[foundIndex].price);

    saveInventory();
    printf("\n[Success] Inventory record updated successfully!\n");
}

// 8. Delete Product Record
void deleteItem() {
    int targetId, foundIndex = -1;
    printf("\nEnter Product ID to delete: ");
    scanf("%d", &targetId);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == targetId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\n[Error] Product with ID %d not found.\n", targetId);
        return;
    }

    // Shift elements left to overwrite the deleted item profile index
    for (int i = foundIndex; i < itemCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    itemCount--;

    saveInventory();
    printf("\n[Success] Product removed from database completely.\n");
}

