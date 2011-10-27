// Much of this stuff can be found in the first part, so we won't comment
// as much of it.
#include <stdio.h>

#define FILENAME "employee.dat"

struct employee
{
    char firstName[40];
    char lastName[40];
    int id;
};

typedef struct employee Employee;

void LoadEmployeeRecord(Employee e[], FILE *FileName);
void SaveEmployeeRecord(Employee e[], FILE *FileName);
void WordCap(char []);

int main()
{
    FILE *filePtr;

    Employee e[3];
    LoadEmployeeRecord(e, filePtr);
    SaveEmployeeRecord(e, filePtr);

    return 0;
}

void LoadEmployeeRecord(Employee e[3], FILE *FileName)
{
    int i;
    char firstName[40];
    char lastName[40];
    char junk[40];
    int id;

    if((FileName = fopen(FILENAME, "r")) == NULL)
        printf("Error opening file!\n");
    else
    {
        fgets(junk, 40, FileName);
        for(i = 0; i < 3; ++i)
            fscanf(FileName, "%d %s %s", &e[i].id, e[i].firstName, e[i].lastName);
    }
}

// This function is a bit different. It capitalizes the stuff
void SaveEmployeeRecord(Employee e[3], FILE *FileName)
{
    int i;
    if((FileName = fopen(FILENAME, "w")) == NULL)
        printf("Error opening file!\n");
    else
    {
        fprintf(FileName, "ID FIRSTNAME LASTNAME\n");
        for(i = 0; i < 3; ++i) {
            WordCap(e[i].firstName);
            WordCap(e[i].lastName);
            fprintf(FileName, "%d %s %s\n", e[i].id, e[i].firstName, e[i].lastName);
        }
        printf("Employees saved with fixed letters\n");
    }
    fclose(FileName);
}

// Capitalization function
void WordCap(char Word[])
{
    Word[0] = toupper(Word[0]);
}
