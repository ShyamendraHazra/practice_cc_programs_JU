#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define f1 "emplTEXT"
#define f2 "emplBIN"
#define TXT 'T'
#define BIN 'B'


typedef struct employee Employee;

Employee {
    char* name;
    char* emp_id;
    unsigned int salary;
};

void control();
bool menu(FILE** fpT, FILE** fpB);
void file_ops(FILE** fp, const char* filename, const char* mode);
void display_files(FILE** fp, char mode);
void append_to_files(FILE** fp);
void delete_entry(FILE** fp, char mode, const int* entry_list, int entry_count);
void load_employee_data(Employee* emp);

int main() {


    return 0;
}

void control() {

    FILE* empLTF = NULL;
    FILE* empLBF = NULL;
    bool flag = true;

    while(flag) {
        printf("Choose from below options \n");
        flag = menu(&empLTF, &empLBF);
    }

}

bool menu(FILE** fpT, FILE** fpB) {

    bool sig = true;
    int choice = -1;
    
    printf("\
        Enter 1 to display the file\n\
        Enter 2 to append an entry\n\
        Enter 3 to delete any entry(ies)\n\
        Enter 0 to exit...\n\
        Your choice [1,2,3,0] :: 
    ");

    scanf("%d", &choice);

    if(choice < 0 || choice > 3) {
        
        printf("Invalid choice please try again!\n\n");
    
    } else if(!choice) {
        
        printf("Exiting....");
        sig = false;
    
    } else {

        switch(choice) {
            
            case 1:
                display_files(&fpT, TXT);
                display_files(&fpB, BIN);
                break;
            
            case 2: 
                append_to_file(&fpT);
                break;

            case 3:
                delete_entry(&fpT, TXT);           
                delete_entry(&fpB, BIN);           
                break;
        }

    }


    return sig;
}

void file_ops(FILE** fp, const char* filename, const char* mode) {
    
    *fp = fopen(filename, mode);
    
    if(fp == NULL) {

        perror("Error opening file %s", filename);
        exit(EXIT_FAILURE);
    }
    
}

void display_files(FILE** fp, char mode) {

    switch(mode) {
        case TXT:
            file_ops(fp, f1, "r");
            
            if(!feof(*fp)) {

                int count = 0;
                while(!feof()) {
                    count++;
                    printf("%d | ",count);
                    printf("%c",fgetc(*fp));

                }

            } else {

                printf("No entry in the file yet!!\n");

            }
            fclose(*fp);
            *fp = NULL;
            break;
        
        case BIN:
            file_ops(fp, f1, "rb");

            if(!feof(*fp)) {

                int count = 0;
                char ch;
                while(!feof()) {
                    count++;
                    printf("%d | ",count);
                    printf("%c",fread(&ch, sizeof(char), 1, *fp));

                }

            } else {

                printf("No entry in the file yet!!\n");

            }

            fclose(*fp);
            *fp = NULL;
            break;
    }

}
void append_to_files(FILE** fp) {
   	char mode = TXT; 
        switch(mode) {
        case TXT:
            
            file_ops(fp, f1, "a");
            
            char* emp_data;

            Employee emp;
	    load_employee_data(&emp);
	    sprintf(emp_data, "%s %s %d\n", emp.name, emp.emp_id, emp.salary);
	    fprintf(*fp, "%s", emp_data);

	    printf("Entry :: %s\twas added to the file\n", emp_data);

            fclose(*fp);
            *fp = NULL;
            
        
        case BIN:

	    file_ops(fp, f1, "ab");	
		
	    fwrite(&emp, sizeof(Employee), 1, *fp);

            fclose(*fp);
            *fp = NULL;
            break;
    }

}
void delete_entry(FILE** fp, char mode, const int* entry_list, int entry_count);
void load_employee_data(Employee* emp){}
