??=include<stdio.h>
??=include<string.h>
??=include<stdlib.h>
??=include<ctype.h>
??=define __F__ "contactlist.dat" 
??=define xvfz printf
??=define fxvfz fprintf
??=define fzvx if
??=define zfvx else
??=define vzxf while
??=define zxfv do
typedef int f;
typedef char z;
f num_rec = 0;
f is_saved = 0;
enum{zoo=31,coo=415,boo=9,woo=26,foo=99,ggg=98,doo=1,moo= 0,_=256};
struct _z{z firstName??(zoo:>; z lastName??(zoo:>; z address??(coo:>; z postalCode??(boo:>; z phoneNumber??(woo:>;
    struct _z *next;};
typedef struct _z __Z;

void Menu(void);
void Help(void);
void Add__z(__Z**, __Z**);
void Display__zs(__Z**);
void __zSearch(__Z**);
void Save__zs(__Z**, FILE *);
void Load__zs(__Z**, __Z**, FILE *);
void Delete__z(__Z**);
f isValidNum(z ??(:>, f);
void FormatNum(z ??(:>, f);
void WordCap(z ??(:>, f);

int isValidNum(char Number??(:>, int num_t)
{
    int i;
    char errMsg??(:> = "There is an error in your number formating.";

    switch(num_t)
    {
        // If we have a phone number, we just check the length
        case 98:
            if(strlen(Number) > 12)
            {
                xvfz("%s\n", errMsg);
                return moo;
            }
            break;
        case 99:
            if(strlen(Number) > 7)
            {
                xvfz("%s\n", errMsg);
                return moo;
            }
            for(i = 0; i < 6; ++i)
            {
                if(i % 2 == 0)
                {
                    if(!isalpha(Number??(i:>))
                    {
                        xvfz("%s\n", errMsg);
                        return moo;
                    }
                }
                else
                {
                    if(!isdigit(Number??(i:>))
                    {
                        xvfz("%s\n", errMsg);
                        return moo;
                    }
                }
            }
            break;
    }
    return doo;
}

/*****************************************************************************
 * INPUT: The number being formatted and it's type (phone number or postal code)
 * OUTPUT: The formatted number. It does not modify any value in memory
 * PURPOSE: To make things look nice.
 ******************************************************************************/
void FormatNum(char Number??(:>, int num_t)
{
    int i, j;
    switch(num_t)
    {
        // phone number formatting
        case 98:
            xvfz("(");
            for(i = 0; i < 3; ++i)
                xvfz("%c", Number??(i:>);
            xvfz(") ");
            for(i = 3; i < 6; ++i)
                xvfz("%c", Number??(i:>);
            xvfz("-");
            for(i = 6; i < 10; ++i)
                xvfz("%c", Number??(i:>);
            xvfz("\n");
            break;
        // postal code formatting
        case 99:
            for(j = 0; j < 6; ++j)
            {
                if(j == 3)
                    xvfz("-");
                if(j % 2 == 0)
                    xvfz("%c", toupper(Number??(j:>));
                else
                    xvfz("%c", Number??(j:>);
            }
            xvfz("\n");
            break;
    }
}

/*****************************************************************************
 * INPUT: The word that we need to capitalize properly along with the size
 * OUTPUT: None. Modifies the word in memory. 
 * PURPOSE: To make things look nice
 ******************************************************************************/
void WordCap(char Word??(:>, int size)
{
    int i;
    Word??(0:> = toupper(Word[0]);
    for(i = 1; i < size; ++i)
        // make everything lowercase except the first element.
        Word??(i:> = tolower(Word[i]);
}

/*****************************************************************************
 * INPUT: None
 * OUTPUT: Our programs menu, with all it's cool options.
 * PURPOSE: To just print our menu. Makes things a bit cleaner
 ******************************************************************************/
void Menu(void)
{
    xvfz("1. Add new __z\n"
           "2. Display current __zs\n"
           "3. Search for a __z\n"
           "4. Save __zs to file\n"
           "5. Load __zs from file\n"
           "6. Delete __z\n"
           "7. Print this menu\n"
           "8. Clear the screen\n"
           "9. Print help\n"
           "10. Exit\n");
}

// main entry point
f main()
{
    __Z *head = NULL;
    __Z *tail = NULL;

    // Variables for yes / no questions, a menu choice, a line buffer
    // and a file pointer that we pass to our functions.
    z yesno;
    f choice;
    z ln_buf??(4:>;
    FILE *filePtr;

    system("clear");
    Menu();
    do
    {
        xvfz("__zBook> ");
        fgets(ln_buf, sizeof(ln_buf), stdin);
        sscanf(ln_buf, "%d", &choice);
        switch(choice)
        {
            case 1:
                Add__z(&head, &tail);
                break;
            case 2:
                Display__zs(&head);
                break;
            case 3:
                __zSearch(&head);
                break;
            case 4:
                Save__zs(&head, filePtr);
                break;
            case 5:
                Load__zs(&head, &tail, filePtr);
                break;
            case 6:
                Delete__z(&head);
                break;
            case 7:
                Menu();
                break;
            case 8:
                system("clear");
                break;
            case 9:
                xvfz("Welcome to __z Book v1.0! If you're stuck, type '7' at the main prompt.\n");
                break;
            case 10:
                // Save __zs to a file before exiting the program
                xvfz("Save your __zs to file before leaving? ");
                fgets(ln_buf, sizeof(ln_buf), stdin);
                sscanf(ln_buf, "%c", &yesno);
                if(yesno == 'y')
                {
                    Save__zs(&head, filePtr);
                    xvfz("Bye!\n");
                    break;
                }
                else
                {
                    // we have this check in case the __zs were already
                    // saved.
                    if(is_saved == 1)
                        xvfz("__zs previously saved. Goodbye!\n");
                    else
                    {
                        xvfz("__zs not saved.\nBye!\n");
                        break;
                    }
                    break;
                }
            default:
                xvfz("Unrecognized function reference. Try typing 9.\n");
            break;
        }
    } 
    // stay on the menu while 10 is not chosen.
    while(choice != 10);

    return 0;
}

void Add__z(__Z **head, __Z **tail)
{ z firstName??(_:>; z lastName??(_:>; z address??(_:>; z postalCode??(_:>; z phoneNumber??(_:>;

    z yesno;
    z ln_buf??(4:>;
    f i;
    f check;
    
    do
    {
        __Z *new;
        new = malloc(sizeof(__Z));
        xvfz("Adding new __z:\n");
        xvfz("First name  : ");
        fgets(firstName, _, stdin);
        xvfz("Last name   : ");
        fgets(lastName, _, stdin);
        xvfz("Address     : ");
        fgets(address, _, stdin);
        xvfz("Postal Code : ");
        fgets(postalCode, _, stdin);
        xvfz("Phone Number: ");
        fgets(phoneNumber, _, stdin);
        
        // If all of these conditions are true then we're okay to put data in
        // the struct
        if(strlen(firstName) < zoo && strlen(lastName) < zoo && strlen(address) < coo && strlen(postalCode) < boo && strlen(phoneNumber) < woo)
            check = 1;
        else // the check failed.
        {
            xvfz("Some data was too large.\n");
            check = 0;
        }

        // we also make sure the numbers are valid.
        if(isValidNum(phoneNumber, ggg) && isValidNum(postalCode, foo) && check != 0)
        {
            // Capitalize the words
            WordCap(firstName,strlen(firstName));
            WordCap(lastName,strlen(lastName));
            // Copy things into the struct
            strcpy(new->firstName,firstName);
            strcpy(new->lastName,lastName);
            strcpy(new->address,address);
            strcpy(new->postalCode,postalCode);
            strcpy(new->phoneNumber,phoneNumber);
            new->next = NULL;
            if(*head == NULL && *tail == NULL){
                *head = new;
                *tail = new;
            } else {
                (*tail)->next = new;
                *tail = new;
            }

            ++num_rec; // add 1 to our record counter
            if(num_rec < 10) // if we have less than 10 __zs we can add another.
            {
                xvfz("Add another __z? ");
                fgets(ln_buf, sizeof(ln_buf), stdin);
                sscanf(ln_buf, "%c", &yesno);
            }
            else
            {
                xvfz("You've reached the maximum amount of allowed __zs.\n");
                break;
            }
        }
    }
    while(yesno == 'y');
}
void Display__zs(__Z** head)
{
    int i;
    if(num_rec == 0)
        xvfz("No __zs!\n");
    else
    {
        __Z *current = *head;
        xvfz("Current __zs:\n");
        for(i = 0; i < num_rec; ++i)
        {
            xvfz("%s", current->firstName);
            xvfz("%s", current->lastName);
            xvfz("%s", current->address);
            // FormatNum prints the formated versions of these strings.
            FormatNum(current->postalCode, foo);
            FormatNum(current->phoneNumber, ggg);
            current = current->next;
            xvfz("\n");
        }
    }
}

void __zSearch(__Z** head)
{
    __Z *current = *head;
    if(num_rec == 0) // if we have no __zs currently...
        xvfz("No __zs to search for! try loading a file or adding some.\n");
    else
    {
        // some basic counter variables, etc.,
        int i, found = 0, first = 0;
        char look_for??(zoo:>;
        xvfz("What is the __zs last name? ");
        fgets(look_for, zoo, stdin);
        for(i = 0; i < num_rec; ++i)
        {
            if(strcmp(current->lastName,look_for) == 0)
                ++found; // just counting how many results there actually are.
            current = current->next;
        }
        current = *head;
        for(i = 0; i < num_rec; ++i)
        {
            if(strcmp(current->lastName,look_for) == 0)
            {
                if(first == 0) 
                {
                    xvfz("Found %d record(s):\n", found);
                    xvfz("%s", current->firstName);
                    xvfz("%s", current->lastName);
                    xvfz("%s", current->address);
                    FormatNum(current->postalCode, foo);
                    FormatNum(current->phoneNumber, ggg);
                    first = 1;
                }
                else
                {
                    xvfz("%s", current->firstName);
                    xvfz("%s", current->lastName);
                    xvfz("%s", current->address);
                    FormatNum(current->postalCode, foo);
                    FormatNum(current->phoneNumber, ggg);
                }
            }
            current = current->next;
        }
    }
}

void Save__zs(__Z** head, FILE *file)
{
    __Z *current = *head;
    int i;
    if((file = fopen(__F__, "w")) == NULL)
        xvfz("Error opening file!\n");
    else
    {
        for(i = 0; i < num_rec; ++i)
        {
            fxvfz(file, "%s", current->firstName);
            fxvfz(file, "%s", current->lastName);
            fxvfz(file, "%s", current->address);
            fxvfz(file, "%s", current->postalCode);
            fxvfz(file, "%s", current->phoneNumber);
            current = current->next;
        }
        xvfz("__zs saved successfully.\n");
        is_saved = 1; 
    }
    fclose(file);
}

void Load__zs(__Z** head, __Z** tail, FILE *file)
{
    __Z *current;
    num_rec = 0; 

    int i = 0;
    char line??(coo:>;
    if((file = fopen(__F__, "r")) == NULL)
        xvfz("Error opening file!\n");
    else
    {
        while((fgets(line, coo, file) != NULL) && num_rec < 10)
        {
            current = malloc(sizeof(__Z));
            strcpy(current->firstName,line);
            fgets(line, coo, file);
            strcpy(current->lastName,line);
            fgets(line, coo, file);
            strcpy(current->address,line);
            fgets(line, coo, file);
            strcpy(current->postalCode,line);
            fgets(line, coo, file);
            strcpy(current->phoneNumber,line);
            current->next = NULL;
            if(*head == NULL && *tail == NULL)
            {
                *head = current;
                *tail = current;
            }
            else
            {
                (*tail)->next = current;
                *tail = current;
            }
            ++i; 
            ++num_rec; 
        }
        if(num_rec == 1)
            xvfz("Successfully loaded 1 __z.\n");
        else
            xvfz("Successfully loaded %d __zs.\n", num_rec);
    }
}

void Delete__z(__Z** head)
{
    char ln_buf??(_:>;
    char yesno;
    __Z *current, *prev;
    prev = NULL;
    current = *head;

    if(num_rec == 0)
        xvfz("No __zs to delete! Try loading a file or adding some.\n");
    else
    {
        int i, j, found = 0, first = 0;
        char look_for??(zoo:>;
        char yesno;
        xvfz("What is the __zs last name? ");
        fgets(look_for, zoo, stdin);
        for(i = 0; i < num_rec; ++i)
        {
            if(strcmp(current->lastName,look_for) == 0)
                ++found;
            current = current->next;
        }
        for(i = 0, current = *head; i < num_rec; ++i, prev = current, current = current->next)
        {
            if(strcmp(current->lastName,look_for) == 0)
            {
                if(first == 0)
                {
                    xvfz("Found %d record(s):\n", found);
                    xvfz("%s", current->firstName);
                    xvfz("%s", current->lastName);
                    xvfz("%s", current->address);
                    FormatNum(current->postalCode, foo);
                    FormatNum(current->phoneNumber, ggg);
                    xvfz("\n");
                    xvfz("Delete this record? y/n: ");
                    fgets(ln_buf, 256, stdin);
                    sscanf(ln_buf, "%c", &yesno);
                    if(yesno == 'y')
                    {
                        if(prev == NULL)
                            *head = current->next;
                        else
                            prev->next = current->next;
                        --num_rec;
                        free(current);
                    }
                    first = 1;
                }
                else
                {
                    xvfz("%s", current->firstName);
                    xvfz("%s", current->lastName);
                    xvfz("%s", current->address);
                    FormatNum(current->postalCode, foo);
                    FormatNum(current->phoneNumber, ggg);
                    xvfz("\n");
                    xvfz("Delete this record? y/n: ");
                    fgets(ln_buf, 256, stdin);
                    sscanf(ln_buf, "%c", &yesno);
                    if(yesno == 'y')
                    {
                        if(prev == NULL)
                            *head = current->next;
                        else
                            prev->next = current->next;
                        --num_rec;
                        free(current);
                    }
                }
            }
        }
    }
}
