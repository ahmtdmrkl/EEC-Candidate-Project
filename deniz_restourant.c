/**
 * Author:    Ahmet Demirkol
 * Created:   06.03.2023
 **/

#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_MENU_COUNT  5 
#define MAX_SOUPS_MENU_COUNT 3
#define MAX_MEALS_MENU_COUNT 4
#define MAX_DESSERTS_MENU_COUNT 2


enum menu {
    exit_menu       = 0,  /* Opens         exit menu */
    soups_menu      = 1,  /* Opens soups    sub-menu */
    meals_menu      = 2,  /* Opens meals    sub-menu */
    desserts_menu   = 3,  /* Opens desserts sub-menu */
    bill_menu       = 4,  /* Opens         bill menu */
    main_menu       = 5   /* Returns to    main menu */
}; 


char* main_menu_names[MAX_MENU_COUNT] = { "Cikis\0", "Corbalar\0", "Yemekler\0", "Tatlilar\0", "Hesap\0" };

/* Variables related to soup */
char* soups[MAX_SOUPS_MENU_COUNT] = { "Istemiyorum\0","Domates\0","Tarhana\0" };
int soup_prices[MAX_SOUPS_MENU_COUNT] = { 0, 4, 4 };
int soup_orders_given[MAX_SOUPS_MENU_COUNT] = { 0, 0,0 };

/* Variables related to meal */
char* meals[MAX_MEALS_MENU_COUNT] = { "Istemiyorum\0","Kofte\0","Tavuk\0","Ispanak\0" };
int meals_prices[MAX_MEALS_MENU_COUNT] = { 0, 15, 10, 7 };
int meals_orders_given[MAX_MEALS_MENU_COUNT] = { 0,0,0,0 };

/* Variables related to dessert */
char* desserts[MAX_DESSERTS_MENU_COUNT] = { "Istemiyorum\0","Bakalava\0" };
int desserts_prices[MAX_DESSERTS_MENU_COUNT] = { 0,5 };
int desserts_order_given[MAX_DESSERTS_MENU_COUNT] = { 0,0 };

int bill = 0;
bool customer = true;

/* Prints the main menu */
void print_main_menu(void);

/*Checks the value of the menu page and prints the entered sub menu.*/
void print_sub_menu(int sub_menu);

/* This function takes the menu number as input and controls it.
 *  Prints "invalid input" if an invalid input is entered and it asks for a valid input.
 *  If input is valid this function assigns input to menu page
 */
bool get_next_page(int *next_menu);

/*This function takes order number as input and controls it.If the input is invalid, 
 * it requests the input again and prints the sub menu where it is located again.
 * If the current input is entered, it takes the selected order and increases the index of the order by one.
 */
bool select_order(int order);

/* Checks the value of the bill and redirects customer to the homepage if there is no bill.
 * If the bill is not zero, it prints the orders placed and the total bill and allows the customer to pay the bill.
 * The customer has to pay the bill to leave. If the customer pays valid payment gives change to the customer after successful
 * pay transaction, the program terminates.
 */
bool get_bill(void);

/* This function checks the value of the bill and terminates the program if it is zero.
 * If it is not zero, it redirects to the payment page.
 */
bool exit_page(void);

int main()
{
    int menu_page = main_menu;
    printf("********** DENIZ RESTORANA HOSGELDINIZ **********\n");
    while (customer)
    {
        switch (menu_page)
        {

        case main_menu:
            print_main_menu();
            if (!get_next_page(&menu_page))
            {
                menu_page = main_menu;
            }
            break;

        case soups_menu:
        case meals_menu:
        case desserts_menu:
            print_sub_menu(menu_page);
            /*This condition helps us to find out if the order has been placed and allows us to return to the main page if the order has been placed.*/
            if (select_order(menu_page)) 
            {
                menu_page = main_menu;
            }
            break;
        case bill_menu:
            /*If the bill has been paid, we set the customer variable to false so we exit the loop and terminate the program*/
            if (get_bill()) 
            {
                customer = false;
            }
            else/*If the bill=0 we don't want money from the customer and return and we return the customer to the main menu.*/
            {
                menu_page = main_menu;
            }
            break;
        case exit_menu:
            /*If the bill=0 the customer is free to leave.if bill !=0 we direct the customer to the bill menu.The customer can't leave without paying.*/
            if (exit_page())
            {
                customer = false;
            }
            else
            {
                menu_page = bill_menu;
            }
            break;
        }
    }
    return 0;
}

void print_main_menu(void)
{
    printf("Seciminizi yapin:\n");
    for (int main_menu_index = 1; main_menu_index < MAX_MENU_COUNT; main_menu_index++) 
    {
        printf("%d. %s\n", main_menu_index, main_menu_names[main_menu_index]);
    }
    printf("%d. %s\n", 0, main_menu_names[0]);
}

bool get_next_page(int* next_menu)
{
    bool is_successful = false;
    printf("Secim: ");
    if (scanf("%d", next_menu) == 0)
    {
        printf("Gecersiz secim.\n\n");
        while (getchar() != '\n');
        is_successful = false;
    }
    else if (getchar() != '\n')
    {
        printf("Gecersiz secim.\n\n");
        while (getchar() != '\n');
        is_successful = false;
    }
    else
    {
        if (*next_menu >= 0 && *next_menu < MAX_MENU_COUNT)
        {
            printf("\n");
            is_successful = true;
        }
        else
        {
            printf("Gecersiz secim.\n\n");
            is_successful = false;
        }
    }
    return is_successful;
}

void print_sub_menu(int sub_menu)
{
    switch (sub_menu)
    {
    case soups_menu:
        printf("***Corbalar Fiyat***\n");

        for (int soups_index = 1; soups_index < MAX_SOUPS_MENU_COUNT; soups_index++) 
        {
            printf("%d. %s     %d\n", soups_index, soups[soups_index], soup_prices[soups_index]);
        }

        printf("%d. %s\n", 0, soups[0]);
        break;

    case meals_menu:
        printf("***Yemekler Fiyat***\n");

        for (int meals_index = 1; meals_index < MAX_MEALS_MENU_COUNT; meals_index++)
        {
            printf("%d. %s     %d\n", meals_index, meals[meals_index], meals_prices[meals_index]);
        }

        printf("%d. %s\n", 0, meals[0]);
        break;

    case desserts_menu:
        printf("***Tatlilar Fiyat***\n");
        for (int desserts_index = 1; desserts_index < MAX_DESSERTS_MENU_COUNT; desserts_index++)
        {
            printf("%d. %s     %d\n", desserts_index, desserts[desserts_index], desserts_prices[desserts_index]);
        }
        printf("%d. %s\n", 0, desserts[0]);
        break;


    }


}

bool select_order(int order)
{
    bool is_successful = false;
    int choice = 0;
    bool choice_available = false;
    printf("Secim: ");
    if (scanf("%d", &choice) == 0)
    {
        printf("Gecersiz secim.\n\n");
        while (getchar() != '\n');
        is_successful = false;
    }
    else if (getchar() != '\n')
    {
        printf("Gecersiz secim.\n\n");
        while (getchar() != '\n');
        is_successful = false;
    }
    else
    {
        switch (order)
        {
        case soups_menu:
            if (choice >= 0 && choice < MAX_SOUPS_MENU_COUNT)
            {
                if (!(choice == 0))
                {
                    printf("%s yolda.\n", soups[choice]);
                    soup_orders_given[choice]++;
                    bill += soup_prices[choice];
                }
                is_successful = true;
            }
            else
            {
                printf("Gecersiz secim.\n");
                is_successful = false;
            }
            printf("\n");
            break;

        case meals_menu:
            if (choice >= 0 && choice < MAX_MEALS_MENU_COUNT)
            {
                if (!(choice == 0))
                {
                    printf("%s yolda.\n", meals[choice]);
                    meals_orders_given[choice]++;
                    bill += meals_prices[choice];
                }
                is_successful = true;
            }
            else
            {
                printf("Gecersiz secim.\n");
                is_successful = false;
            }
            printf("\n");
            break;

        case desserts_menu:
            if (choice >= 0 && choice < MAX_DESSERTS_MENU_COUNT)
            {
                if (!(choice == 0))
                {
                    printf("%s yolda.\n", desserts[choice]);
                    desserts_order_given[choice]++;
                    bill += desserts_prices[choice];
                }
                is_successful = true;
            }
            else
            {
                printf("Gecersiz secim.\n");
                is_successful = false;
            }
            printf("\n");
            break;
        }
    }
    return is_successful;
}

bool get_bill(void)
{
    bool is_successful = false;
    int payment = 0;
    int change = 0;

    printf("***Hesap***\n");
    if (bill == 0)
    {
        printf("Hesabiniz bulunmamaktadir cikis seceneginden cikabilirsiniz.\n\n");
        is_successful = false;
    }
    else
    {
        for (int corba_index = 1; corba_index < MAX_SOUPS_MENU_COUNT; corba_index++)
        {
            if (soup_orders_given[corba_index] > 0)
            {
                printf("%d %s: %d\n", soup_orders_given[corba_index], soups[corba_index], soup_orders_given[corba_index] * soup_prices[corba_index]);
            }
        }
        for (int meal_index = 1; meal_index < MAX_MEALS_MENU_COUNT; meal_index++)
        {
            if (meals_orders_given[meal_index] > 0)
            {
                printf("%d %s: %d\n", meals_orders_given[meal_index], meals[meal_index], meals_orders_given[meal_index] * meals_prices[meal_index]);

            }
        }
        for (int dessert_index = 1; dessert_index < MAX_DESSERTS_MENU_COUNT; dessert_index++)
        {
            if (desserts_order_given[dessert_index] > 0)
            {
                printf("%d %s: %d\n", desserts_order_given[dessert_index], desserts[dessert_index], desserts_order_given[dessert_index] * desserts_prices[dessert_index]);
            }
        }
        while (payment < bill)
        {
            printf("Toplam: %d\n", bill);
            printf("Parayi girin: ");

            if (scanf("%d", &payment) == 0)
            {
                printf("Gecersiz para.\n\n");
                while (getchar() != '\n');
                is_successful = false;
            }
            else if (getchar() != '\n')
            {
                printf("Gecersiz secim.\n\n");
                while (getchar() != '\n');
                is_successful = false;
                payment = 0; 
                /*We're assigning 0 to the payment because it still holds the value retrieved with scanf.
                  So we are entering the while loop again.*/ 
            }

            else if (payment < bill)
            {
                 printf("Yetersiz!\n\n");
            }
            else   /*(payment => bill)*/
            {
                    change = payment - bill;
                    printf("\n");
                    if (change > 0)
                    {
                        printf("Para ustu: %d\n", change);
                    }
                    printf("Afiyet Olsun:)\n");
                    printf("Tesekkurler yeniden bekleriz...\n");
                    is_successful = true;
            }
            
        }
    }
    return is_successful;
}

bool exit_page(void)
{
    bool is_successful = false;
    printf("***Cikis***\n");
    if (bill > 0)
    {
        printf("Lutfen odemenizi yapiniz.\n\n");
        is_successful = false;
    }
    else 
    {
        printf("Tesekkurler, yeniden bekleriz :)\n");
        is_successful = true;
    }
    return is_successful;
}

