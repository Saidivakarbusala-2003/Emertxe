#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "common.h"
#include "types.h"

Status read_and_validate_decode_args(int argc, char *argv[], DecodeInfo *decInfo) //Function Definitions
{
    if (argc < 3 || argc > 4) //argument count less the 3 or grater then 4 
    {
        return e_failure; // Returning mess if its failure
    }

    if (strstr(argv[2], ".bmp") != NULL) // Check if stego image file is a .bmp
    {
        decInfo->stego_image_fname = argv[2]; // Store stego image filename
    }
    else
    {
        printf("ERROR: Stego image must be .bmp file\n");
        return e_failure;  // Returning mess if its failure
    }

    if (argc == 4) //// Check if output secret file name is provided
    {
        decInfo->secret_fname = argv[3]; // Use provided name
        printf("INFO: Output File name Provided\n");
    }
    else
    {
        decInfo->secret_fname = "divakar.txt";// User not provied default name 
        printf("INFO: Output File name not provided, using default file\n");
    }

    return e_success;
}

Status open_files(DecodeInfo *decInfo) //Function Definitions
{
    decInfo -> fptr_stego_image  = fopen(decInfo -> stego_image_fname, "r"); //open the file int read mode
    if ((decInfo -> fptr_stego_image) == NULL) //checking null or not
    {
        perror("fopen"); //if file doesnt open then i am throwing an error
        return e_failure;
    }
    decInfo->fptr_secret = fopen(decInfo->secret_fname, "w"); //open the file in write mode
    if (decInfo->fptr_secret == NULL) //checking null or not
    {
        perror("fopen"); // Prints the system error message for the last failed fopen() call
        return e_failure;
    }
    return e_success; // Files opened successfully
}

Status skip_bmp_header(FILE * fptr_stego_image) //Function Definitions
{
    fseek(fptr_stego_image, 54, SEEK_SET); //skip the header 54 bytes
    return e_success;
}

Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo) //Function Definitions
{
    int len = strlen(magic_string); //calculate magic_string length using inbuilt function
    char my_magic_string[len + 1]; //declare char array with size 
    decode_image_into_data(my_magic_string, len,  decInfo -> fptr_stego_image); //stroe the image data into user buffer
    my_magic_string[len] = '\0'; // Null terminate string
    if(strcmp(my_magic_string , magic_string) != 0) //check magic_string and my_string are equal or not
    {
        printf("ERROR : Magic string not matched\n");
        return e_failure;
    }
    return e_success;
}

Status decode_secret_file_extn_size(DecodeInfo *decInfo) //Function Definitions
{
    char decode_buffer[32]; //declare char array
    fread(decode_buffer, 32, 1, decInfo->fptr_stego_image); // Read 32 bytes from image
    decode_lsb_into_size(&decInfo -> extn_size, decode_buffer); // Convert LSBs to integer
    return e_success;
}

Status decode_secret_file_extn(DecodeInfo *decInfo) //Function Definitions
{
    return decode_image_into_data(decInfo-> secret_file_extn, decInfo->extn_size,decInfo->fptr_stego_image);   // Calls the function to decode the secret file extension from the image
}

Status decode_secret_file_size(DecodeInfo *decInfo) //Function Definitions
{
    char image_buffer[32]; //declare the char array
    fread(image_buffer, 32, 1, decInfo->fptr_stego_image); // Read 32 bytes
    decode_lsb_into_size(&decInfo -> size_secret_file, image_buffer); // Store as integer
    return e_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo) //Function Definitions
{
    char ch;
    for(int i = 0;i < decInfo -> size_secret_file ; i++) //loop runs upto size_secret_file times
    {
        if(decode_image_into_data(&ch ,1 ,decInfo->fptr_stego_image) == e_failure) // Decode 1 byte from image into 'ch'
        {
            return e_failure;      //encoding secret file data
        }
        fwrite(&ch ,1, 1, decInfo->fptr_secret); // Write decoded byte to secret file
    }
    return e_success;
}

Status decode_image_into_data(char *data, int size, FILE *fptr_stego_image) //Function Definitions
{
    char image_buffer[8]; //declare char array
    for (int i = 0; i < size; i++) //loops runs from size times
    {
        fread(image_buffer, 8, 1, fptr_stego_image);// Read 8 bytes (1 byte encoded)
        decode_lsb_into_byte(&data[i], image_buffer);// Convert LSBs to byte
    }
    return e_success;
}

Status decode_lsb_into_byte(char *data, char *image_buffer) //Function Definitions
{
    *data = 0; // Initialize the decoded byte to 0
    for (int i = 0; i < 8; i++) //loop runs 8 times it's char
    {
        // Shift current data left by 1 bit and OR with LSB of current image byte 
        // image_buffer[i] & 1 extracts the least significant bit
        *data = (*data << 1) | (image_buffer[i] & 1);
    }
    // After loop, *data contains 8 bits combined from the LSBs of image_buffer
    return e_success;// Return status to indicate successful decoding
}

Status decode_lsb_into_size(int *data, char *image_buffer) //Function Definitions
{
    *data = 0;// Initialize the integer to 0
    for (int i = 0; i < 32; i++) //loop runs 32 times it is int
    {
        // Shift current data left by 1 bit and OR with LSB of current image byte
        // image_buffer[i] & 1 extracts the least significant bit
        *data = (*data << 1) | (image_buffer[i] & 1);
    }
    // After loop, *data contains 32 bits combined from the LSBs of image_buffer &// which represents the original integer (size or extension length)
    return e_success; // Return status to indicate successful decoding
}

Status do_decoding(DecodeInfo *decInfo) //Function Definitions and only functions calls and print the success and failure messages
{
    printf("## DECODING PROCEDURE STARTED ##\n"); //decoding process starts 
    printf("INFO: Opening required files\n");
    if (open_files(decInfo) == e_failure)  //calling open_files function
    {
        printf("ERROR: Unable to open files\n"); //print the failure msg
        return e_failure;
    }
    printf("INFO: DONE opened files\n"); //print the success msg

    /* Skip BMP header (54 bytes) */
    printf("INFO: Skipping BMP header\n");
    if (skip_bmp_header(decInfo->fptr_stego_image) == e_failure) //calling skip_bmp_header function
    {
        printf("ERROR: Failed to skip BMP header\n");  //print the failure msg
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }
    printf("INFO: DONE\n"); //print the success msg

    /* 1. Decode & validate magic string */
    printf("INFO: Decoding magic string\n");
    if (decode_magic_string(MAGIC_STRING, decInfo) != e_success) //calling magic_string function
    {
        printf("ERROR: Magic string mismatch\n");  //print the failure msg
        fclose(decInfo->fptr_stego_image); //close the file
        return e_failure; //return e_failure;
    }
    printf("INFO: DONE (matched)\n"); //print the success msg

    /* 2. Decode secret file extension size */
    printf("INFO: Decoding secret file extension size\n");
    if (decode_secret_file_extn_size(decInfo) != e_success) //calling secret_file_extn_size function
    {
        printf("ERROR: Failed to decode extension size\n");  //print the failure msg
       return e_failure;//return e_failure;
    }
    printf("INFO: DONE\n"); //print the success msg

    /* 3. Decode secret file extension */
    printf("INFO: Decoding secret file extension\n");
    if (decode_secret_file_extn(decInfo) != e_success) //calling secret_file_extn function
    {
        printf("ERROR: Failed to decode extension\n");  //print the failure msg
        return e_failure;//return e_failure;
    }
    printf("INFO: DONE\n"); //print the success msg

    /* 4. Decode secret file size */
    printf("INFO: Decoding secret file size\n");
    if (decode_secret_file_size(decInfo) != e_success) //calling secret_file_size function
    {
        printf("ERROR: Failed to decode secret file size\n");  //print the failure msg
        return e_failure;//return e_failure;
    }
    printf("INFO: DONE\n"); //print the success msg

    /* 5. Decode secret file data */
    printf("INFO: Decoding secret file data\n");
    if (decode_secret_file_data(decInfo) != e_success) //calling secret_file_data function
    {
        printf("ERROR: Failed to decode secret file data\n");  //print the failure msg
        return e_failure;//return e_failure;
    }
    printf("INFO: DONE\n"); //print the success msg

    fclose(decInfo->fptr_secret); //close the file end of the program
    fclose(decInfo->fptr_stego_image);//close the file end of the program

    return e_success;
}
