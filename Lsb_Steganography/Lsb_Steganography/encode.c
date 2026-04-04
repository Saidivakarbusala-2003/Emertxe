#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "common.h"
#include "types.h"


uint get_image_size_for_bmp(FILE *fptr_image) //Function Definitions
{
    uint width, height; //declare the variables
    fseek(fptr_image, 18, SEEK_SET);//// Seek to 18th byte
 
    fread(&width, sizeof(int), 1, fptr_image); // Read the width (an int)
    //printf("width = %u\n", width);

    fread(&height, sizeof(int), 1, fptr_image); // Read the height (an int)
    //printf("height = %u\n", height);

    return width * height * 3; //this is bytes of data and Return image capacity
}

uint get_file_size(FILE *fptr) //Function Definitions
{
    fseek(fptr, 0, SEEK_END);  //Use the fseek to move the file pointer to end.
    uint size = ftell(fptr);  //Use the ftell to find the pos of the file pointer & return the pos. 
    rewind(fptr); // Resets the file pointer to the beginning of the file
    return size; //return size
}

Status open_file(EncodeInfo *encInfo)  //Function Definitions
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r"); //open scr_image from readbinary mode.
    if (encInfo->fptr_src_image == NULL) //Do Error handling
    {
    	perror("fopen"); // Prints the system error message for the last failed fopen() call
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
    	return e_failure;
    }
    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r"); //open fptr_secret from readbinary mode.
    if (encInfo->fptr_secret == NULL) //Do Error handling
    {
    	perror("fopen");  //Prints the system error message for the last failed fopen() call
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname); // Prints an error message to stderr indicating failure to open the stego image file
    	return e_failure;
    }
    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w"); //open fptr_stego_image from writebinary mode
    if (encInfo->fptr_stego_image == NULL)  //Do Error handling
    {
    	perror("fopen");// Prints the system error message for the last failed fopen() call
    	return e_failure;
    }
    return e_success; // No failure return e_success
}

Status read_and_validate_encode_args(int argc,char *argv[], EncodeInfo *encInfo)  //Function Definitions
{
    if (argc < 4 || argc > 5) //Check the argc is less than 4 and greater than 5
    {
        return e_failure;  // Returning mess if its failure
    }
    if (strstr(argv[2], ".bmp")) // check the argv[2] is having ".bmp" or not
    {
        encInfo->src_image_fname = argv[2]; //Store the argv[2] to the encInfo ->src_image_fname
    }
    else
    {
        printf("FAIL: "".bmp"" file doesnot exits\n");
        return e_failure;// Returning mess if its failure
    } 

    char *extn = strchr(argv[3],'.'); //Check the argv[3] is having '.' or not
    if(extn == NULL) //check it null or not
    {
        return e_failure;
    }
    else
    { 
        encInfo -> secret_fname = argv[3];  //store secret.txt in secret_fname
        strncpy(encInfo->extn_secret_file, extn, MAX_FILE_SUFFIX - 1); //store .txt in extn_secret_file
        encInfo->extn_secret_file[MAX_FILE_SUFFIX - 1] = '\0'; //the after storing the .txt put null 
    }

    if (argc == 4) //if(argv[4] == NULL) // Check whether output file argument is provided
    {    
        printf("INFO: Output File not mentioned. Creating steged_img.bmp as default\n");
        encInfo->stego_image_fname = "steged_img.bmp";  // Assign default output file name if not provided
    }
    else   //if argv[4] Output file argument is present 
    { 
        if (strstr(argv[4], ".bmp") != NULL) //// Check whether output file has .bmp extension
        {
            encInfo->stego_image_fname = argv[4];//Store the argv[4] to the encInfo ->stego_image_fname
        }
        else
        {
            return e_failure;// Returning mess if its failure
        }
    }
    return e_success; // Return success after successful validation
}

Status check_capacity(EncodeInfo *encInfo)   //Function Definitions
{
    encInfo -> image_capacity = get_image_size_for_bmp(encInfo -> fptr_src_image); // Get total usable bytes in the source BMP image
    encInfo -> size_secret_file = get_file_size(encInfo -> fptr_secret);  // Get size of the secret file in bytes
    // 54 bytes BMP header + magic string + secret file extension size (int) + secret file extension + secret file size (int) + secret file data, and multiply everything by 8 to get bits, then convert to bits
    uint required_size =((54 + strlen(MAGIC_STRING) + sizeof(int) + strlen(encInfo->extn_secret_file) + sizeof(int) + encInfo->size_secret_file) * 8);                        
    if (encInfo->image_capacity < required_size)  // Check if image capacity is insufficient
    {
        return e_failure;
    }
    return e_success;
}

Status copy_bmp_header(FILE * fptr_src_image, FILE *fptr_dest_image)  //Function Definitions 
{
    char buffer[54];// Buffer to store 54-byte BMP header
    rewind(fptr_src_image); // Move source image file pointer to the beginning
    if (fread(buffer, 54, 1, fptr_src_image) != 1 ||  // Read BMP header from source image
        fwrite(buffer, 54, 1, fptr_dest_image) != 1)  // Write BMP header to destination ima
    {
        return e_failure;
    }
    return e_success;  // Return success after copying BMP header
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)  //Function Definitions
{
    // Encodes the magic string into the image and checks for encoding failure
    if(encode_data_to_image(magic_string, strlen(magic_string), encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_failure)
    {
        return e_failure;
    }
    return e_success;
}

Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)  //Function Definitions
{
    char image_buffer[8]; //declare char array
    for(int i = 0;i < size;i++) //loops runs size times
    {
        if (fread(image_buffer, 8, 1, fptr_src_image) != 1)  //reading 8 bytes from src image & store the data  into buffer.
        {
            return e_failure;
        }
        if(encode_byte_to_lsb(data[i],image_buffer) == e_failure)  //calling encode_byte_to_lsb
        {
            return e_failure;
        }    
        fwrite(image_buffer, 8, 1, fptr_stego_image);   //writing 8 bytes to fptr_stego_image dest image
    }
    return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer)   //Function Definitions
{
   int bit_get; //declare the variable 
   for (int i = 0; i < 8; i++) //loops runs 8 times why 1 byte it is char
    { 
        bit_get = (data >> (7 - i)) & 1;  //get the bit from data(msb - lsb)
        image_buffer[i] = (image_buffer[i] & (~1)) | bit_get;  //clear LSB of image_buffer[i] at a time set buffer[i] bit into LSB
        // image_buffer[i] &= (~1);      //clear LSB of image_buffer[i]
        // image_buffer[i] |= bit_get;   //set buffer[i] bit into LSB
    }
    return e_success;
}

Status encode_size_to_lsb(int data, char *image_buffer)  //Function Definitions
{
   int bit_get; //declare variable
   for (int i = 0; i < 32; i++) //loops runs 32 times why 32 means it is int
    {
        bit_get = (data >> (31 - i)) & 1;   //get the msb bit from data
        image_buffer[i] = (image_buffer[i] & (~1)) | bit_get; //clear LSB of image_buffer[i] at a time set buffer[i] bit into LSB
    //     image_buffer[i] &= (~1);       //clear LSB of image_buffer[i]
    //     image_buffer[i] |= bit_get;   //set buffer[i] bit into LSB
    }
    return e_success; //return success 
}

Status encode_secret_file_extn_size(long extn_file_size , EncodeInfo *encInfo)  //Function Definitions
{
    char image_buffer[32]; //declare char array 
    fread(image_buffer, 32, 1, encInfo->fptr_src_image);  // Read 32 bytes from source image
    encode_size_to_lsb(extn_file_size, image_buffer);   // Encode extension size (32 bits)
    fwrite(image_buffer, 32, 1, encInfo->fptr_stego_image);  // Write 32 bytes to stego image
    return e_success; //return success msg 
}

Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo)  //Function Definitions
{
    return encode_data_to_image(file_extn,strlen(file_extn), encInfo->fptr_src_image,encInfo->fptr_stego_image); // Encodes the secret file extension into the image using LSB steganography
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)  //Function Definitions
{
    char image_buffer[32]; //declare char array
    fread(image_buffer , 32, 1, encInfo -> fptr_src_image);  //read 32 bytes from fptr_src_image & store the data  into buffer.
    encode_size_to_lsb(file_size, image_buffer);  //function call
    fwrite(image_buffer , 32 ,1 ,encInfo -> fptr_stego_image);  //write 32 bytes into the fptr_stego_image
    return e_success; //return msg

}

Status encode_secret_file_data(EncodeInfo *encInfo)  //Function Definitions
{
    char ch;
    rewind(encInfo->fptr_secret);  //move the file pointer start then read the data
    while(fread(&ch ,1, 1, encInfo->fptr_secret) == 1) //read a encInfo -> size_secret_file bytes from encInfo -> fptr_secret & store the data into buffer
        if(encode_data_to_image(&ch ,1 ,encInfo->fptr_src_image,encInfo->fptr_stego_image) == e_failure) //function call and condition checking & store the data into image
        {
            return e_failure;      //encoding secret file data
        }
    return e_success;

    // //another method
    // char sec_buffer[encInfo->size_secret_file]; //declare char array
    // rewind(encInfo->fptr_secret);  //move the file pointer starting position then read the data
    // fread(sec_buffer,encInfo->size_secret_file,1,encInfo->fptr_secret); //read a encInfo -> size_secret_file bytes from encInfo -> fptr_secret & store the data into buffer
    // if(encode_data_to_image(sec_buffer,encInfo->size_secret_file,encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure)  //function call from encode_data_to_image
    // {
    //     return e_failure;               //encoding secret file data
    // }
    // return e_success;
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)  //Function Definitions
{
    char buffer;
    //loop runs (EOF)
    while(fread(&buffer, 1, 1, fptr_src) > 0) //Read 1 byte from fptr_scr & store to buffer.
    {
        fwrite(&buffer, 1, 1, fptr_dest);      //write 1 byte of buffer info fptr_dest.
    }
    return e_success; 
}

Status do_encoding(EncodeInfo *encInfo)//Function Definitions it's only func call and print the msg
{
    //printf("INFO: ENCODING PROCEDURE STARTED\n");
    // 1. Open files
    printf("INFO: Opening required files\n");
    if(open_file(encInfo) != e_success) //encInfo have the address
    {
        printf("FAIL: Unable to open files\n");  //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE files open successfully\n");//print the success msg

    // 2. Check capacity
    printf("## ENCODING PROCEDURE STARTED ##\n");
    printf("INFO : Checking for beautiful.bmp capacity of file\n");
    if(check_capacity(encInfo) != e_success)    //calling check capacity function
    {
        printf("FAIL: Insufficient image capacity\n");  //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE . FOUND OK\n"); //print the success msg
    
    // 3. Copy BMP header
    encInfo -> secret_file_extn_size = strlen(encInfo -> extn_secret_file);
    printf("INFO: Copying Image BMP header\n");
    if(copy_bmp_header(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) != e_success)   //calling copy_bmp_header function
    {
        printf("FAIL: Failed to copy 54 bytes BMP Header\n");  //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE\n");//print the success msg
    
    // 4. Encode magic string
    printf("INFO: Encoding magic string\n");
    if(encode_magic_string(MAGIC_STRING,encInfo) != e_success)   //calling encode_magic string function
    {
        printf("FAIL: Magic string encoding failed\n");  //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE\n");//print the success msg

    // 5. Encode secret file extension size
    printf("INFO: Encoding Secret File Extension size\n");
    if(encode_secret_file_extn_size(strlen(encInfo -> extn_secret_file),encInfo) != e_success)
    {
        printf("FAIL: Extension size encoding failed\n");   //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE\n");//print the success msg

    // 6. Encode secret file extension
    printf("INFO: Encoding Secret File Extension\n");
    if(encode_secret_file_extn(encInfo -> extn_secret_file, encInfo) != e_success)   //calling encode_secret_file_extn function
    {
        printf("FAIL: Extension encoding failed\n");   //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE\n"); //print the success msg

    // 7. Encode secret file size
    printf("INFO: Encoding Secret File size\n");
    if(encode_secret_file_size(encInfo -> size_secret_file, encInfo) != e_success)   //calling encode_secret_file_size function
    {
        printf("FAIL: Secret file size encoding failed\n");   //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE\n");//print the success msg

    // 8. Encode secret file data
    printf("INFO: Encoding secret File Data\n");
    if(encode_secret_file_data(encInfo) != e_success)    //calling encode_secret_file_data function
    {
        printf("FAIL: Secret file data encoding failed\n");  //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE\n"); //print the success msg

    // 9. Copy remaining image data
    printf("INFO: Copying remaining image data\n");
    if(copy_remaining_img_data(encInfo -> fptr_src_image, encInfo->fptr_stego_image) != e_success)  //calling copy_remaining_img_data function
    {
        printf("FAIL: Remaining image data copy failed\n");  //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE\n");

    fclose(encInfo->fptr_secret); //close the file end of the program
    fclose(encInfo->fptr_src_image); //close the file end of the program
    fclose(encInfo->fptr_stego_image);//close the file end of the program
    //success return e_success 
    return e_success;
}