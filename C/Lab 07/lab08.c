#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point
{
    int x;
    int y;
    char label[21];
    struct point *ptrNext;
};

typedef struct point Point;

int isEmpty(Point *ptr);
void PrintList(Point *ptrF);
void ResetList(Point **ptrF);
void AddToBeginning(Point **ptrF, Point **ptrL);
void AddToEnd(Point **ptrF, Point **ptrL);
void Save(Point *ptrF);
void Load(Point **ptrF, Point **ptrL);

void Menu()
{
    printf("1. Add to the beginning of the list\n"
           "2. Add to the end of the list\n"
           "3. Check if the list is empty\n"
           "4. Reset the list\n"
           "5. Display the list\n"
           "6. Save the list to a text file\n"
           "7. Load the list from a file\n"
           "8. Exit the program\n");
}

int main()
{
    char ln_buf[256];
    int choice;

    Point *ptrFirst = NULL;
    Point *ptrLast = NULL;

    Menu();
    do
    {
        printf("Lab 08> ");
        fgets(ln_buf, 256, stdin);
        sscanf(ln_buf, "%d", &choice);
        switch(choice)
        {
            case 1:
                AddToBeginning(&ptrFirst, &ptrLast);
                break;
            case 2:
                AddToEnd(&ptrFirst, &ptrLast);
                break;
            case 3:
                if(isEmpty(ptrFirst))
                    printf("List isn't empty!\n");
                else
                    printf("List is empty!\n");
                break;
            case 4:
                ResetList(&ptrFirst);
                break;
            case 5:
                PrintList(ptrFirst);
                break;
            case 6:
                Save(ptrFirst);
                break;
            case 7:
                Load(&ptrFirst, &ptrLast);
                break;
            case 8:
                printf("Bai! =D\n");
                break;
            default:
                printf("Unrecognized function reference.\n");
                break;
        }
    }
    while(choice != 8);

    return 0;
}

void AddToBeginning(Point **ptrF, Point **ptrL)
{
    Point *new;
    int x, y, i = 0;
    char label[21];
    char ln_buf[256];
    new = malloc(sizeof(Point));

    printf("Enter a point for x.\n");
    fgets(ln_buf, 258, stdin);
    sscanf(ln_buf, "%d", &x);
    printf("Enter a point for y.\n");
    fgets(ln_buf, 258, stdin);
    sscanf(ln_buf, "%d", &y);
    printf("Enter a label for this point\n");
    fgets(label, 23, stdin);
    do 
        if(label[i] == '\n') label[i] = '\0';
    while(label[i++] != '\0');
    new->x = x;
    new->y = y;
    strcpy(new->label,label);
    new->ptrNext = NULL;

    if(*ptrF == NULL && *ptrL == NULL) {
        *ptrF = new;
        *ptrL = new;
    } else {
        new->ptrNext = *ptrF;
        *ptrF = new;
    }
}

void AddToEnd(Point **ptrF, Point **ptrL)
{
    Point *new;
    int x, y, i = 0;
    char label[21];
    char ln_buf[256];
    new = malloc(sizeof(Point));

    printf("Enter a point for x.\n");
    fgets(ln_buf, 258, stdin);
    sscanf(ln_buf, "%d", &x);
    printf("Enter a point for y.\n");
    fgets(ln_buf, 258, stdin);
    sscanf(ln_buf, "%d", &y);
    printf("Enter a label for this point\n");
    fgets(label, 23, stdin);
    do 
        if(label[i] == '\n') label[i] = '\0';
    while(label[i++] != '\0');
    new->x = x;
    new->y = y;
    strcpy(new->label,label);
    new->ptrNext = NULL;

    if(*ptrF == NULL && *ptrL == NULL) {
        *ptrF = new;
        *ptrL = new;
    } else {
        (*ptrL)->ptrNext = new;
        *ptrL = new;
    }
}

void PrintList(Point *ptrF)
{
    unsigned int i = 0, j = 1;
    Point *current;
    current = ptrF;

    if(current == NULL || current == 0) {
        printf("Nothing to print!\n");
    } else {
        do {
            printf("Item No.%d\n", j);
            do 
                if(current->label[i] == '\n') current->label[i] = '\0';
            while(current->label[i++] != '\0');
            i = 0;
            printf("%s: (%d, %d)\n", current->label, current->x, current->y);
            current = current->ptrNext;
            ++j;
        } while(current != NULL || current != 0);
    }
}

void ResetList(Point **ptrF)
{
    Point *tmp;
    while(*ptrF != NULL)
    {
        tmp = (*ptrF)->ptrNext;
        free(*ptrF);
        *ptrF = tmp;
    }
}

void Save(Point *ptrF)
{
    Point *current;
    current = ptrF;
    FILE *filePtr;
    if((filePtr = fopen("list.txt", "w")) == NULL)
        printf("Error opening file!\n");
    else {
        while(current != NULL) {
            fprintf(filePtr, "%s\n%d\n%d\n", current->label, current->x, current->y);
            current = current->ptrNext;
        }
        printf("List saved successfully\n");
    }
    fclose(filePtr);
}

void Load(Point **ptrF, Point **ptrL)
{
    Point *current;
    unsigned int x, y, i = 0;
    char line[21];
    FILE *filePtr;
    if((filePtr = fopen("list.txt", "r")) == NULL)
        printf("Error opening file!\n");
    else {
        while(fgets(line, 21, filePtr) != NULL) {
            current = malloc(sizeof(Point));
            strcpy(current->label,line);
            fgets(line, 21, filePtr);
            sscanf(line, "%d", &x);
            current->x = x;
            fgets(line, 21, filePtr);
            sscanf(line, "%d", &y);
            current->y = y;
            current->ptrNext = NULL;

            if(*ptrF == NULL && *ptrL == NULL) {
                *ptrF = current;
                *ptrL = current;
            } else {
                (*ptrL)->ptrNext = current;
                *ptrL = current;
            }
        }
        printf("File loaded successfully.\n");
    }
    fclose(filePtr);
}

int isEmpty(Point *ptrF)
{
    return ptrF == NULL || 0 ? 0 : 1;
}
