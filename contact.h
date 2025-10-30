#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

typedef struct AddressBook_Data
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

/* Function declarations */
void init_intialization(AddressBook *);
int create_contact(AddressBook *);
void list_contacts(AddressBook *);
int search_contacts(AddressBook *);
int edit_contact(AddressBook *);
int delete_contact(AddressBook *);
int save_contacts(AddressBook *);
int valid_name(char *);
int valid_phonenumber(char *);
int valid_email(char *);
int duplicate_mobile(AddressBook *, char *, int );
int duplicate_email(AddressBook *, char *, int);
int edit_contact_details(AddressBook *, int);

#endif // CONTACT_H
       // CONTACT_H