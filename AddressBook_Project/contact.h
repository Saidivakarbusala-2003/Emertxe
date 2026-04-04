#ifndef CONTACT_H//include guard start
#define CONTACT_H//contact guard

#define MAX_CONTACTS 100//max contacts written in macro

typedef struct {//struct for contact
    char name[50];//string array declare in name
    char phone[20];//string array declare in phone
    char email[50];//string array declare in email
} Contact;//struct for contact

typedef struct {
    Contact contacts[100];//array of struct contact
    int contactCount;//variable to store contact count
} AddressBook;//struct for addressbook

void createContact(AddressBook *addressBook);//function declare for createcontact
void searchContact(AddressBook *addressBook);//function declare for searchcontact
void editContact(AddressBook *addressBook);//function declare for editcontact
void deleteContact(AddressBook *addressBook);//function declare for deletecontact
void listContacts(AddressBook *addressBook);//function declare for listcontact
void initialize(AddressBook *addressBook);//function declare for initialize
void saveContactsToFile(AddressBook *AddressBook);//function declare for save contact to file
void sortContacts(AddressBook *addressBook);//function declare for sortcontacts

#endif
