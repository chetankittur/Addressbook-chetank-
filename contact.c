#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

void init_intialization(AddressBook *addressbook)
//function to  Load Contacts from File : This function loads contacts from "contacts.txt" and stores them back into the address book. 
 {
    FILE *fp;
    int count;
    fp = fopen("contacts.csv", "r");  // Open file in read mode
    if (fp == NULL) {  // If file doesn't exist or can't be opened
        printf("Error: Unable to open file for reading!\n");
        return;  // Return failure
    }
    // Read the total number of contacts from the file
    fscanf(fp, "#%d\n", &count);
    addressbook->contact_count = 0;  // Reset current contact count
    // Read each contact from file line by line
    for (int i = 0; i < count; i++) {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n",addressbook->contact_details[addressbook->contact_count].Name,addressbook->contact_details[addressbook->contact_count].Mobile_number, addressbook->contact_details[addressbook->contact_count].Mail_ID);

        addressbook->contact_count++;  // Increment after loading each contact
    }
    fclose(fp);  // Close the file 
}

 //function to validate name:Checks if the given name contains only alphabets and spaces.Returns 1 if valid, otherwise 0.
int valid_name(char *name) 
{
    int i = 0;
    while (name[i] != '\0')  // Loop through each character in name
    {
        if (!(isalpha(name[i]) || name[i] == ' '))  // Allow only alphabets or spaces
            return 0;  // Invalid character found return 0
        i++;
    }
    return 1;  // return 1 if name is valid
}
//function to validate phonenumber:Ensures the phone number is 10 digits, starts with 6–9, and contains only numeric digits.
int valid_phonenumber(char *phonenumber)
{
    int len = strlen(phonenumber);
    if (len != 10) {// Must be exactly 10 characters
      printf("Mobile number must be 10 digits.\n");
    
        return 0;
    }

    if (phonenumber[0] < '6' || phonenumber[0] > '9') { // First digit should be 6–9
        printf("Mobile number must start with 6 0r 7 0r 8 0r 9 digit.\n");
        return 0;
    }
    for (int j = 0; phonenumber[j] != '\0'; j++)  // Check all characters are digits
    {
        if (!isdigit(phonenumber[j])) { // If any non-digit is found then return 0
           printf("Mobile number should contain only digits.\n");
            return 0;
        }
    }
    return 1;  // return 1 if Valid phone number
}

//function to validate email:Validates an email by checking format, allowed characters, presence of one '@', and ensuring it ends with ".com".

int valid_email(char *email) 
{
    int len = strlen(email);
    int i, at_count = 0, at_index = -1, dot_count = 0;

    if (len < 5)  // checks the lenght of email
    {
        printf("Mail ID length should be minimum 5 character\n");
        return 0;
    }

    // Convert all entered characters from user  to lowercase
    for (i = 0; i < len; i++) 
    {
        email[i] = tolower(email[i]);
    }

    if (!isalpha(email[0]))  //if  first character is not  alphabet then return 0
    {
        printf("Mail ID should start with alphabet character only.\n");
        return 0;
    }

    for (i = 0; i < len; i++) 
    {
        char ch = email[i];

        if (!(isalnum(ch) || ch == '@' || ch == '.'))  // Allow only letters, numbers, @, .
        {
            printf("Mail ID must contain alphabets,digits,@ and dot.\n");
            return 0;
        }

        if (ch == '.')  // Count dots
        {
            dot_count++;
            if (i > 0 && email[i - 1] == '.')  // No consecutive dots allowed
            {
                printf("Mail ID should not contain consecutive dots\n");
                return 0;
            }
        }

        if (ch == '@')  // Count '@' and remember position
        {
            at_count++;
            at_index = i;
        }
    }

    if (at_count != 1)  // Must have exactly one '@'
    {
        printf("Mail ID should contain only one '@' character.\n" );
        return 0;
    }

    if (at_index == 0 || at_index == len - 1)  // '@' cannot be first or last
    {
        printf("Mail ID should not conatain '@' character at first or last.\n");
        return 0;
    }

    if (email[at_index + 1] == '.')  // Domain cannot start with a dot
    {
        printf("Mail ID domain cannot start with a dot.\n");
        return 0;
    }

    if (dot_count != 1)  // Must contain only one dot (for ".com")
    {
        printf("Mail ID must contain only one dot.\n");
        return 0;
    }

    // Checks email ends with ".com"
    if (email[len - 4] != '.' || email[len - 3] != 'c' || email[len - 2] != 'o' || email[len - 1] != 'm') 
    {
        printf("Mail ID must end with '.com'\n");
        return 0;
    }

    return 1;  // if email is Valid return 1
}
// function to check duplicate mobile number: Checks if the given phone number already exists in the address book, Skips the contact at skip_index (useful when editing a contact), Returns 1 if duplicate found, otherwise 0.
int duplicate_mobile(AddressBook *addressbook, char *phonenumber, int skip_index) 
{
    for (int i = 0; i < addressbook->contact_count; i++) 
    {
        // Compare only if not skipping the given index
        if (i != skip_index && strcmp(addressbook->contact_details[i].Mobile_number, phonenumber) == 0) 
        {
            return 1;  // Duplicate phone number found
        }
    }
    return 0;  // No duplicate 
}

//function to check  duplicate email ID:Checks if the given email already exists in the address book, Skips the contact at skip_index (useful when editing a contact),Returns 1 if duplicate found, otherwise 0.
int duplicate_email(AddressBook *addressbook, char *mail, int skip_index) 
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        // Compare only if not skipping the given index
        if (i != skip_index && strcmp(addressbook->contact_details[i].Mail_ID, mail) == 0)
        {
            return 1;  // Duplicate email found
        }
    }
    return 0;  // No duplicate
}

//function to  create contact: Adds a new contact to the addressbook, Validates name, phone number, and email before saving,Also checks for duplicates to avoid repeated entries.
int create_contact(AddressBook *addressbook) {
    char ch;
    do {
        Contacts temp;
        // Validate name input
        while (1) {
            printf("Enter the Name: ");
            scanf(" %[^\n]", temp.Name);  // Read full line (with spaces)
            if (valid_name(temp.Name))  // Ensure name contains only alphabets/spaces
                break;
            printf("Invalid name, Name should contain only alphabets and space.\n");
        }
        // Validate phone number input
        while (1) {
            printf("Enter the Phone Number: ");
            scanf(" %[^\n]", temp.Mobile_number);
            if (!valid_phonenumber(temp.Mobile_number))  // checks for entered mobile number  is valid or not
            {
                continue;
            }
            if (duplicate_mobile(addressbook, temp.Mobile_number, -1))  // Check for duplicates for mobile number
            {
                printf("Phone number already exists!\n");
                continue;
            }
            break;  // Valid phone number
        }
        // Validate email input
        while (1) 
        {
            printf("Enter the Email ID: ");
            scanf(" %[^\n]", temp.Mail_ID);
            if (!valid_email(temp.Mail_ID)) {  // check the entered mail id is valid or not
                continue;
            }
            if (duplicate_email(addressbook, temp.Mail_ID, -1))  // Check for duplicates of mail id
            {
                printf("Email already exists!\n");
                continue;
            }
            break;  // Valid email
        }
        // Save the new contact in the address book
        addressbook->contact_details[addressbook->contact_count++] = temp;
        printf("Contact added successfully!\n");
        // Ask if the user wants to add another contact
        printf("Do you want to add another contact? (y/n): ");
        scanf(" %c", &ch);
        getchar();
    } while (ch == 'y' || ch == 'Y');
    return 1;  // Successfully added
}
// function to list_contacts: Displays all the contacts stored in the address book,in a neatly formatted table. Prints a message if empty.
void list_contacts(AddressBook *addressbook) {
    if (addressbook->contact_count == 0) {  // No contacts case
        printf("\n┌───────────────────────────────┐\n");
        printf("│       No contacts found!      │\n");
        printf("└───────────────────────────────┘\n");
        return;
    }
    // Print header table format
    printf("\n┌─────┬──────────────────────┬──────────────┬──────────────────────────┐\n");
    printf("│SI.No│ Name                 │ Phone Number │ Email ID                 │\n");
    printf("├─────┼──────────────────────┼──────────────┼──────────────────────────┤\n");
    // Print each contact row
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf("│ %-3d │ %-20s │ %-12s │ %-24s │\n", i + 1, addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number, addressbook->contact_details[i].Mail_ID);
    }

    // Print footer line
    printf("└─────┴──────────────────────┴──────────────┴──────────────────────────┘\n");
}

//function for search contacts: It allows searching for a contact by name, phone, or email,Prints contact details if found, otherwise shows "Not found".
int search_contacts(AddressBook *addressbook) {
    char details[100];
    char option;
    int found = 0, matched_indices[100], match_count = 0;

    scanf(" %c",&option);  // Take user search choice
    getchar();
    found = 0;
    match_count = 0;

    if (option == '1') {  // Search by Name
        printf("Enter the name: ");
        scanf(" %[^\n]", details);
        for (int i = 0; i < addressbook->contact_count; i++) {
            if (strcasecmp(details, addressbook->contact_details[i].Name) == 0) {
                matched_indices[match_count++] = i;  // Store index of match
                found = 1;
            }
        }
        if (!found) {
            printf("Entered name is not found.\n");
        } else if (match_count == 1) {  // Single match
            int idx = matched_indices[0];
            printf("------Contact details------\nName: %s | Phone: %s | Email: %s\n",addressbook->contact_details[idx].Name,addressbook->contact_details[idx].Mobile_number, addressbook->contact_details[idx].Mail_ID);
        } else {  // Multiple matches
            printf("------Contacts details------\n");
            for (int j = 0; j < match_count; j++) {
                printf("%d. Name: %s | Phone: %s | Email: %s\n", j+1, addressbook->contact_details[matched_indices[j]].Name, addressbook->contact_details[matched_indices[j]].Mobile_number,addressbook->contact_details[matched_indices[j]].Mail_ID);
            }
        }
    }
    else if (option == '2') {  // Search by Phone
        printf("Enter the phone number: ");
        scanf(" %[^\n]", details);
        for (int i = 0; i < addressbook->contact_count; i++) {
            if (strcasecmp(details, addressbook->contact_details[i].Mobile_number) == 0) {
                printf("Match found:\nName: %s | Phone: %s | Email: %s\n", addressbook->contact_details[i].Name, addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                found = 1;
                break;
            }
        }
        if (!found) printf("Entered phone number is not found.\n");
    }
    else if (option == '3') {  // Search by Email
        printf("Enter the email ID: ");
        scanf(" %[^\n]", details);
        for (int i = 0; i < addressbook->contact_count; i++) {
            if (strcasecmp(details, addressbook->contact_details[i].Mail_ID) == 0) {
                printf("Match found:\nName: %s | Phone: %s | Email: %s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number, addressbook->contact_details[i].Mail_ID);
                found = 1;
                break;
            }
        }
        if (!found) printf("Entered mail ID is Not found.\n");
    }
    else if (option == '4') {
        return 0;  // Exit to main menu
    }
    else {
        printf("Invalid choice,Please choose valid choice\n");
    }

    return 1;  // Always return to main menu after search
}
// Function to edit details of a selected contact
int edit_contact_details(AddressBook *addressbook, int index) {
    char choice;

    while (1) {
        // Show which contact is being edited
        printf("\nEditing Contact [%d]\n", index + 1);
        printf("Current Details:\n");
        printf("Name: %s\n", addressbook->contact_details[index].Name);
        printf("Phone: %s\n", addressbook->contact_details[index].Mobile_number);
        printf("Email: %s\n", addressbook->contact_details[index].Mail_ID);

        // Menu options for editing
        printf("\nWhich detail do you want to edit?\n");
        printf("1. Name\n2. Mobile Number\n3. Email ID\n4. Edit All Details\n5. Exit\n");
        printf("Enter your choice (1 to 5): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');   // clear newline

        switch (choice) {
            case '1':  // Edit Name
                while (1) {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressbook->contact_details[index].Name);
                    if (valid_name(addressbook->contact_details[index].Name))
                        break;
                }
                printf("Name updated successfully!\n");
                break;

            case '2':  // Edit Mobile
                while (1) {
                    printf("Enter new mobile number: ");
                    scanf(" %[^\n]", addressbook->contact_details[index].Mobile_number);
                    if (!valid_phonenumber(addressbook->contact_details[index].Mobile_number)) {
                        continue;
                    }
                    if (duplicate_mobile(addressbook, addressbook->contact_details[index].Mobile_number, index)) {
                        printf("Phone number already exists!\n");
                        continue;
                    }
                    break;
                }
                printf("Mobile number updated successfully!\n");
                break;

            case '3':  // Edit Email
                while (1) {
                    printf("Enter new email ID: ");
                    scanf(" %[^\n]", addressbook->contact_details[index].Mail_ID);
                    if (!valid_email(addressbook->contact_details[index].Mail_ID)) {
                        continue;
                    }
                    if (duplicate_email(addressbook, addressbook->contact_details[index].Mail_ID, index)) {
                        printf("Email ID already exists!\n");
                        continue;
                    }
                    break;
                }
                printf("Email updated successfully!\n");
                break;

            case '4':  // Edit All
                // Edit Name
                while (1) {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressbook->contact_details[index].Name);
                    if (valid_name(addressbook->contact_details[index].Name))
                        break;
                }
                // Edit Mobile
                while (1) {
                    printf("Enter new mobile number: ");
                    scanf(" %[^\n]", addressbook->contact_details[index].Mobile_number);
                    if (!valid_phonenumber(addressbook->contact_details[index].Mobile_number)) {
                        continue;
                    }
                    if (duplicate_mobile(addressbook, addressbook->contact_details[index].Mobile_number, index)) {
                        printf("Phone number already exists!\n");
                        continue;
                    }
                    break;
                }
                // Edit Email
                while (1) {
                    printf("Enter new email ID: ");
                    scanf(" %[^\n]", addressbook->contact_details[index].Mail_ID);
                    if (!valid_email(addressbook->contact_details[index].Mail_ID)) {
                        continue;
                    }
                    if (duplicate_email(addressbook, addressbook->contact_details[index].Mail_ID, index)) {
                        printf("Email already exists!\n");
                        continue;
                    }
                    break;
                }
                printf("All details updated successfully!\n");
                break;

            case '5':  // Exit
                return 0;

            default:
                printf("Please select a valid choice, try again.\n");
        }
    }
}

// Function to Edit Contact: Based on the user requirements
int edit_contact(AddressBook *addressbook){
    char details[100];
    char option;
    int found, matched_indices[100], match_count, chosen_serial;

    while(1){
        printf("\nEdit Contact Menu\n1.Search by Name\n2.Search by Phone number\n3.Search by Email ID\n4.Exit\nEnter your Choice(1 to 4): ");
        scanf(" %c",&option);
        while (getchar() != '\n');  // clear buffer
        match_count = 0; 
        found = 0;

        switch(option){
            case '1':
                // Search by Name
                printf("Enter the name: ");
                scanf(" %[^\n]", details);
                for(int i = 0; i < addressbook->contact_count; i++){
                    if(strcasecmp(details, addressbook->contact_details[i].Name) == 0){
                        matched_indices[match_count++] = i;
                        found = 1;
                    }
                }
                if(!found){
                    printf("Entered name is not found.\n");
                    break;
                }
                if(match_count == 1){
                    // Directly edit if only one match
                    edit_contact_details(addressbook, matched_indices[0]);
                } else {
                    // Multiple matches → ask user to pick
                    for(int j = 0; j < match_count; j++){
                        printf("%d. Name:%s | Phone:%s | Email:%s\n",j+1,addressbook->contact_details[matched_indices[j]].Name,addressbook->contact_details[matched_indices[j]].Mobile_number, addressbook->contact_details[matched_indices[j]].Mail_ID);
                    }
                    printf("Enter serial number of contact to edit: ");
                    scanf("%d", &chosen_serial);
                    while (getchar() != '\n'); // flush buffer
                    if(chosen_serial < 1 || chosen_serial > match_count){
                        printf("\nPlease select valid option, try again.\n");
                        break;
                    }
                    edit_contact_details(addressbook, matched_indices[chosen_serial - 1]);
                }
                break;

            case '2':
                // Search by Phone
                printf("Enter the phone number: ");
                scanf(" %[^\n]", details);
                for(int i = 0; i < addressbook->contact_count; i++){
                    if(strcasecmp(details, addressbook->contact_details[i].Mobile_number) == 0){
                        printf("Contact Details:\nName:%s | Phone:%s | Email:%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                        edit_contact_details(addressbook, i); // go to edit
                        found = 1;
                        break;
                    }
                }
                if(!found) printf("Entered phone number is not found.\n");
                break;

            case '3':
                // Search by Email
                printf("Enter the email ID: ");
                scanf(" %[^\n]", details);
                for(int i = 0; i < addressbook->contact_count; i++){
                    if(strcasecmp(details, addressbook->contact_details[i].Mail_ID) == 0){
                        printf("Contact Details:\nName:%s | Phone:%s | Email:%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                        edit_contact_details(addressbook, i);
                        found = 1;
                        break;
                    }
                }
                if(!found) printf("Entered mail ID is not found.\n");
                break;

            case '4':
                return 0; // Exit to main menu

            default:
                printf("\nPlease select valid choice, try again.\n");
        }
    }
}
//function to delete contacts:It will delete the contact based on name,phone number,email id
int delete_contact(AddressBook *addressbook) {
    char details[100], confirm;
    char option;
    int found, matched_indices[100], match_count, chosen_serial;

    while (1) {
        // Delete menu
        printf("\nDelete Contact Menu\n1.Search by Name\n2.Search by Phone number\n3.Search by Email\n4.Exit\nEnter the Choice(1 to 4): ");
        scanf(" %c", &option);
        getchar();

        match_count = 0; 
        found = 0;

        switch (option) {
            // Delete by Name 
            case '1':
                printf("Enter name: ");
                scanf(" %[^\n]", details);

                // Find matches
                for (int i = 0; i < addressbook->contact_count; i++) {
                    if (strcasecmp(details, addressbook->contact_details[i].Name) == 0) {
                        matched_indices[match_count++] = i;
                        found = 1;
                    }
                }

                if (!found) {
                    printf("Entered name is not found.\n");
                    break;
                }

                if (match_count == 1) {
                    // Single match → confirm deletion
                    int del_index = matched_indices[0];
                    printf("Contact Details:\nName:%s | Phone:%s | Email:%s\n",addressbook->contact_details[del_index].Name,addressbook->contact_details[del_index].Mobile_number,addressbook->contact_details[del_index].Mail_ID);

                    printf("Do you want to delete this contact (y/n): ");
                    scanf(" %c", &confirm);

                    if (confirm == 'y' || confirm == 'Y') {
                        // Shift remaining contacts up
                        for (int j = del_index; j < addressbook->contact_count - 1; j++)
                            addressbook->contact_details[j] = addressbook->contact_details[j + 1];

                        addressbook->contact_count--;
                        printf("Contact deleted successfully.\n");
                    }
                } else {
                    // Multiple matches → list all
                    for (int j = 0; j < match_count; j++) {
                        printf("%d. Name:%s | Phone:%s | Email:%s\n", j+1,addressbook->contact_details[matched_indices[j]].Name,addressbook->contact_details[matched_indices[j]].Mobile_number,addressbook->contact_details[matched_indices[j]].Mail_ID);
                    }

                    // Choose one to delete
                    printf("Enter the serial number of contact to delete: ");
                    scanf("%d", &chosen_serial);

                    if (chosen_serial < 1 || chosen_serial > match_count) {
                        printf("Invalid choice, please select valid choice to delete\n");
                        break;
                    }

                    int del_index = matched_indices[chosen_serial - 1];
                    printf("Do you want to delete this contact (y/n): ");
                    scanf(" %c", &confirm);

                    if (confirm == 'y' || confirm == 'Y') {
                        for (int j = del_index; j < addressbook->contact_count - 1; j++)
                            addressbook->contact_details[j] = addressbook->contact_details[j + 1];

                        addressbook->contact_count--;
                        printf("\nContact deleted successfully.\n");
                    }
                }
                break;

            // Delete by Phone 
            case '2':
                printf("Enter the phone number: ");
                scanf(" %[^\n]", details);

                for (int i = 0; i < addressbook->contact_count; i++) {
                    if (strcasecmp(details, addressbook->contact_details[i].Mobile_number) == 0) {
                        printf("Contact Details:\nName:%s | Phone:%s | Email:%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);

                        printf("Do you want to delete this contact (y/n): ");
                        scanf(" %c", &confirm);

                        if (confirm == 'y' || confirm == 'Y') {
                            for (int j = i; j < addressbook->contact_count - 1; j++)
                                addressbook->contact_details[j] = addressbook->contact_details[j + 1];

                            addressbook->contact_count--;
                            printf("Contact deleted successfully.\n");
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Entered phone number is not found.\n");
                }
                break;  

            // Delete by Email 
            case '3':
                printf("Enter the email: ");
                scanf(" %[^\n]", details);

                for (int i = 0; i < addressbook->contact_count; i++) {
                    if (strcasecmp(details, addressbook->contact_details[i].Mail_ID) == 0) {
                        printf("Match found:\nName:%s | Phone:%s | Email:%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);

                        printf("Do you want to delete this contact (y/n): ");
                        scanf(" %c", &confirm);

                        if (confirm == 'y' || confirm == 'Y') {
                            for (int j = i; j < addressbook->contact_count - 1; j++)
                                addressbook->contact_details[j] = addressbook->contact_details[j + 1];

                            addressbook->contact_count--;
                            printf("Contact deleted successfully.\n");
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found){
                    printf("Entered mail ID is not found.\n");
                }
                break;  

            // Exit
            case '4':
                printf("Exiting delete menu...\n");
                return 0; // Exit back to main menu

            // Default: Invalid Choice
            default:
                printf("\nInvalid choice. Please select valid choice\n");
        }
    }
}
// function to Save Contacts to File:This function saves all the contacts from the addressbook into a file named "contacts.txt" in write mode.
int save_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("contacts.csv", "w");  // Open file in write mode
    if (fp == NULL) {  // Check if file failed to open
        printf("Error: Unable to open file for saving!\n");
        return 0;  // Return failure
    }

    // Save total number of contacts at the top of the file
    fprintf(fp, "#%d\n", addressbook->contact_count);

    // Save each contact as: Name,Mobile,Email
    for (int i = 0; i < addressbook->contact_count; i++) {
        fprintf(fp, "%s,%s,%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }

    fclose(fp);  // Close the file
    printf("Contacts saved successfully to contacts.csv file\n");
    return 1; 
}

