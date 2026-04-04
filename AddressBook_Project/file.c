#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)//function defination for save contact to file
{
    sortContacts(addressBook);//function call for sortcontacts
    
    FILE *fp;//file pointer declare

    //open file in write mode
    if((fp = fopen("contacts.csv", "w")) == NULL)
    {
        //printing to stderr it can be file folder location ,can use file ptr or any std streams
        //fprintf to stderr for error handling
        fprintf(stderr,"Can't open output file text.txt...!\n");
        return; //exit from function
    }
    
    fprintf(fp,"#%d\n",addressBook->contactCount);//writing contact count to file
    //loop runs contactCount times
    for(int i = 0;i<addressBook->contactCount;i++)
    {
        //writing each contact details to file
        fprintf(fp,"%s, %s, %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);//close file
    
}

void loadContactsFromFile(AddressBook *addressBook)//function defination for loadcontactsfromfile
{
    FILE *fp;//file pointer declare

    //open file in read mode
    if((fp = fopen("contacts.csv", "r")) == NULL)
    {
        //printing to stderr it can be file folder location ,can use file ptr or any std streams
        //fprintf to stderr for error handling
        fprintf(stderr,"Can't open input file text.txt...!\n");
        return; //exit from function
    }
    
    fscanf(fp,"#%d\n",&addressBook->contactCount);//reading contact count from file
    //loop runs contactCount times
    for(int i = 0;i<addressBook->contactCount;i++)
    {
        //reading each contact details from file
        fscanf(fp,"%[^,], %[^,], %[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);//close file
    
}
