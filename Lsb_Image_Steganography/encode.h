#ifndef ENCODE_H
#define ENCODE_H
#include<stdio.h>
#include "common.h"
#include "types.h" // Contains user defined types

/* Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */
typedef struct _EncodeInfo
{
    /* Source Image info */
    char *src_image_fname; // Pointer to the source image file name
    FILE *fptr_src_image; // File pointer to the source image file
    uint image_capacity; // Maximum data (in bytes) that can be hidden in the image
    uint bits_per_pixel; // Number of bits per pixel in the image (e.g., 24 for BMP)
    char image_data[MAX_IMAGE_BUF_SIZE]; // Buffer to store image pixel data

    /* Secret File Info */
    char *secret_fname; // Pointer to the secret file name
    FILE *fptr_secret; // File pointer to the secret file
    char extn_secret_file[MAX_FILE_SUFFIX]; // Buffer to store the secret file extension (e.g., ".txt")
    char secret_data[MAX_SECRET_BUF_SIZE]; // Buffer to store secret file data
    int secret_file_extn_size; // Size of the secret file extension
    long size_secret_file; // Size of the secret file in bytes

    /* Stego Image Info */
    char *stego_image_fname; // Pointer to the stego image file name (output image)
    FILE *fptr_stego_image; // File pointer to the stego image file
    
} EncodeInfo;

/* Encoding function prototype */

/* Check operation type */
OperationType check_operation_type(char *argv[]);

/* Read and validate Encode args from argv */
Status read_and_validate_encode_args(int argc,char *argv[], EncodeInfo *encInfo);

/* Perform the encoding */
Status do_encoding(EncodeInfo *encInfo);

/* Get File pointers for i/p and o/p files */
Status open_file(EncodeInfo *encInfo);

/* check capacity */
Status check_capacity(EncodeInfo *encInfo);

/* Get image size */
uint get_image_size_for_bmp(FILE *fptr_image);

/* Get file size */
uint get_file_size(FILE *fptr);

/* Copy bmp image header */
Status copy_bmp_header(FILE * fptr_src_image, FILE *fptr_dest_image);

/* Store Magic String */
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo);

/* Encode secret file extenstion size*/
Status encode_secret_file_extn_size(long extn_file_size, EncodeInfo *encInfo);

/* Encode secret file extenstion */
Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo);

/* Encode secret file size */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo);

/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo);

/* Encode function, which does the real encoding */
Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);

/* Encode a byte into LSB of image data array */
Status encode_byte_to_lsb(char data, char *image_buffer);

/* Encode a byte into LSB of image data array */
Status encode_size_to_lsb(int data, char *image_buffer);

/* Copy remaining image bytes from src to stego image after encoding */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest);

#endif
