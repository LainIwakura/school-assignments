/* Written by: Zachary Easterbrook
 * Started on: March 31st 2011
 * Student ID: 103163420
 * Purpose: Manage an address book using a linked list data structure
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define FILENAME "contactlist.dat" 

// Global variables. These are USEFUL in this program because MULTIPLE
// FUNCTIONS need to know how many records we have OR if the contacts have
// already been saved. It is very messy to pass a pointer everywhere, and since
// they are being used relatively safely there isn't much worry about abusing
// these variables.
int num_rec = 0;
int is_saved = 0;

/* All of our data fields need two more
 * spaces than usual for two special characters, \n
 * and \0. fgets will count these characters
 * so we need to account for them.
 */
enum
{
    MAX_REC = 12,
    MAX_NAME = 42,
    MAX_ADDR = 102,
    MAX_POST = 8,
    MAX_PHNUM = 12,
    IS_POST = 99,
    IS_PHONE = 98,
    CLEAN_EXIT = 1,
    BAD_EXIT = 0,
    BUF_SIZE = 256
};

// where we keep all of our contact information
struct contact
{
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    char address[MAX_ADDR];
    char postalCode[MAX_POST];
    char phoneNumber[MAX_PHNUM];
    struct contact *next;
};

typedef struct contact Contact;

Contact *first = NULL;
Contact *last = NULL;

// two simple functions, one prints the menu
// the other prints a message on how to use
// the program
void Menu(void);
void Help(void);

// our main functions that will do the work.
void AddContact();
void DisplayContacts();
void ContactSearch();
void SaveContacts(FILE *);
void LoadContacts(FILE *);
void DeleteContact();

// our helper functions
int isValidNum(char [], int);
void FormatNum(char [], int);
void WordCap(char [], int);

/*****************************************************************************
 * INPUT: The number being checked and it's type (phone number or postal code)
 * OUTPUT: None. Returns false if the checks fail.
 * PURPOSE: To ensure proper data is being entered into our struct
 ******************************************************************************/
int isValidNum(char Number[], int num_t)
{
    int i;
    char errMsg[] = "There is an error in your number formating.";

    switch(num_t)
    {
        // If we have a phone number, we just check the length
        case 98:
            if(strlen(Number) > 12)
            {
                printf("%s\n", errMsg);
                return BAD_EXIT;
            }
            break;
        // If we have a postal code, we not only check the length-
        // we also check that it is in XYXYXY form where X is an
        // alphabetic character and Y is is a digit.
        case 99:
            if(strlen(Number) > 7)
            {
                printf("%s\n", errMsg);
                return BAD_EXIT;
            }
            // for each element of the postal code
            for(i = 0; i < 6; ++i)
            {
                // if it's an index that when mod 2 == 0
                // we know it's a letter
                if(i % 2 == 0)
                {
                    if(!isalpha(Number[i]))
                    {
                        printf("%s\n", errMsg);
                        return BAD_EXIT;
                    }
                }
                else // it's a digit, so we check.
                {
                    if(!isdigit(Number[i]))
                    {
                        printf("%s\n", errMsg);
                        return BAD_EXIT;
                    }
                }
            }
            break;
    }

    // return a value defined in our enum indicating the function did not
    // encounter errors.
    return CLEAN_EXIT;
}

/*****************************************************************************
 * INPUT: The number being formatted and it's type (phone number or postal code)
 * OUTPUT: The formatted number. It does not modify any value in memory
 * PURPOSE: To make things look nice.
 ******************************************************************************/
void FormatNum(char Number[], int num_t)
{
    int i, j;
    switch(num_t)
    {
        // phone number formatting
        case 98:
            printf("(");
            for(i = 0; i < 3; ++i)
                printf("%c", Number[i]);
            printf(") ");
            for(i = 3; i < 6; ++i)
                printf("%c", Number[i]);
            printf("-");
            for(i = 6; i < 10; ++i)
                printf("%c", Number[i]);
            printf("\n");
            break;
        // postal code formatting
        case 99:
            for(j = 0; j < 6; ++j)
            {
                if(j == 3)
                    printf("-");
                if(j % 2 == 0)
                    printf("%c", toupper(Number[j]));
                else
                    printf("%c", Number[j]);
            }
            printf("\n");
            break;
    }
}

/*****************************************************************************
 * INPUT: The word that we need to capitalize properly along with the size
 * OUTPUT: None. Modifies the word in memory. 
 * PURPOSE: To make things look nice
 ******************************************************************************/
void WordCap(char Word[], int size)
{
    int i;
    Word[0] = toupper(Word[0]);
    for(i = 1; i < size; ++i)
        // make everything lowercase except the first element.
        Word[i] = tolower(Word[i]);
}

/*****************************************************************************
 * INPUT: None
 * OUTPUT: Our programs menu, with all it's cool options.
 * PURPOSE: To just print our menu. Makes things a bit cleaner
 ******************************************************************************/
void Menu(void)
{
    printf("1. Add new contact\n"
           "2. Display current contacts\n"
           "3. Search for a contact\n"
           "4. Save contacts to file\n"
           "5. Load contacts from file\n"
           "6. Delete contact\n"
           "7. Print this menu\n"
           "8. Clear the screen\n"
           "9. Print help\n"
           "10. Exit\n");
}

// main entry point
int main()
{
    // Variables for yes / no questions, a menu choice, a line buffer
    // and a file pointer that we pass to our functions.
    char yesno;
    int choice;
    char ln_buf[4];
    FILE *filePtr;

    system("clear");
    Menu();
    do
    {
        printf("ContactBook> ");
        fgets(ln_buf, sizeof(ln_buf), stdin);
        sscanf(ln_buf, "%d", &choice);
        switch(choice)
        {
            case 1:
                AddContact(filePtr);
                break;
            case 2:
                /*
                DisplayContacts();
                break;
            case 3:
                ContactSearch();
                break;
            case 4:
                SaveContacts(filePtr);
                break;
            case 5:
                LoadContacts(filePtr);
                break;
            case 6:
                DeleteContact();
                break;
            case 7:
                Menu();
                break;
            case 8:
                system("clear");
                break;
            case 9:
                printf("Welcome to Contact Book v1.0! If you're stuck, type '7' at the main prompt.\n");
                break;
            case 10:
                // Save contacts to a file before exiting the program
                printf("Save your contacts to file before leaving? ");
                fgets(ln_buf, sizeof(ln_buf), stdin);
                sscanf(ln_buf, "%c", &yesno);
                if(yesno == 'y')
                {
                    SaveContacts(filePtr);
                    printf("Bye!\n");
                    break;
                }
                else
                {
                    // we have this check in case the contacts were already
                    // saved.
                    if(is_saved == 1)
                        printf("Contacts previously saved. Goodbye!\n");
                    else
                    {
                        printf("Contacts not saved.\nBye!\n");
                        break;
                    }
                    break;
                }
                */
            default:
                printf("Unrecognized function reference. Try typing 9.\n");
            break;
        }
    } 
    // stay on the menu while 10 is not chosen.
    while(choice != 10);

    return 0;
}

/*****************************************************************************
 * INPUT: None. 
 * OUTPUT: Just some menus for inputting the data.
 * PURPOSE: To enter contact data into our contact struct.
 ******************************************************************************/
void AddContact()
{
    // Buffer variables, we do not directly put data in the struct
    // because we need to check it for correctness
    char firstName[BUF_SIZE];
    char lastName[BUF_SIZE];
    char address[BUF_SIZE];
    char postalCode[BUF_SIZE];
    char phoneNumber[BUF_SIZE];

    // some basic variables for holding choices / counting
    char yesno;
    char ln_buf[4];
    int i;
    int check;
    
    do
    {
        printf("Adding new contact:\n");
        printf("First name  : ");
        fgets(firstName, BUF_SIZE, stdin);
        printf("Last name   : ");
        fgets(lastName, BUF_SIZE, stdin);
        printf("Address     : ");
        fgets(address, BUF_SIZE, stdin);
        printf("Postal Code : ");
        fgets(postalCode, BUF_SIZE, stdin);
        printf("Phone Number: ");
        fgets(phoneNumber, BUF_SIZE, stdin);
        
        // If all of these conditions are true then we're okay to put data in
        // the struct
        if(strlen(firstName) < MAX_NAME && strlen(lastName) < MAX_NAME && strlen(address) < MAX_ADDR && strlen(postalCode) < MAX_POST && strlen(phoneNumber) < MAX_PHNUM)
            check = 1;
        else // the check failed.
        {
            printf("Some data was too large.\n");
            check = 0;
        }

        // we also make sure the numbers are valid.
        if(isValidNum(phoneNumber, IS_PHONE) && isValidNum(postalCode, IS_POST) && check != 0)
        {
            // Capitalize the words
            WordCap(firstName,strlen(firstName));
            WordCap(lastName,strlen(lastName));
            // Copy things into the struct
            strcpy(contact[num_rec].firstName,firstName);
            strcpy(contact[num_rec].lastName,lastName);
            strcpy(contact[num_rec].address,address);
            strcpy(contact[num_rec].postalCode,postalCode);
            strcpy(contact[num_rec].phoneNumber,phoneNumber);
            ++num_rec; // add 1 to our record counter
            if(num_rec < 10) // if we have less than 10 contacts we can add another.
            {
                printf("Add another contact? ");
                fgets(ln_buf, sizeof(ln_buf), stdin);
                sscanf(ln_buf, "%c", &yesno);
            }
            else
            {
                printf("You've reached the maximum amount of allowed contacts.\n");
                break;
            }
        }
    }
    while(yesno == 'y');
}

/*****************************************************************************
 * INPUT: None.
 * OUTPUT: All of the current contacts in our struct, or no contacts.
 * PURPOSE: To print all of the current contacts in our struct.
 ******************************************************************************/
void DisplayContacts()
{
    int i;
    if(num_rec == 0)
        printf("No contacts!\n");
    else
    {
        printf("Current contacts:\n");
        for(i = 0; i < num_rec; ++i)
        {
            printf("%s", contact[i].firstName);
            printf("%s", contact[i].lastName);
            printf("%s", contact[i].address);
            // FormatNum prints the formated versions of these strings.
            FormatNum(contact[i].postalCode, IS_POST);
            FormatNum(contact[i].phoneNumber, IS_PHONE);
            printf("\n");
        }
    }
}

/*****************************************************************************
 * INPUT: None.
 * OUTPUT: The contacts we find as a result of the search
 * PURPOSE: To search for contacts by last name and display them.
 ******************************************************************************/
void ContactSearch()
{
    if(num_rec == 0) // if we have no contacts currently...
        printf("No contacts to search for! try loading a file or adding some.\n");
    else
    {
        // some basic counter variables, etc.,
        int i, found = 0, first = 0;
        char look_for[MAX_NAME];
        printf("What is the contacts last name? ");
        fgets(look_for, MAX_NAME, stdin);
        for(i = 0; i < num_rec; ++i)
        {
            if(strcmp(contact[i].lastName,look_for) == 0)
                ++found; // just counting how many results there actually are.
        }
        for(i = 0; i < num_rec; ++i)
        {
            // if we find a result
            if(strcmp(contact[i].lastName,look_for) == 0)
            {
                if(first == 0) // and it's our first...print out how many we have in total along with first result
                {
                    printf("Found %d record(s):\n", found);
                    printf("%s", contact[i].firstName);
                    printf("%s", contact[i].lastName);
                    printf("%s", contact[i].address);
                    FormatNum(contact[i].postalCode, IS_POST);
                    FormatNum(contact[i].phoneNumber, IS_PHONE);
                    first = 1;
                }
                else // if it's not the first, just print the results.
                {
                    printf("%s", contact[i].firstName);
                    printf("%s", contact[i].lastName);
                    printf("%s", contact[i].address);
                    FormatNum(contact[i].postalCode, IS_POST);
                    FormatNum(contact[i].phoneNumber, IS_PHONE);
                }
            }
        }
    }
}

/*****************************************************************************
 * INPUT: A file pointer to our sequential text file.
 * OUTPUT: The current members in our contact struct, except to a text file.
 * PURPOSE: To save our data for use at a later point. 
 *******************************************************************************/
void SaveContacts(FILE *file)
{
    int i;
    if((file = fopen(FILENAME, "w")) == NULL)
        printf("Error opening file!\n");
    else
    {
        for(i = 0; i < num_rec; ++i)
        {
            fprintf(file, "%s", contact[i].firstName);
            fprintf(file, "%s", contact[i].lastName);
            fprintf(file, "%s", contact[i].address);
            fprintf(file, "%s", contact[i].postalCode);
            fprintf(file, "%s", contact[i].phoneNumber);
        }
        printf("Contacts saved successfully.\n");
        is_saved = 1; // we use this variable in main
    }
    fclose(file);
}

/*****************************************************************************
 * INPUT: The number being checked and it's type (phone number or postal code)
 * OUTPUT: None. Returns false if the checks fail.
 * PURPOSE: To ensure proper data is being entered into our struct
 ******************************************************************************/
void LoadContacts(FILE *file)
{
    num_rec = 0; // set this to zero so we overwrite current values in the struct.

    int i = 0;
    char line[MAX_ADDR];
    if((file = fopen(FILENAME, "r")) == NULL)
        printf("Error opening file!\n");
    else
    {
        // Do this loop while the fgets isn't null and we have less than 10
        // records.
        while((fgets(line, MAX_ADDR, file) != NULL) && num_rec < 10)
        {
            strcpy(contact[i].firstName,line);
            fgets(line, MAX_ADDR, file);
            strcpy(contact[i].lastName,line);
            fgets(line, MAX_ADDR, file);
            strcpy(contact[i].address,line);
            fgets(line, MAX_ADDR, file);
            strcpy(contact[i].postalCode,line);
            fgets(line, MAX_ADDR, file);
            strcpy(contact[i].phoneNumber,line);
            ++i; // increment our counter
            ++num_rec; // increment the number of records, this variable could be 
                       // used as a counter but it has a different purpose.
        }
        if(num_rec == 1)
            printf("Successfully loaded 1 contact.\n");
        else
            printf("Successfully loaded %d contacts.\n", num_rec);
    }
}

/*****************************************************************************
 * INPUT: None.
 * OUTPUT: The records found, and possibly the records we'll delete.
 * PURPOSE: To delete entries from our struct that are unneeded 
 *******************************************************************************/
void DeleteContact()
{
    char ln_buf[256];
    char yesno;

    if(num_rec == 0)
        printf("No contacts to delete! Try loading a file or adding some.\n");
    else
    {
        int i, j, found = 0, first = 0;
        char look_for[MAX_NAME];
        char yesno;
        printf("What is the contacts last name? ");
        fgets(look_for, MAX_NAME, stdin);
        // This is similar to our search function, refer to that documentation.
        for(i = 0; i < num_rec; ++i)
        {
            if(strcmp(contact[i].lastName,look_for) == 0)
                ++found;
        }
        for(i = 0; i < num_rec; ++i)
        {
            if(strcmp(contact[i].lastName,look_for) == 0)
            {
                if(first == 0)
                {
                    printf("Found %d record(s):\n", found);
                    printf("%s", contact[i].firstName);
                    printf("%s", contact[i].lastName);
                    printf("%s", contact[i].address);
                    FormatNum(contact[i].postalCode, IS_POST);
                    FormatNum(contact[i].phoneNumber, IS_PHONE);
                    printf("\n");
                    printf("Delete this record? y/n: "); // This is where we differ from the search function.
                    fgets(ln_buf, 256, stdin);
                    sscanf(ln_buf, "%c", &yesno);
                    if(yesno == 'y')
                    {
                        // if we are deleting a record, we copy everything from
                        // that record down one.
                        for(j = i; j < num_rec; ++j)
                        {
                            strcpy(contact[j].firstName,contact[j+1].firstName);
                            strcpy(contact[j].lastName,contact[j+1].lastName);
                            strcpy(contact[j].address,contact[j+1].address);
                            strcpy(contact[j].postalCode,contact[j+1].postalCode);
                            strcpy(contact[j].phoneNumber,contact[j+1].phoneNumber);
                        }
                    }
                    first = 1;
                }
                else
                {
                    printf("%s", contact[i].firstName);
                    printf("%s", contact[i].lastName);
                    printf("%s", contact[i].address);
                    FormatNum(contact[i].postalCode, IS_POST);
                    FormatNum(contact[i].phoneNumber, IS_PHONE);
                    printf("\n");
                    // Same story as above. 
                    printf("Delete this record? y/n: ");
                    fgets(ln_buf, 256, stdin);
                    sscanf(ln_buf, "%c", &yesno);
                    if(yesno == 'y')
                    {
                        for(j = i; j < num_rec; ++j)
                        {
                            strcpy(contact[j].firstName,contact[j+1].firstName);
                            strcpy(contact[j].lastName,contact[j+1].lastName);
                            strcpy(contact[j].address,contact[j+1].address);
                            strcpy(contact[j].postalCode,contact[j+1].postalCode);
                            strcpy(contact[j].phoneNumber,contact[j+1].phoneNumber);
                        }
                    }
                }
            }
        }
    }
}
