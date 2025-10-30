# Addressbook-chetank-
A C-based Address Book Management System that lets you add, search, edit, and delete contacts with full input validation and CSV file storage for data persistence.

# 📇 Address Book Management System (C Project)

A **C-based Address Book Management System** that allows users to **add, list, search, edit, and delete contacts** with proper data validation and file storage.  
The project ensures **data persistence** through a CSV file and checks for **duplicate entries** (mobile number and email) to maintain clean data integrity.

---

## 🚀 Features

✅ **Add Contact**
- Validates name, mobile number, and email before saving  
- Prevents duplicate entries for mobile numbers and emails  

✅ **List Contacts**
- Displays all stored contacts in a well-formatted table  

✅ **Search Contacts**
- Search by:
  - Name  
  - Mobile number  
  - Email ID  

✅ **Edit Contacts**
- Modify:
  - Name  
  - Mobile number  
  - Email  
  - Or all fields at once  

✅ **Delete Contacts**
- Delete by name, phone, or email (with confirmation prompt)  

✅ **Save and Load**
- Contacts are automatically saved to and loaded from `contacts.csv`

---
## 🧱 Project Structure

📦 AddressBook
┣ 📜 main.c
┣ 📜 contact.c
┣ 📜 contact.h
┣ 📜 contacts.csv
┗ 📜 README.md

