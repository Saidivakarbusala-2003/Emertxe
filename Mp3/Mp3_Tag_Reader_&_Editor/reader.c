#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reader.h"
#include "header.h"
#define RED     "\033[1;31m" //define for red color
#define YELLOW  "\033[1;33m" //define for yellow color
#define RESET   "\033[0m" //define for reset color

TagData* read_id3_tags(const char *filename)  //fuction defineation
{ 
    FILE *file = fopen(filename, "rb"); //open the mp3 file in binary read mode
    if (!file) 
    {
        perror("Could not open file"); //print error message if file opening fails and return NULL
        return NULL;
    }

    TagData *tag = create_tag_data();//create a new TagData structure to store the metadata
    if (!tag)
    {
        fclose(file);
        return NULL;
    }

    fseek(file, 10, SEEK_SET); // seek to the position of header size (10 bytes from the start of file)

    unsigned char tag_buffer[5];//buffer to read frame id
    for (int i = 0; i < 6; i++)//loop to read each frame until we reach the end of header (6 frames in total)
    {
        if (fread(tag_buffer, 1, 4, file) != 4) //read frame id from file, if it fails to read 4 bytes, break the loop 
            break;
        tag_buffer[4] = '\0'; //null terminate the frame id

        unsigned char size_buf[4];//buffer to read frame size
        fread(size_buf, 1, 4, file);//read frame size from file

        unsigned int size =(size_buf[0] << 24) | (size_buf[1] << 16) | (size_buf[2] << 8)  | size_buf[3];//calculate frame size from bytes

        fseek(file, 2, SEEK_CUR); // skip frame flags (2 bytes)

        unsigned char *new_data = malloc(size + 1);//buffer to read frame data, allocate memory for frame data plus null terminator
        if (!new_data)//check if memory allocation failed
            break;

        fread(new_data, 1, size, file);//read frame data from file
        new_data[size] = '\0';//null terminate the frame data

        char *text = (char *)(new_data + 1); //text starts from the second byte, first byte is encoding or null information

        if (strcmp(tag_buffer, "TIT2") == 0)       //check if frame id is "TIT2" (title) 
            tag->title = strdup(text);       //if it is, duplicate the text and store it in the title field of TagData structure

        else if (strcmp(tag_buffer, "TPE1") == 0)  //check if frame id is "TPE1" (artist)
            tag->artist = strdup(text);      //if it is, duplicate the text and store it in the artist field of TagData structure

        else if (strcmp(tag_buffer, "TALB") == 0)  //check if frame id is "TALB" (album)
            tag->album = strdup(text);       //if it is, duplicate the text and store it in the album field of TagData structure

        else if (strcmp(tag_buffer, "TYER") == 0 || //check if frame id is "TYER" (year) or "TDRC" (recording time, used in ID3v2.4 as a replacement for TYER)
                 strcmp(tag_buffer, "TDRC") == 0)
            tag->year = strdup((char *)text); //if it is, duplicate the text and store it in the year field of TagData structure

        else if (strcmp(tag_buffer, "TCON") == 0)   //check if frame id is "TCON" (genre)
            tag->genre = strdup(text);        //if it is, duplicate the text and store it in the genre field of TagData structure

        else if (strcmp(tag_buffer, "COMM") == 0)   //check if frame id is "COMM" (comment)
            tag->comment = strdup(text);      //if it is, duplicate the text and store it in the comment field of TagData structure

        free(new_data); //free the buffer after use
    }
    fclose(file); //close the file after reading is done
    return tag; //return the populated TagData structure with the metadata read from the file
}

void display_metadata(const TagData *data) //function defineation to display the metadata
{
    printf("---------------------------------------------------------\n");
    printf("\t🎵 "YELLOW"MP3 TAG READRE AND EDITOR FOR ID3V2"RESET" 🎶\n");
    printf("---------------------------------------------------------\n");
    printf("\n------------------ "RED"ID3 TAG METADATA"RESET"----------------------\n");

    printf("TITLE   : %s\n", data->title  ? data->title  : "Not available");   //display title, if title is not available, display "Not available"
    printf("ARTIST  : %s\n", data->artist ? data->artist : "Not available");   //display artist, if artist is not available, display "Not available"
    printf("ALBUM   : %s\n", data->album  ? data->album  : "Not available");   //display album, if album is not available, display "Not available"
    printf("YEAR    : %s\n", data->year   ? data->year   : "Not available");   //display year, if year is not available, display "Not available"
    printf("MUSIC   : %s\n", data->genre  ? data->genre  : "Not available");   //display genre, if genre is not available, display "Not available"  
    printf("Comment : %s\n", data->comment? data->comment: "Not available");   //display comment, if comment is not available, display "Not available"

    printf("----------------------------------------------------------\n");
}

void view_tags(const char *filename) //function defineation 
{
    TagData *data = read_id3_tags(filename); //call the read_id3_tags function
    if (!data)
    {
        perror("Failed to read ID3 tags"); //if reading tags fails, print an error message and return
        return;
    }
    display_metadata(data); //call the display_metadata function
    free_tag_data(data); //call the free_tag_data function to free the memory allocated
}
