#include<stdio.h>
#include<string.h>
#include "validate.h"
#include "contact.h"

int validateName(char *name)//function defination for name
{
    //loop until null character
    for(int i=0;name[i]!='\0';i++)
    {
        //two spaces and dots are coming its not valid 
        if((name[i] ==' ' && name[i+1] == ' ') || (name[i] =='.' && name[i+1] == '.'))
        {
            return 0;//flase
        }
        //check for special character and digits
        if(!((name[i] >='a' && name[i] <='z') || 
        (name[i] >='A' && name[i] <='Z') ||
        (name[i] ==' ') || (name[i] =='.')))
        {
            return 0;//false
        }
    }
    return 1;//true
}

int validatePhone(char *phone)//function defination for phone number
{
    int res=0;//variable declare
    int len = strlen(phone);//calculate length of phone number
    if (len != 10)  // check exact 10 digits
    {
        printf("Error: try again enter 10 digits...😨\n");//error prompt
        return 0;//false
    }
    //loop runs length of phone number
    for (int i = 0; i < len; i++)
    {
        //check for digits only
        if (phone[i] >= '0' && phone[i] <= '9')
        {
            res = res * 10 + (phone[i] - '0');//string to integer
        }
        else
        {
            printf("Error: only digits allowed...❌\n");
            return 0;//false
        }
    }
    return 1;//true
}

int validateEmail(char *email)//fun defination for email.id 
{
    int len = strlen(email);//calculate length of email
    int j = 0,k,count = 0;//variable declare
    if((email[0] >='0' && email[0] <='9')|| email[0] == '@')
    {
        return 0;//false
    }
    //loop runs from 1 to length of email
    for(int i=1;i < len;i++)
    {
        if(email[i]=='@')//checking two times @
        {
            count++;//count increase by 1
            k=i;//store index of @
        }
    }
    if(count != 1)// zero or more then 1 time is @ break
    {
        return 0;
    }
    //check for character after @
    if(!(email[k+1] >='a' && email[k+1] <='z'))
    {
        return 0;
    }
    //this is one method
    /*char rev[len+1];
    for(int i=0;i<len;i++)
    {
        rev[i]=email[len-i-1];//sring reverse
    }
    rev[len] = '\0';

    char str2[]="moc.";//after .com any characters taken or not
    for(int i=0;str2[i]!='\0';i++)
    {
        if(str2[i]==rev[i])
        continue;//skip the next itteration
        else
        return 0;//false
    }*/

    //another method using inbuilt function compare
    if (len < 4 || strcmp(email + len - 4, ".com") != 0)//email + len - 4  ----> points to " .com"
    {
        return 0;
    }
    
    //while(j < len-4)//len-4 means .com was not checking
    while (j < len)//
    {
        
        if((email[j] >='a' && email[j] <= 'z') ||//only lower case
        (email[j] >= '0' && email[j] <= '9') ||//check digits
           email[j] == '.' || email[j] == '_'  || email[j] == '@')//check dot, underscore and @
        {
            j++;//increase j by 1
            continue;//its true goto next itteration
        }
        else
        return 0;//false
    }
    return 1;//true
} 