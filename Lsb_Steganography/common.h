#ifndef COMMON_H //if not define defiend it
#define COMMON_H

/* Magic string to identify whether stegged or not */
#define MAGIC_STRING "#*"

#define MAX_SECRET_BUF_SIZE 1    // Maximum number of bytes read from the secret file at a time
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)   // Image buffer size needed to encode one secret byte (8 bits)
#define MAX_FILE_SUFFIX 4     // Maximum length of the secret file extension (including dot)

#endif
