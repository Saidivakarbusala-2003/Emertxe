#ifndef DECODE_H
#define DECODE_H
#include <stdio.h>
#include "common.h"
#include "types.h" // Contains user defined types

/* Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */
typedef struct _DecodeInfo
{
    /* Secret File Info */
    char *secret_fname; // Pointer to the name of the secret file to be decoded
    FILE *fptr_secret; // File pointer to the output secret file
    char secret_file_extn[MAX_FILE_SUFFIX]; // Buffer to store the secret file extension (e.g., ".txt", ".c")
    char secret_data[MAX_SECRET_BUF_SIZE]; // Buffer to temporarily store decoded secret data
    int size_secret_file; // Size of the secret file in bytes
    int extn_size; // Size of the secret file extension

    /* Stego Image Info */
    char *stego_image_fname; // Pointer to the stego image file name (image containing hidden data)
    FILE *fptr_stego_image;  // File pointer to the stego image file

} DecodeInfo;

/* Decoding function prototype */

/* Read and validate Encode args from argv */
Status read_and_validate_decode_args(int argc,char *argv[], DecodeInfo *decInfo);

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_files(DecodeInfo *decInfo);

/* Copy bmp image header */
Status skip_bmp_header(FILE * fptr_stego_image);

/* Read Magic String */
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo);

/* decode secret file extenstion size*/
Status decode_secret_file_extn_size(DecodeInfo *decInfo);

/* decode secret file extenstion */
Status decode_secret_file_extn(DecodeInfo *decInfo);

/* decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* decode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo);

/* decode function, which does the real decoding */
Status decode_image_into_data(char *data, int size, FILE *fptr_stego_image);

/* decode a bit into arr of LSB of image char msb */
Status decode_lsb_into_byte(char *data, char *image_buffer); 

/* decode a bit into arr of LSB of image int msb */
Status decode_lsb_into_size(int *data, char *image_buffer); 

#endif
