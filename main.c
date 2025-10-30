/*Name: Chetan Kittur
  Date: 21/09/2025
  Description:The project is a Address Book system designed to manage  contact details.It provides options to add, search, edit, delete, and save contacts using a menu-driven interface.
              The implementation highlights the use of structures and file handling for efficient data storage and retrieval.
*/
/*
1).int create_contact(AddressBook *): This function is responsible for creating a new contact in the address book. It takes the user’s input for name, phone number, and email, then validates them for correctness. If all inputs are valid, the new contact is stored in the address book.

2).void list_contacts(AddressBook *): This function displays all the contacts saved in the address book. It prints each contact’s details such as name, phone number, and email in a clear format. The user can easily browse through all stored contacts using this function.

3).int search_contacts(AddressBook *): This function allows the user to search for a contact by name, phone number, or email. It scans the address book and returns the index of the contact if found. If the contact does not exist, it notifies the user accordingly.

4).int edit_contact(AddressBook *): This function is used to edit an existing contact’s information. It provides a menu where the user can choose to update the name, phone number, email, or all details. Validation and duplicate checks are performed to ensure the new details are correct.

5).int delete_contact(AddressBook *): This function removes a selected contact from the address book. After deletion, the remaining contacts are shifted so that the list stays continuous. It ensures safe deletion by confirming the user’s choice to prevent mistakes.

6).int save_contacts(AddressBook *): This function saves all the current contacts into a file on disk. It ensures that the data remains available even after the program is closed. The function returns success or failure based on whether the file operation was completed successfully.
*/
#include <stdio.h>
#include "contact.h"
/* Structure declaration */
int main()
{
    /* Variable and structre defintion */
    char option;
    AddressBook addressbook;
    addressbook.contact_count = 0;
     init_intialization(&addressbook);
    while (1)
    {
        printf("\nAddress book menu\n"); /* Give a prompt message for a user */
        printf("1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contact\n7.Exit\n");
        printf("Enter the option (1 to 7): ");
        scanf(" %c", &option);
        getchar();
        switch (option) /* Based on choosed option */
        {
        case '1':
        {
            create_contact(&addressbook);
            break;
        }

        case '2':
        {
            printf("Search Contact menu : \n1.Search by Name \n2.Search by Phone number\n3.Search by Mail ID\n4. Exit\nEnter the option(1 to 4) :"); /* Providing menu */
            search_contacts(&addressbook);
            break;
        }
        case '3':
          //printf("\nEdit Contact Menu\n1.Search by Name\n2.Search by Phone number\n3.Search by Email ID\n4.Exit\nEnter your Choice(1 to 4): "); /* Providing menu */
            edit_contact(&addressbook);
            break;

        case '4':
        {
            //printf("\nDelete Contact Menu\n1.Search by Name\n2.Search by Phone number\n3.Search by Email\n4.Exit\nEnter the Choice(1 to 4): "); /* Providing menu */
            delete_contact(&addressbook);
            break;
        }
        case '5':
        {
            printf("List Contacts:");
            list_contacts(&addressbook);
            break;
        }
        case '6':
            printf("Saving contacts\n");
            save_contacts(&addressbook);
            break;
        case '7':
            printf("INFO : Save and Exit...\n");
            save_contacts(&addressbook);
            return 0;
        default:
            printf("Invalid option,Please select valid option \n");
            break;
        }
    }
    return 0;
}
