#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 5
#define FILE_NAME "shop_report.txt"

// Structure defining a product item
typedef struct {
    int id;
    char name[30];
    int stock;
    double price;
} Product;

// Core processing function
void generateReport(Product shop[], int size) {
    double totalValue = 0.0;
    int totalStock = 0;

    // 1. Output directly to the console interface
    printf("\n====================================================\n");
    printf("          REAL-TIME SHOP INVENTORY REPORT          \n");
    printf("====================================================\n");
    printf("%-8s %-20s %-12s %-10s\n", "Prod ID", "Product Name", "Stock Qty", "Unit Price");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("%-8d %-20s %-12d $%-10.2f\n", 
               shop[i].id, shop[i].name, shop[i].stock, shop[i].price);
        
        // Calculate metrics
        totalStock += shop[i].stock;
        totalValue += (shop[i].stock * shop[i].price);
    }

    printf("----------------------------------------------------\n");
    printf("Total Inventory Items: %d units\n", totalStock);
    printf("Total Asset Valuation: $%.2f\n", totalValue);
    printf("====================================================\n");

    // 2. Persistent File Handling Operations (Saves report to a file)
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("[Error] Dynamic file initialization failed.\n");
        return;
    }

    fprintf(file, "====================================================\n");
    fprintf(file, "          PERSISTENT SHOP INVENTORY REPORT          \n");
    fprintf(file, "====================================================\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "ID: %-5d | Name: %-15s | Qty: %-5d | Price: $%.2f\n", 
                shop[i].id, shop[i].name, shop[i].stock, shop[i].price);
    }
    fprintf(file, "----------------------------------------------------\n");
    fprintf(file, "Total Stock Units : %d\n", totalStock);
    fprintf(file, "Total Asset Value : $%.2f\n", totalValue);
    fprintf(file, "====================================================\n");
    
    fclose(file);
    printf("\n[Success] Local database compiled! Report saved to '%s'\n", FILE_NAME);
}

int main() {
    // Initialize mock datasets cleanly
    Product shopInventory[MAX_ITEMS] = {
        {101, "Wireless_Mouse", 45, 19.99},
        {102, "Mechanical_Keyboard", 20, 69.50},
        {103, "HD_Monitor_24", 12, 149.99},
        {104, "USB_C_Hub", 75, 24.95},
        {105, "Gaming_Headset", 30, 45.00}
    };

    // Execute core business logic
    generateReport(shopInventory, MAX_ITEMS);

    printf("\nPress Enter to close program...\n");
    getchar(); 
    return 0;
}

