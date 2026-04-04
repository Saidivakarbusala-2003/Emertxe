/*
Name        : Busala Sai Divakar.

Date        : 10-12-2025.

Project     : Address Book Management System in C.

Description : Address Book Application

This application allows users to create, search, edit, delete, list, and save contacts in an address book.

The Address Book Management System is a menu-driven application developed in the C programming language that 
allows users to efficiently store, search, update, and manage contact information. The project demonstrates 
the use of structures, file handling, arrays, functions, string operations, and modular programming concepts in C.

This system stores essential contact details such as Name, Phone Number, and Email ID for each person. 
It provides the user with various operations including adding new contacts, viewing all saved contacts, searching
for a specific contact, editing existing information, deleting contacts, and saving data to a file for future use.

The project is designed to be simple, interactive, and easy to use, making it suitable for beginners learning 
data handling and function-based programming in C.

Expected input: Enter 1 
open menu for create contact

Enter name : Rajesh Kumar
Enter phone number : 9876543210
Enter email : rajesh@gmail.com


Expected output:

 One Contact added successfully! 😊

 */

#include <stdio.h>
#include "contact.h"

int main() {
    int choice;//variable declare for choice
    AddressBook addressBook;//struct declare for addressbook
    initialize(&addressBook); // Initialize the address book
    

    do {
        //display Address Book main menu
        printf("\n========= Address Book Menu ==========:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);//read choice from user
        getchar();//not take the enter
        
        switch (choice) {
            case 1:
                createContact(&addressBook);//function call for createcontact
                break;//exist the case 1
            case 2:
                searchContact(&addressBook);//function call for searchcontact
                break;//exist the case 2
            case 3:
                editContact(&addressBook);//function call for editcontact
                break;//exist the case 3
            case 4:
                deleteContact(&addressBook);//function call for deletecontact
                break;//exist the case 4
            case 5:          
                listContacts(&addressBook);//function call for listcontacts
                break;//exist the case 5
            case 6:
                printf("Saving sucessfully....🥳\n");
                saveContactsToFile(&addressBook);//function call for savecontacttofile
                break;//exist the case 6
                case 7:
                   printf("Exiting sucessfully....👋 \n");
                break;//exist the case 7

            //enter  >7.    
            default:
                printf("Invalid choice. Please try again...😐\n");
        }
    } while (choice != 7);//condition checking
    
       return 0;
}
