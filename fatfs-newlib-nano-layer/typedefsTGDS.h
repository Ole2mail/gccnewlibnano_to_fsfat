/*
 * typedefsTGDS.h
 *
 *  Created on: Jul 3, 2018
 *      Author: oleg.kokorin
 */

#ifndef TYPEDEFSTGDS_H_
#define TYPEDEFSTGDS_H_

#include <stdbool.h>
#include <stdint.h>
#include "devopttab.h"
#include "ffconf.h"

#define OPEN_MAXFILEDES 16 /*1024*/
#define NAME_MAX FF_MAX_LFN

typedef char sint8;
typedef unsigned char uint8;
typedef int32_t sint32;
typedef uint32_t uint32;

struct dirent {
    ino_t          d_ino;       /* inode number */
    off_t          d_off;       /* offset to the next dirent */
    unsigned short d_reclen;    /* length of this record */
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types */
    char           d_name[256]; /* filename */
};

#endif /* TYPEDEFSTGDS_H_ */
