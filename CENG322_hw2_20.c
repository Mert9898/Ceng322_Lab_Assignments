#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
struct vegan {
	char* date;
	char* soup;
	char* maindish;
	char* sidedish;
	char* extra;
	int* salecount;
};
struct vegetarian {
	char* date;
	char* soup;
	char* maindish;
	char* sidedish;
	char* extra;
	int* salecount;
};
struct normal {
	char* date;
	char* soup;
	char* maindish;
	char* sidedish;
	char* extra;
	int* salecount;
};
struct cafeteria {
	char* month;
	struct normal* normal_menu;
	struct vegetarian* vegetarian_menu;
	struct vegan* vegan_menu;
};
int SIZE_OF_ARRAY=23;

void initialize_menus(struct cafeteria *cafeteria, char *csv_file_name ) {
	FILE* fp = fopen(csv_file_name, "r");
	cafeteria->month="March";
	cafeteria->normal_menu=(struct normal*) malloc((SIZE_OF_ARRAY)* sizeof(struct normal));
	cafeteria->vegan_menu=(struct vegan*) malloc((SIZE_OF_ARRAY)* sizeof(struct vegan));
	cafeteria->vegetarian_menu=(struct vegetarian*) malloc((SIZE_OF_ARRAY)* sizeof(struct vegetarian));
	char line[1024];
	int i=0;
	char *token;
	int size;
    while (i<23) {
			fgets(line, 1024, fp);
            token = strtok(line, ",");
			token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->normal_menu[i].date=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->normal_menu[i].date, token, size);
			printf("date %s\n", cafeteria->normal_menu[i].date);
			
            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->normal_menu[i].soup=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->normal_menu[i].soup, token, size);
			printf(" soup %s\n", cafeteria->normal_menu[i].soup);

            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->normal_menu[i].maindish=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->normal_menu[i].maindish, token, size);
			printf("main dish %s\n", cafeteria->normal_menu[i].maindish);
			
            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->normal_menu[i].sidedish=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->normal_menu[i].sidedish, token, size);
			printf(" side %s\n", cafeteria->normal_menu[i].sidedish);
			
			token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->normal_menu[i].extra=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->normal_menu[i].extra, token, size);
			printf(" extra %s\n", cafeteria->normal_menu[i].extra);
			(cafeteria->normal_menu[i]).salecount=(int* )malloc(3 * sizeof(int));
			(cafeteria->normal_menu[i]).salecount[0]=0;
			(cafeteria->normal_menu[i]).salecount[1]=0;
			(cafeteria->normal_menu[i]).salecount[2]=0;
			i++;
		}
    
		while (i<46) {
			fgets(line, 1024, fp);
			token = strtok(line, ",");
			token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegan_menu[i].date=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegan_menu[i].date, token, size);
			printf("date %s\n", cafeteria->vegan_menu[i].date);
			
            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegan_menu[i].soup=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegan_menu[i].soup, token, size);
			printf(" soup %s\n", cafeteria->vegan_menu[i].soup);

            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegan_menu[i].maindish=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegan_menu[i].maindish, token, size);
			printf("main dish %s\n", cafeteria->vegan_menu[i].maindish);
			
            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegan_menu[i].sidedish=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegan_menu[i].sidedish, token, size);
			printf(" side %s\n", cafeteria->vegan_menu[i].sidedish);
			
			token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegan_menu[i].extra=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegan_menu[i].extra, token, size);
			printf(" extra %s\n", cafeteria->vegan_menu[i].extra);
			(cafeteria->vegan_menu[i]).salecount=(int* )malloc(3 * sizeof(int));
			(cafeteria->vegan_menu[i]).salecount[0]=0;
			(cafeteria->vegan_menu[i]).salecount[1]=0;
			(cafeteria->vegan_menu[i]).salecount[2]=0;
			i++;
		}
		
			while (i<69) { 
			fgets(line, 1024, fp);
			token = strtok(line, ",");
			token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegetarian_menu[i].date=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegetarian_menu[i].date, token, size);
			printf("date %s\n", cafeteria->vegetarian_menu[i].date);
			
            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegetarian_menu[i].soup=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegetarian_menu[i].soup, token, size);
			printf(" soup %s\n", cafeteria->vegetarian_menu[i].soup);

            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegetarian_menu[i].maindish=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegetarian_menu[i].maindish, token, size);
			printf("main dish %s\n", cafeteria->vegetarian_menu[i].maindish);
			
            token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegetarian_menu[i].sidedish=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegetarian_menu[i].sidedish, token, size);
			printf(" side %s\n", cafeteria->vegetarian_menu[i].sidedish);
			
			token = strtok(NULL, ",");
			size=strlen(token);
			cafeteria->vegetarian_menu[i].extra=(char*) malloc(size* sizeof(char));
            strncpy(cafeteria->vegetarian_menu[i].extra, token, size);
			printf(" extra %s\n", cafeteria->normal_menu[i].extra);
			(cafeteria->vegetarian_menu[i]).salecount=(int* )malloc(3 * sizeof(int));
			(cafeteria->vegetarian_menu[i]).salecount[0]=0;
			(cafeteria->vegetarian_menu[i]).salecount[1]=0;
			(cafeteria->vegetarian_menu[i]).salecount[2]=0;
			i++;}

	fclose(fp);
}

void record_customer_counts(struct cafeteria *cafeteria) {
	for (int i=0 ; i < SIZE_OF_ARRAY; i++){
		int student_count = (rand() % (51));
		(cafeteria->normal_menu[i]).salecount[0]=student_count;
		int academic_count = (rand() % (51));	
		(cafeteria->normal_menu[i]).salecount[1]=academic_count;
		int administrative_count = (rand() % (51));	
		(cafeteria->normal_menu[i]).salecount[2]=administrative_count;
		
	}
	for (int i=0 ; i < SIZE_OF_ARRAY; i++){
		int student_count = (rand() % (51));
		(cafeteria->vegetarian_menu[i]).salecount[0]=student_count;
		int academic_count = (rand() % (51));	
		(cafeteria->vegetarian_menu[i]).salecount[1]=academic_count;
		int administrative_count = (rand() % (51));	
		(cafeteria->vegetarian_menu[i]).salecount[2]=administrative_count;
		
	}
	for (int i=0 ; i < SIZE_OF_ARRAY; i++){
		int student_count = (rand() % (51));
		(cafeteria->vegan_menu[i]).salecount[0]=student_count;
		int academic_count = (rand() % (51));	
		(cafeteria->vegan_menu[i]).salecount[1]=academic_count;
		int administrative_count = (rand() % (51));	
		(cafeteria->vegan_menu[i]).salecount[2]=administrative_count;	
	}
	
}
void calc_and_show_income(struct cafeteria *cafeteria) {
	
	// Calculate income for each menu type
    int normal_income = 0;
    int vegan_income = 0;
    int vegetarian_income = 0;
	int std_income = 0;
	int academic_income=0;
	int administrative_income=0;
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
    {
		std_income += (cafeteria->normal_menu[i].salecount[0]+ cafeteria->vegan_menu[i].salecount[0]+ cafeteria->vegetarian_menu[i].salecount[0])*6;
		academic_income += (cafeteria->normal_menu[i].salecount[1]+ cafeteria->vegan_menu[i].salecount[1]+ cafeteria->vegetarian_menu[i].salecount[1])*16;
		administrative_income += (cafeteria->normal_menu[i].salecount[2]+ cafeteria->vegan_menu[i].salecount[2]+ cafeteria->vegetarian_menu[i].salecount[2])*12;
        normal_income += (cafeteria->normal_menu[i].salecount[0])*6 + (cafeteria->normal_menu[i].salecount[1])*16 + (cafeteria->normal_menu[i].salecount[2])*12;
       vegan_income += (cafeteria->vegan_menu[i].salecount[0])*6 + (cafeteria->vegan_menu[i].salecount[1])*16 + (cafeteria->vegan_menu[i].salecount[2])*12;
      vegetarian_income += (cafeteria->vegetarian_menu[i].salecount[0])*6 + (cafeteria->vegetarian_menu[i].salecount[1])*16 + (cafeteria->vegetarian_menu[i].salecount[2])*12;
    }
    // Calculate total income
    int total_income = normal_income + vegan_income + vegetarian_income ;
    // Print income information
    printf("Income by menu type:\n");
    printf("Normal menu: %d TL\n", normal_income);
    printf("Vegan menu: %d TL\n", vegan_income);
    printf("Vegetarian menu: %d TL\n", vegetarian_income);

    printf("\nIncome by customer type:\n");
    printf("Students: %d TL\n", std_income);
    printf("Academic personal: %d TL\n", academic_income);
    printf("Administrative personal: %d TL\n", administrative_income);

    printf("\nTotal income: %d TL\n", total_income);
}

int main() {
	
	struct cafeteria* cafeteria = (struct cafeteria*)malloc(sizeof(struct cafeteria));
	
	cafeteria->month=NULL;
	cafeteria->normal_menu = NULL;
	cafeteria->vegetarian_menu = NULL;
	cafeteria->vegan_menu = NULL;
	char* csv_file_name="cafeteria_march_menu.csv";
	initialize_menus(cafeteria,csv_file_name);
    record_customer_counts(cafeteria);
	calc_and_show_income(cafeteria);
	printf("\n~ ~ ~ ~ Normal menu for the first and last days of the month:\n");
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->normal_menu[0].date, cafeteria->normal_menu[0].soup, cafeteria->normal_menu[0].maindish, cafeteria->normal_menu[0].sidedish, cafeteria->normal_menu[0].extra);
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->normal_menu[SIZE_OF_ARRAY - 1].date, cafeteria->normal_menu[SIZE_OF_ARRAY - 1].soup, cafeteria->normal_menu[SIZE_OF_ARRAY - 1].maindish, cafeteria->normal_menu[SIZE_OF_ARRAY - 1].sidedish, cafeteria->normal_menu[SIZE_OF_ARRAY - 1].extra);
	
	printf("\n~ ~ ~ ~ Vegan menu for the first and last days of the month:\n");
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegan_menu[0].date, cafeteria->vegan_menu[0].soup, cafeteria->vegan_menu[0].maindish, cafeteria->vegan_menu[0].sidedish, cafeteria->vegan_menu[0].extra);
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegan_menu[SIZE_OF_ARRAY - 1].date, cafeteria->vegan_menu[SIZE_OF_ARRAY - 1].soup, cafeteria->vegan_menu[SIZE_OF_ARRAY - 1].maindish, cafeteria->vegan_menu[SIZE_OF_ARRAY - 1].sidedish, cafeteria->vegan_menu[SIZE_OF_ARRAY - 1].extra);

    printf("\n~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\n");
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegetarian_menu[0].date, cafeteria->vegetarian_menu[0].soup, cafeteria->vegetarian_menu[0].maindish, cafeteria->vegetarian_menu[0].sidedish, cafeteria->vegetarian_menu[0].extra);
    printf("date--> \"%s\" soup--> \"%s\" main_dish--> \"%s\" side_dish--> \"%s\" extra--> \"%s\"\n", cafeteria->vegetarian_menu[SIZE_OF_ARRAY - 1].date, cafeteria->vegetarian_menu[SIZE_OF_ARRAY - 1].soup, cafeteria->vegetarian_menu[SIZE_OF_ARRAY - 1].maindish, cafeteria->vegetarian_menu[SIZE_OF_ARRAY - 1].sidedish, cafeteria->vegetarian_menu[SIZE_OF_ARRAY - 1].extra);
return 0;}