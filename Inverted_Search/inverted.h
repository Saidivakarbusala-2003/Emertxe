#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

#define SUCCESS		1 // Define a constant for success status
#define FAILURE		0 // Define a constant for failure status

extern int db_created; // Flag to indicate if the database has been created
extern int db_updated; // Flag to indicate if the database has been updated

typedef struct file // Structure for file nodes in the linked list
{
    char f_name[20];
    struct file *link;
}F_node;

typedef struct Sub // Structure for sub nodes in the main node's linked list
{
    int word_count;
    char filename[20];
    struct Sub *sub_link;
}S_node;

typedef struct Main // Structure for main nodes in the hash table
{
    char word[25];
    int file_count;
    S_node *sub_link;
    struct Main *main_link;
}M_node;

// Function prototypes
void create_database(M_node *HT[], F_node *head);
void display_database(M_node *HT[]);
void search_database(M_node *HT[]);
void save_database(M_node *HT[]);
int update_database(M_node *HT[],F_node **head);

void validate_files(char *argv[], F_node **head);
int insert_last(F_node **head, char *f_name);
int delete_node(F_node** head,char* file_name);
int check_duplicates(F_node *head, char *f_name);
int print_filenames(F_node *head);
int get_index(char *word);
int create_node(M_node *HT[],int index,char *word,char *file_name);

#endif
