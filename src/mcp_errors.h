#ifndef __STUB_MCP_ERRORS_H
#define __STUB_MCP_ERRORS_H

#define FSYS_ERR_DISK_ERR               -18 /* (1) A hard error occurred in the low level disk I/O layer */
#define FSYS_ERR_INT_ERR                -19 /* (2) Assertion failed */
#define FSYS_ERR_NOT_READY              -20 /* (3) The physical drive cannot work */
#define FSYS_ERR_NO_FILE                -21 /* (4) Could not find the file */
#define FSYS_ERR_NO_PATH                -22 /* (5) Could not find the path */
#define FSYS_ERR_INVALID_NAME           -23 /* (6) The path name format is invalid */
#define FSYS_ERR_DENIED                 -24 /* (7) Access denied due to prohibited access or directory full */
#define FSYS_ERR_EXIST                  -25 /* (8) Access denied due to prohibited access */
#define FSYS_ERR_INVALID_OBJECT         -26 /* (9) The file/directory object is invalid */
#define FSYS_ERR_WRITE_PROTECTED        -27 /* (10) The physical drive is write protected */
#define FSYS_ERR_INVALID_DRIVE          -28 /* (11) The logical drive number is invalid */
#define FSYS_ERR_NOT_ENABLED            -29 /* (12) The volume has no work area */
#define FSYS_ERR_NO_FILESYSTEM          -30 /* (13) There is no valid FAT volume */
#define FSYS_ERR_MKFS_ABORTED           -31 /* (14) The f_mkfs() aborted due to any problem */
#define FSYS_ERR_TIMEOUT                -32 /* (15) Could not get a grant to access the volume within defined period */
#define FSYS_ERR_LOCKED                 -33 /* (16) The operation is rejected according to the file sharing policy */
#define FSYS_ERR_NOT_ENOUGH_CORE        -34 /* (17) LFN working buffer could not be allocated */
#define FSYS_ERR_TOO_MANY_OPEN_FILES    -35 /* (18) Number of open files > FF_FS_LOCK */
#define FSYS_ERR_INVALID_PARAMETER      -36 /* (19) Given parameter is invalid */

extern int map_errno(int result);

#endif
