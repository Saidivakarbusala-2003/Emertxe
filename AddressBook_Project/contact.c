#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validate.h"

void listContacts(AddressBook *addressBook) //function defination for listcontact
{
    if(addressBook->contactCount == 0)//check if list is empty
    {
        printf("No contacts available to display.\n");//display message
        return;//exit function
    }
    //loop runs contactCount times
    for(int i=0;i < addressBook->contactCount;i++)
    {
        printf("\nContact %d\n",i+1);//display contact number
        printf("Name = %s\n",addressBook->contacts[i].name);//display name
        printf("Phone = %s\n",addressBook->contacts[i].phone);//display phone number
        printf("Email = %s\n",addressBook->contacts[i].email);//display email
        printf("-------------------------------!\n");
    }
}

void initialize(AddressBook *addressBook) //function defination for initialize
{
    addressBook->contactCount = 0;//contactCount ass the value
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);

}

void saveAndExit(AddressBook *addressBook) //function defination for save and exit
{
    saveContactsToFile(addressBook);
     // Save contacts to file

    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook) //function defination forcreatecontact
{
	/* Define the logic to create a Contacts */

    char name[30];//string array declare
    int x;//variable to store validation result
    do
    {
        printf("Enter the name (digits and special character not allowed) : ");//prompt using the name 
        scanf("%[^\n]",name);//read the name for user
        getchar();//consume newline character
        x = validateName(name);//function call name

        if(x == 0)
        {
            printf("Invalid name,Try again...❌\n");
        }
        
    } while (x == 0);//condition checking
    printf("Name stored sucessfully : %s\n",name);//display the name stored sucessfully

    
    char phone [20];//string array declare
    int res,flag;//variable declare 
    do{
        printf("Enter only digits (characters and special character not allowed) : ");//promt using the phone number
        scanf("%s",phone);//read the phone number for user
        getchar();//not take the enter
        res = validatePhone(phone);//function call for phone number

        if(res == 0)
        {
            printf("Invalid number,try again...❌\n");
        }
        else
        {
            flag = 0;
            //loop runs from contactCount times
            for(int i=0;i < addressBook->contactCount;i++)
            {
                //comparing the present phone num and already stored phone num equal or not
                if(strcmp(phone,addressBook->contacts[i].phone) == 0)
                {
                    flag = 1;//1 assign to flag
                    break;//stop searching once found
                }
            }
            if(flag)
            {
                printf("Phone number already exists, try again...😮\n");//phone num already exists
                res = 0;//again read
            }
        }
    }while(res == 0);//conditon checking
    printf("Phone number stored sucessfully : %s\n",phone);//display the phone number stored sucessfully


    char email [50];//string array declare
    int z,flag1;//variable declare
    do
    {
        printf("Enter the mail (ex - xyz@gmail.com): ");//promt using the mail
        scanf("%s",email);//read the mail for user
        getchar();
        z=validateEmail(email);//function call for  email
        if(z == 0)
        {
            printf("Invalid email,Try again...❌\n");
        }
        else
        {
            flag1 = 0;//variable ass
            //loop runs contactCount times
            for(int i=0;i < addressBook->contactCount;i++)
            {
                //using string comparation to check found or not
                if(strcmp(email,addressBook->contacts[i].email) == 0)
                {
                    flag1 = 1;
                    break;//stop searching once found
                }
            }
            if(flag1)
            {
                printf("Email.id already exists, try again...😮\n");//email already exists
                z = 0;//again read
            }
        }
    }while(z == 0);//condition checking
    printf("Email stored sucessfully : %s",email);//display the email stored sucessfully
 
    //copy the name into structure
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    //copy the phone number into structure
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    //copy the email into structure
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);

    addressBook->contactCount++;//increase the contactCount by 1
    printf("\nOne Contact created sucessfully...🤗\n");//display contact created sucessfully

}

void searchContact(AddressBook *addressBook) //function defination for searchcontact
{
    /* Define the logic for search */
    int choice;//variable declare
    do {
        //display search menu
        printf("\n=======Search Menu=======\n");
        printf("1. Search a name\n");
        printf("2. Search a phone number\n");
        printf("3. Search a email.id\n");
        printf("4. Exit\n");
        printf("Enter a choice : ");
        scanf("%d", &choice);
        getchar();//not take the enter

        switch (choice)
        {
            case 1: 
            {
                char name[20];
                int matchIndexes[50];   // store matching contact indexes
                int found = 0;

                printf("Enter a name: ");//prompt using the name
                scanf("%[^\n]", name);//read input from user
                getchar();//not take the enter

                // search the name
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    //compare the name found or not
                    if (strcmp(name, addressBook->contacts[i].name) == 0)
                    {
                        printf("\nContact %d\n",i+1);//display contact number
                        printf("Name = %s\n",addressBook->contacts[i].name);//display name
                        printf("Phone = %s\n",addressBook->contacts[i].phone);//display phone number
                        printf("Email = %s\n",addressBook->contacts[i].email);//display email
                        printf("-------------------------------!\n");
                        matchIndexes[found] = i;//store matching index
                        found++;//increase found by 1
                    }
                }

                // No match
                if (found == 0)
                {
                    printf("Contact not found... 😊\n");
                    break;//exit the case 1
                }
                if (found == 1)
                {
                    break;
                }
                // More than 1 match → Show phone/email/exit menu
                int pick;
                do {
                    //display multiple contacts found menu
                    printf("\nMultiple contacts found for '%s'\n", name);
                    printf("1. Enter phone numbers to search\n");
                    printf("2. Enter emails to search\n");
                    printf("3. Exit\n");
                    printf("Enter choice: ");
                    scanf("%d", &pick);
                    getchar();//not take the enter

                    switch (pick)
                    {
                    case 1:
                    {
                        char phone[20];//string array declare
                        int count1 = 0;//variable declare
                        printf("Enter a phone number📱 : ");//prompt using the phone number
                        scanf(" %[^\n]",phone);//read input from user
                        //loop runs contactCount times
                        for(int i = 0;i < addressBook->contactCount;i++)
                        {
                            //comparing the phone number found or not
                            if(strcmp(phone,addressBook->contacts[i].phone) == 0)
                            {
                                //phone num found enterd
                                count1++;
                                printf("-------------------------\n");
                                printf("%d Contact is matching\n",i+1);//display contact number
                                printf("Name = %s\n",addressBook->contacts[i].name);//found,display name
                                printf("Phone = %s\n",addressBook->contacts[i].phone);//found, display phone number
                                printf("Email = %s\n",addressBook->contacts[i].email);//found, display email
                                printf("-------------------------\n");
                            }

                        }
                        //phone num not found
                        if(count1 == 0)
                        {
                            printf("Contact not found...😒\n");
                        }
                        break;//exist the case 2
                    }
                    case 2:
                    { 
                        char email[50];//string array declare
                        int count2 = 0;
                        printf("Enter a email.id📧 : ");
                        scanf(" %[^\n]",email);//read input from user
                        //loop runs contactCount times
                        for(int i = 0;i < addressBook->contactCount;i++)
                        {
                            if(strcmp(email,addressBook->contacts[i].email) == 0)
                            {
                                count2++;
                                printf("-------------------------\n");
                                printf("%d Contact is found\n",i+1);//display contact number
                                printf("Name = %s\n",addressBook->contacts[i].name);//display name
                                printf("Phone = %s\n",addressBook->contacts[i].phone);//display phone number
                                printf("Email = %s\n",addressBook->contacts[i].email);//display email
                                printf("-------------------------\n");
                            }

                        }
                        //email not found
                        if(count2 == 0)
                        {
                            printf("Contact not found...😒\n");
                        }
                        break;//exist the case 2
                    }

                    case 3://user enter 3 exists the search contact
                        printf("Exiting to menu...👋\n");
                        break;

                    default://choice>3
                        printf("Invalid choice! Try again....👊\n");
                    }

                } while (pick != 3);//condition checking
                break;//exist the case 1
            }


            case 2:
            {
                char phone[20];//string array declare
                int count1 = 0;
                printf("Enter a phone number📱 : ");
                scanf(" %[^\n]",phone);//read input from user
                //loop runs contactCount times
                for(int i = 0;i < addressBook->contactCount;i++)
                {
                    if(strcmp(phone,addressBook->contacts[i].phone) == 0)
                    {
                        //phone num found enterd
                        count1++;
                        printf("-------------------------\n");
                        printf("%d Contact is found\n",i+1);//display contact number
                        printf("Name = %s\n",addressBook->contacts[i].name);//found,display name
                        printf("Phone = %s\n",addressBook->contacts[i].phone);//found, display phone number
                        printf("Email = %s\n",addressBook->contacts[i].email);//found, display email
                        printf("-------------------------\n");
                    }

                }
                if(count1 == 0)
                {
                    //phone num not found
                    printf("Contact not found...😊\n");
                }
            }
            break;//exist the case 2

            case 3:
            { 
                char email[50];//string array declare
                int count2 = 0;
                printf("Enter a email.id📧 : ");
                scanf(" %[^\n]",email);//read input from user
                //loop runs contactCount times
                for(int i = 0;i < addressBook->contactCount;i++)
                {
                    if(strcmp(email,addressBook->contacts[i].email) == 0)
                    {
                        count2++;
                        printf("-------------------------\n");
                        printf("%d Contact is found\n",i+1);//display contact number
                        printf("Name = %s\n",addressBook->contacts[i].name);//display name
                        printf("Phone = %s\n",addressBook->contacts[i].phone);//display phone number
                        printf("Email = %s\n",addressBook->contacts[i].email);//display email
                        printf("-------------------------\n");
                    }

                }
                if(count2 == 0)
                {
                    //email not found
                    printf("Contact not found...😊\n");
                }
                break;//exist the case 3
            }

            case 4:
            //usre enter 4 exists the search contact
                printf("Exiting search contact....🫣\n");
                break;//exist the case 4

            default://choice>4
                printf("Invalid choice. Please try again...😮\n");
        }
    } while (choice != 4);//condition chicking
    
}

void editContact(AddressBook *addressBook)//function defination for editcontact
{
	/* Define the logic for Editcontact */
    listContacts(addressBook);
    int contact;//which contact you editing
    printf("which contact you edit : ");
    scanf("%d",&contact);//read the contact in user
    if(contact < 1 || contact > addressBook->contactCount)//check condition
    {
        printf("Invalid contact number...😮\n");//display invalid contact number
        return;//exit function
    }
    int choice;//variable declare
    do {
        //display edit menu   
        printf("\n******** Edit Menu **********\n");
        printf("1. Edit a name\n");
        printf("2. Edit a phone number\n");
        printf("3. Edit a email.id\n");
        printf("4. Exit\n");
        printf("Enter a choice : ");
        scanf("%d", &choice);
        getchar();//not take the enter

        switch (choice)
        {
            case 1: 
            {
                char name[20];//string array declare
                do
                {
                    printf("Entar the name (not allowed digits and special character) : ");//prompt using the name 
                    scanf("%[^\n]",name);//read the name for user
                    getchar();//not take the enter
                    if(!validateName(name))
                    {
                        printf("Invalid name,Try again...❌\n");
                    }
                    
                } while (!validateName(name));//check condition
                //copy the new nmae in old name.
                strcpy(addressBook->contacts[contact-1].name,name);
                break;//exist the case 1
            }

            case 2:
            {
                char phone[20];//string array declare
                int flag,x;//variable declare
                do
                {
                    printf("Entar the phone numbers (not allowed digits and special character) : ");//prompt using the name 
                    scanf("%[^\n]",phone);//read the name for user
                    getchar();//not take enter 
                    x = validatePhone(phone);//function call and stored that variable
                    if(!x)//return value is correct number goto next
                    {
                        printf("Invalid phone number,Try again...❌\n");
                    }
                    // to check phone number already exists or not
                    else
                    {
                        flag = 0;
                        //loop runs from contactCount times
                        for(int i=0;i < addressBook->contactCount;i++)
                        {
                            //comparing the present phone num and already stored phone num equal or not 
                            if(strcmp(phone,addressBook->contacts[i].phone) == 0)
                            {
                                flag = 1;
                                break;//stop searching once found
                            }
                        }
                        if(flag)
                        {
                            //phone num already exists
                            printf("Phone number already exists, try again...😮\n");
                            x = 0;//again read
                        }
                    }
                    
                } while (x == 0);//check condition
                //cpoy the new phone num in old phone num
                strcpy(addressBook->contacts[contact-1].phone,phone);
                break;//exist the case 2
            }

            case 3:
            { 
                char email[50];//string array declare
                int flag1,y;//variable declare
                do
                {
                    printf("Entar the mail📧 (allowed-xyz@abc.com) : ");//prompt using the name 
                    scanf("%[^\n]",email);//read the email for user
                    getchar();//not take the enter
                    y = validateEmail(email);//function call and stored that variable
                    if(!y)
                    {
                        printf("Invalid email.id,Try again...❌\n");
                    }
                    else
                    {
                        flag1 = 0;//variable ass
                        //loop runs contactCount times
                        for(int i=0;i < addressBook->contactCount;i++)
                        {
                            //using string comparation to check found or not
                            if(strcmp(email,addressBook->contacts[i].email) == 0)
                            {
                                flag1 = 1;
                                break;//stop searching once found
                            }
                        }
                        if(flag1)
                        {
                            //email already exists
                            printf("Email.id already exists, try again😮\n");
                            y = 0;//again read
                        }
                    }
                    
                } while (y == 0);//check condition
                //copy the new email into old email
                strcpy(addressBook->contacts[contact-1].email,email);
                break;//exist the case 3
            }

            case 4:
            //usre enter 4 exists the edit contact
                printf("Exiting Edit contact ....🫣\n");
                break;//exist the case 4

            default:
            //enter  >4 
                printf("Invalid choice. Please try again...👍\n");
        }      
    } while (choice != 4);//condition checking
    
}

void deleteContact(AddressBook *addressBook)//function defination for deletecontact
{
	/* Define the logic for deletecontact */
    if(addressBook->contactCount == 0)//check if list is empty
    {
        printf("No contacts available to delete.\n");//display message
        return;//exit function
    }
    int choice;//variable declare
    do{  
        //display delete menu
        printf("\n========== Delete Menu ==========\n");
        printf("1. Delete a name\n");
        printf("2. Delete a phone number\n");
        printf("3. Delete a email.id\n");
        printf("4. Exit\n");
        printf("Enter a choice : \n");
        scanf("%d", &choice);
        getchar();//not take the enter

        switch(choice)
        {
            case 1:
            {
                //code for delete name
                char name[30];//string array declare
                do
                {
                    printf("Enter the name to delete contact : ");//prompt using the name
                    scanf("%[^\n]", name);//read name from user
                    getchar();//not take the enter

                }while(!validateName(name));// validate once
                
                int index = -1,count=0;//initialize index as not found and count as multiple contacts found

                // loop runs contactCount times
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].name, name) == 0)//to compare the name found or not
                    {
                        index = i;//store index
                        count++;//count increase by 1 and check multiple contacts found
                        printf("Contact %d\n",i+1);//display contact number
                        printf("Name = %s\n",addressBook->contacts[i].name);//display name
                        printf("Phone = %s\n",addressBook->contacts[i].phone);//display phone number
                        printf("Email = %s\n",addressBook->contacts[i].email);//display email
                        printf("-------------------------\n");
                    }
                } 
                if(count > 1)//multiple contacts found
                {
                    printf("Multiple contacts found with the same name. Please choice by phone number or email.id...📱📧\n");
                    break;//exit case 1
                    

                }
                else if(index == -1)
                {
                    //name not found
                    printf("Name not found!...😯\n");
                    break;//exit case 1
                }
                else
                {
                    // shift contacts left
                    for(int i = index; i < addressBook->contactCount; i++)
                    {
                        strcpy(addressBook->contacts[i].name,  addressBook->contacts[i + 1].name);// shift name in before contact
                        strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);// shift phone in before contact
                        strcpy(addressBook->contacts[i].email,  addressBook->contacts[i + 1].email);// shift email in before contact
                    }
                    addressBook->contactCount--;//reduce count by 1

                    printf("Contact deleted successfully😊.\n");//contact deleted sucessfully
                }
                break;//exist case 1
            }
                
            case 2:
            {
                //code for delete phone number
                char phone[15];//string array declare
                do
                {
                    printf("Enter the phone number to delete contact : ");//prompt using the phone number
                    scanf("%s", phone);////read phone number from user
                }while(!validatePhone(phone));// validate once


                int index = -1;//initialize index as not found

                // search that phone number
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].phone, phone) == 0)//to compare number found or not
                    {
                        index = i;//store index
                        break;//stop searching
                    }
                } 
                //phone number not found
                if(index == -1)
                {
                    printf("Phone number not found!...👍\n");
                    break;//exit the case 2
                }

                // shift contacts left
                for(int i = index; i < addressBook->contactCount; i++)
                {
                    strcpy(addressBook->contacts[i].name,  addressBook->contacts[i + 1].name);// shift name in before contact
                    strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);// shift phone in before contact
                    strcpy(addressBook->contacts[i].email,  addressBook->contacts[i + 1].email);// shift email in before contact
                }

                addressBook->contactCount--;//reduce count by 1

                printf("Contact deleted successfully😊.\n");//contact deleted sucessfully
                break;//exist the case 2
            }  
            

            case 3:
            {    //code for delete email.id
                char email[50];//string array declare
                do
                {
                    printf("Enter the email to delete contact (EX -abc@xyz.com): ");
                    scanf("%s", email);////read phone number from user
                }while(!validateEmail(email));// validate once


                int index = -1;//initialize index as not found

                // search that phone number
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].email, email) == 0)//to compare number found or not
                    {
                        index = i;//store index
                        break;//stop searching
                    }
                } 
                //phone number not found
                if(index == -1)
                {
                    printf("Email.id not found!...😑\n");
                    break;
                }

                // shift contacts left
                for(int i = index; i < addressBook->contactCount; i++)
                {
                    strcpy(addressBook->contacts[i].name,  addressBook->contacts[i + 1].name);// shift name in before contact
                    strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);// shift phone in before contact
                    strcpy(addressBook->contacts[i].email,  addressBook->contacts[i + 1].email);// shift email in before contact
                }

                addressBook->contactCount--;//reduce count by 1

                printf("Contact deleted successfully...😊\n");//contact deleted sucessfully
                break;//exist case 2
            }

            case 4:
                printf("Exiting delete contact....🫣\n");//display exit message
                return;//exit from delete function

            default:
                printf("Invalid choice. Please try again...👍\n");//enter >3
        }
    }while(choice != 4);//condation checking
}

void sortContacts(AddressBook *addressBook)//function defination for sortcontacts
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)//outer loop
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)//bubble sort
        {
            //compare adjacent contacts based on name
            if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];//swap contacts
                addressBook->contacts[j] = addressBook->contacts[j + 1];//swap contacts
                addressBook->contacts[j + 1] = temp;//swap contacts
            }
        }
    }
}


