//./a.out -e beautiful.bmp secret.txt  //encoding inputs
//./a.out -d steged_img.bmp //decoding inputs
//./a.out -d steged_img.bmp secret_msg.txt user provied out.txt name
/*
Name        : Busala Sai Divakar.

Date        : 15-01-2025.

Project     : LSB (Least Significant Bit) Image Steganography.

Description : LSB (Least Significant Bit) Image Steganography is a simple technique used to hide secret data inside an image. 
              It works by replacing the least significant bit of each pixel’s color value with bits of the secret message. 
              Since changes in the LSB cause very little visual difference, the image looks almost unchanged to the human eye. 
              This method is easy to implement and commonly used for basic image-based data hiding.
*/

#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "common.h"
#include "encode.h"
#include "types.h"
OperationType check_operation_type(char *argv[]) //function defination
{
    // Check for encode operation
    if(strcmp(argv[1], "-e") == 0)  //check the argv[1] is "-e" or not
    {
        return e_encode; 
    }
    // Check for decode operation
    else if(strcmp(argv[1], "-d") == 0)  //check the argv[1] is "-d" or not
    {
        return e_decode; 
    }
    // Unsupported operation
    else
    {
        return e_unsupported;
    }

}

int main(int argc,char *argv[])//*argv[] means array of pointer
{
    EncodeInfo encInfo; // Structure variable to store all information needed for encoding (hiding secret data inside an image)
    DecodeInfo decInfo; // Structure variable to store all information needed for decoding (retrieving secret data from a stego image)
    if (argc < 2)// Check for minimum arguments
    {
        printf("ERROR: Invalid arguments\n");
        printf("Encoding: ./a.out -e <bmp_file> <.txt file> [output file]\n");//display mess
        printf("Decoding: ./a.out -d <.bmp_file> [output file]\n");//display mess
        return e_failure;
    }
    // Check for incomplete encode arguments
    if (argc == 3 && (strcmp(argv[1], "-e") == 0))
    {
        printf("Encoding: ./a.out -e <bmp_file> <.txt file> [output file]\n");//display mess
        return e_failure;
    }
    // Identify operation type
    int res = check_operation_type(argv);//function call

    // Handle encode operation
    if(res == e_encode)
    {
        printf("INFO: Encode operation selected\n");
        if(read_and_validate_encode_args(argc,argv,&encInfo) == e_success) //fun call and condition checking
        {
            //Print the success mes
            printf("INFO: Encoding Argument validation successful\n");
            if(do_encoding(&encInfo) == e_failure) //fun call and condition checking
            {
                printf("ERROR : encoding not yet complted\n");
			    return e_failure;
            }
            printf("INFO: ## ENCODING SUCCESSFULLY COMPLETED ##\n");
        }
        else
        {
            //print the failure mes
            printf("ERROR: Encoding Argument validation failed\n");
            return e_failure;
        }
    }
    // Handle decode operation
    else if (res == e_decode)
    {
        printf("INFO: Decode operation selected\n");
        // decode logic will go here 
        if(read_and_validate_decode_args(argc,argv,&decInfo) == e_success) //fun call and condition checking
        {
            //Print the success mes
            printf("INFO: Decoding Argument validation successful\n");
            if(do_decoding(&decInfo)) //fun call and condition checking
            {
                printf("ERROR : Decoding not yet complted\n");
			    return e_failure;
            }
            printf("INFO: ## DECODING SUCCESSFULLY COMPLETED ##\n");
        }
        else
        {
            //print the failure mes
            printf("ERROR: Decoding Argument validation failed\n");
            return e_failure;
        }
    }  
    // Handle unsupported operation
    else
    {
        printf("ERROR: Unsupported operation\n");
        return e_failure;
    }
    return 0;
}
