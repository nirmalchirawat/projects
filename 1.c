#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define gst 3.0

void billing();
void previous_bill();

int main()
{
    printf("Welcome to Jewellery Shop\n");
    
    for(;;) { 
        printf("\n1.Billing\n2.Previous Bill\n3.Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d",&choice);
        
        if(choice == 1) {
            billing();
        }
        else if(choice == 2) {
            previous_bill();
        }
        else if(choice == 3) {
            printf("Exiting the program\n");
            break; 
        }
        else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}

void billing()
{
    FILE *fptr = fopen("bill.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char customer_name[50];
    int design, quantity;
    float price_per_gram, total_price, gst_amount, final_amount, making_charge;
    time_t t = time(NULL);

    printf("Enter customer name: ");
    scanf("%s", customer_name);
    printf("Enter design: ");
    scanf("%d", &design);
    printf("Enter quantity in grams: ");
    scanf("%d", &quantity);
    printf("Enter price per gram: ");
    scanf("%f", &price_per_gram);
    printf("Enter making charge %%: ");  
    scanf("%f", &making_charge);

    total_price = price_per_gram * quantity;
    float making_charge_total = (making_charge / 100.0) * total_price;  
    gst_amount = (gst / 100.0) * total_price;
    final_amount = total_price + making_charge_total + gst_amount;  


    printf("\n=== BILL GENERATED ===\n");
    printf("Date: %s", ctime(&t));  
    printf("Customer Name: %s\n", customer_name);
    printf("Item Code: %d\n", design);
    printf("Quantity: %d grams\n", quantity);
    printf("Price per gram: Rs.%.2f\n", price_per_gram);
    printf("Total Price: Rs.%.2f\n", total_price);
    printf("Making Charge (%.1f%%): Rs.%.2f\n", making_charge, making_charge_total); 
    printf("GST Amount (%.1f%%): Rs.%.2f\n", gst, gst_amount);
    printf("Final Amount: Rs.%.2f\n", final_amount);
    printf("-----------------------------\n");

    fprintf(fptr, "\nDate: %s", ctime(&t));
    fprintf(fptr, "Customer Name: %s\n", customer_name);
    fprintf(fptr, "Item Code: %d\n", design);
    fprintf(fptr, "Quantity: %d grams\n", quantity);
    fprintf(fptr, "Price per gram: Rs.%.2f\n", price_per_gram);
    fprintf(fptr, "Total Price: Rs.%.2f\n", total_price);
    fprintf(fptr, "Making Charge (%.1f%%): Rs.%.2f\n", making_charge, making_charge_total);  // ← NEW
    fprintf(fptr, "GST Amount (%.1f%%): Rs.%.2f\n", gst, gst_amount);
    fprintf(fptr, "Final Amount: Rs.%.2f\n", final_amount);
    fprintf(fptr, "--------------------------\n");

    fclose(fptr);
    printf("Bill saved to bill.txt!\n");
}

void previous_bill()
{
    printf("\n--- BILL SEARCH OPTIONS ---\n");
    printf("1. Show All Bills\n");
    printf("2. Search by Customer Name\n");
    printf("Enter choice (1 or 2): ");
    
    int search_choice;
    scanf("%d", &search_choice);
    
    if(search_choice == 2) {
        // SEARCH BY NAME
        char search_name[50];
        printf("Enter customer name to search: ");
        scanf(" %s", search_name);
        
        FILE *fptr = fopen("bill.txt", "r");
        if(fptr == NULL) {
            printf("No bills found!\n");
            return;
        }
        
        printf("\n--- Bills for '%s' ---\n", search_name);
        char line[200];
        int found = 0;
        
        while(fgets(line, sizeof(line), fptr)) {

            if(strstr(line, "Customer Name:") && strstr(line, search_name)) {
                printf("%s", line);  
                found = 1;
                

                for(int i = 0; i < 10 && fgets(line, sizeof(line), fptr); i++) {
                    printf("%s", line);
                }
                printf("\n");
            }
        }
        
        if(found == 0) {
            printf("No bills found for '%s'!\n", search_name);
        }
        fclose(fptr);
    }
    else {

        FILE *fptr = fopen("bill.txt", "r");
        if(fptr == NULL) {
            printf("No previous bills found!\n");
            return;
        }
        
        printf("\n--- All Previous Bills ---\n");
        char ch;
        while((ch = fgetc(fptr)) != EOF) {
            printf("%c", ch);
        }
        fclose(fptr);
    }
}

