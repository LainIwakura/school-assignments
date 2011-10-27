#include <stdio.h>

#define FILENAME "employee.dat"

// A struct, cuz we coool
struct employee
{
    char firstName[40];
    char lastName[40];
    int id;
};

// typedef so we don't write struct everywhere
typedef struct employee Employee;

// function prototypes. Const means the parameter we pass in is read-only
void InputEmployeeRecord(Employee e[]);
void PrintEmployeeRecord(const Employee e[]);
void SaveEmployeeRecord(const Employee e[], FILE *FileName);

int main()
{
    FILE *filePtr;
    
    // create an array of struct 
    Employee e[3];
    InputEmployeeRecord(e);
    PrintEmployeeRecord(e);
    SaveEmployeeRecord(e, filePtr);

    return 0;
}

// Get all our employee records
void InputEmployeeRecord(Employee e[3])
{
    int i;
    char firstName[40];
    char lastName[40];
    int id;
    for(i = 0; i < 3; ++i)
    {
        printf("First Name: ");
        scanf("%s", e[i].firstName);
        printf("Last Name: ");
        scanf("%s", e[i].lastName);
        printf("Employee ID: ");
        scanf("%d", &e[i].id);
    }
}

// Print the records we just put in to stdout
void PrintEmployeeRecord(const Employee e[3])
{
    int i;
    for(i = 0; i < 3; ++i)
    {
        printf("%s\n", e[i].firstName);
        printf("%s\n", e[i].lastName);
        printf("%d\n", e[i].id);
    }
}

// Save them to a file
void SaveEmployeeRecord(const Employee e[3], FILE *FileName)
{
    int i;
    if((FileName = fopen(FILENAME, "w")) == NULL)
        printf("Error opening file!\n");
    else
    {
        fprintf(FileName, "ID FIRSTNAME LASTNAME\n");
        for(i = 0; i < 3; ++i)
            fprintf(FileName, "%d %s %s\n", e[i].id, e[i].firstName, e[i].lastName);
        printf("Employees saved.\n");
    }
    fclose(FileName);
}
