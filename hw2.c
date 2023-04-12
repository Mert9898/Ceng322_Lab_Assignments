#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DAYS 31
#define MAX_NAME_LEN 50
#define MAX_EXTRA_LEN 20
#define MAX_COUNT 50
#define STUDENT_PRICE 6
#define ACADEMIC_PRICE 16
#define ADMIN_PRICE 12

// Structs
typedef struct
{
    char date[6];
    char soup[MAX_NAME_LEN];
    char main_dish[MAX_NAME_LEN];
    char side_dish[MAX_NAME_LEN];
    char extra[MAX_EXTRA_LEN];
    int sales_count[3]; // 0: student_count, 1: academic_count, 2: administrative_count

} Menu;

typedef struct
{
    char month_name[MAX_NAME_LEN];
    Menu *normal_menu;
    Menu *vegan_menu;
    Menu *vegetarian_menu;

} Cafeteria;

// Function declarations
void initialize_menus(Cafeteria *cafeteria, char *csv_file_name);
void record_customer_counts(Cafeteria *cafeteria);
void calc_and_show_income(Cafeteria *cafeteria);

// Main function
int main()
{
    // Initialize random seed
    srand(time(NULL));

    // Allocate memory for cafeteria struct
    Cafeteria *cafeteria = (Cafeteria *)malloc(sizeof(Cafeteria));
    if (cafeteria == NULL)
    {
        printf("Error: could not allocate memory for cafeteria.\n");
        return 1;
    }

    // Initialize cafeteria
    memset(cafeteria->month_name, 0, MAX_NAME_LEN);
    cafeteria->normal_menu = NULL;
    cafeteria->vegan_menu = NULL;
    cafeteria->vegetarian_menu = NULL;

    // Initialize menus and customer counts, and calculate income
    initialize_menus(cafeteria, "cafeteria_march_menu.csv");
    record_customer_counts(cafeteria);
    calc_and_show_income(cafeteria);
    
    printf("\n~ ~ ~ ~ Normal menu for the first and last days of the month:\n");
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->normal_menu[0].date, cafeteria->normal_menu[0].soup, cafeteria->normal_menu[0].main_dish, cafeteria->normal_menu[0].side_dish, cafeteria->normal_menu[0].extra);
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->normal_menu[MAX_DAYS - 1].date, cafeteria->normal_menu[MAX_DAYS - 1].soup, cafeteria->normal_menu[MAX_DAYS - 1].main_dish, cafeteria->normal_menu[MAX_DAYS - 1].side_dish, cafeteria->normal_menu[MAX_DAYS - 1].extra);

    printf("\n~ ~ ~ ~ Vegan menu for the first and last days of the month:\n");
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegan_menu[0].date, cafeteria->vegan_menu[0].soup, cafeteria->vegan_menu[0].main_dish, cafeteria->vegan_menu[0].side_dish, cafeteria->vegan_menu[0].extra);
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegan_menu[MAX_DAYS - 1].date, cafeteria->vegan_menu[MAX_DAYS - 1].soup, cafeteria->vegan_menu[MAX_DAYS - 1].main_dish, cafeteria->vegan_menu[MAX_DAYS - 1].side_dish, cafeteria->vegan_menu[MAX_DAYS - 1].extra);

    printf("\n~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\n");
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegetarian_menu[0].date, cafeteria->vegetarian_menu[0].soup, cafeteria->vegetarian_menu[0].main_dish, cafeteria->vegetarian_menu[0].side_dish, cafeteria->vegetarian_menu[0].extra);
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegetarian_menu[MAX_DAYS - 1].date, cafeteria->vegan_menu[MAX_DAYS - 1].soup, cafeteria->vegan_menu[MAX_DAYS - 1].main_dish, cafeteria->vegan_menu[MAX_DAYS - 1].side_dish, cafeteria->vegan_menu[MAX_DAYS - 1].extra);

    // Free memory
    free(cafeteria->normal_menu);
    free(cafeteria->vegan_menu);
    free(cafeteria->vegetarian_menu);
    free(cafeteria);

    return 0;
}

// Function implementations
void initialize_menus(Cafeteria *cafeteria, char *csv_file_name)
{
    // Open CSV file
    FILE *csv_file = fopen(csv_file_name, "r");
    if (csv_file == NULL)
    {
        printf("Error: could not open CSV file.\n");
        exit(1);
    }

    // Read month name from filename
    char *month_name_start = strrchr(csv_file_name, '/');
    if (month_name_start == NULL)
    {
        month_name_start = csv_file_name;
    }
    else
    {
        month_name_start++;
    }
    char *month_name_end = strchr(month_name_start, '.');
    if (month_name_end == NULL)
    {
        printf("Error: invalid filename.\n");
        exit(1);
    }
    strncpy(cafeteria->month_name, month_name_start, month_name_end - month_name_start);

    // Allocate memory for menus
    cafeteria->normal_menu = (Menu *)malloc(sizeof(Menu) * MAX_DAYS);
    cafeteria->vegan_menu = (Menu *)malloc(sizeof(Menu) * MAX_DAYS);
    cafeteria->vegetarian_menu = (Menu *)malloc(sizeof(Menu) * MAX_DAYS);
    if (cafeteria->normal_menu == NULL || cafeteria->vegan_menu == NULL || cafeteria->vegetarian_menu == NULL)
    {
        printf("Error: could not allocate memory for menus.\n");
        exit(1);
    }

    // Initialize sales counts
    for (int i = 0; i < num_days; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cafeteria->normal_menu[i].sales_count[j] = 0;
            cafeteria->vegan_menu[i].sales_count[j] = 0;
            cafeteria->vegetarian_menu[i].sales_count[j] = 0;
        }
    }

    // Read menus from CSV file
    int day_index = 0;
    while (fgets(line, 1024, csv_file))
    {
        if (line[0] != '\n')
        {
            // Parse menu items
            char *token = strtok(line, ",");
            strncpy(cafeteria->normal_menu[day_index].date, token, 6);
            token = strtok(NULL, ",");
            strncpy(cafeteria->normal_menu[day_index].soup, token, MAX_NAME_LEN);
            token = strtok(NULL, ",");
            strncpy(cafeteria->normal_menu[day_index].main_dish, token, MAX_NAME_LEN);
            token = strtok(NULL, ",");
            strncpy(cafeteria->normal_menu[day_index].side_dish, token, MAX_NAME_LEN);
            token = strtok(NULL, ",");
            strncpy(cafeteria->normal_menu[day_index].extra, token, MAX_EXTRA_LEN);

            // Copy menu items to vegan and vegetarian menus
            memcpy(&cafeteria->vegan_menu[day_index], &cafeteria->normal_menu[day_index], sizeof(Menu));
            memcpy(&cafeteria->vegetarian_menu[day_index], &cafeteria->normal_menu[day_index], sizeof(Menu));

            day_index++;
        }
    }

    // Close CSV file
    fclose(csv_file);
}

void calc_and_show_income(Cafeteria *cafeteria)
{
    // Calculate income for each menu type
    int normal_income = 0;
    int vegan_income = 0;
    int vegetarian_income = 0;
    for (int i = 0; i < cafeteria->num_days; i++)
    {
        int *normal_sales_count = cafeteria->normal_menu[i].sales_count;
        int *vegan_sales_count = cafeteria->vegan_menu[i].sales_count;
        int *vegetarian_sales_count = cafeteria->vegetarian_menu[i].sales_count;

        normal_income += (normal_sales_count[0] * 6) + (normal_sales_count[1] * 16) + (normal_sales_count[2] * 12);
        vegan_income += (vegan_sales_count[0] * 6) + (vegan_sales_count[1] * 16) + (vegan_sales_count[2] * 12);
        vegetarian_income += (vegetarian_sales_count[0] * 6) + (vegetarian_sales_count[1] * 16) + (vegetarian_sales_count[2] * 12);
    }

    // Calculate total income
    int total_income = normal_income + vegan_income + vegetarian_income;

    // Print income information
    printf("Income by menu type:\n");
    printf("Normal menu: %d TL\n", normal_income);
    printf("Vegan menu: %d TL\n", vegan_income);
    printf("Vegetarian menu: %d TL\n", vegetarian_income);

    printf("\nIncome by customer type:\n");
    printf("Students: %d TL\n", (cafeteria->num_students * 6));
    printf("Academic personal: %d TL\n", (cafeteria->num_academics * 16));
    printf("Administrative personal: %d TL\n", (cafeteria->num_admins * 12));

    printf("\nTotal income: %d TL\n", total_income);
}

void record_customer_counts(Cafeteria *cafeteria)
{

    // Seed random number generator
    srand(time(NULL));

    // Loop through each day and menu type
    for (int i = 0; i < cafeteria->num_days; i++)
    {
        // Generate random sales counts for each customer type
        int student_count = rand() % 51;
        int academic_count = rand() % 51;
        int admin_count = rand() % 51;

        // Update sales counts in normal menu
        cafeteria->normal_menu[i].sales_count[0] = student_count;
        cafeteria->normal_menu[i].sales_count[1] = academic_count;
        cafeteria->normal_menu[i].sales_count[2] = admin_count;

        // Update sales counts in vegan menu
        cafeteria->vegan_menu[i].sales_count[0] = student_count;
        cafeteria->vegan_menu[i].sales_count[1] = academic_count;
        cafeteria->vegan_menu[i].sales_count[2] = admin_count;

        // Update sales counts in vegetarian menu
        cafeteria->vegetarian_menu[i].sales_count[0] = student_count;
        cafeteria->vegetarian_menu[i].sales_count[1] = academic_count;
        cafeteria->vegetarian_menu[i].sales_count[2] = admin_count;
    }
}
