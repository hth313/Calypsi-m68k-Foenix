/*
 * Declarations for calling into the Foenix/MCP kernel
 *
 * Code calling into the MCP should include this or a similar set of bindings
 * The kernel will use this to allow for system calls to be replaced if needed
 * by other code.
 *
 */

#ifndef __MCP_SYSCALLS_H
#define __MCP_SYSCALLS_H

#include "types.h"
#include "errors.h"
#include "interrupt.h"

/*
 * Syscall function numbers
 */

/* Core calls */

#define KFN_EXIT                0x00    /* Quick the current program and return to the command line */
#define KFN_WARMBOOT            0x01    /* Do a soft re-initialization */
#define KFN_INT_REGISTER        0x02    /* Set a handler for an exception / interrupt */
#define KFN_INT_ENABLE          0x03    /* Enable an interrupt */
#define KFN_INT_DISABLE         0x04    /* Disable an interrupt */
#define KFN_INT_ENABLE_ALL      0x05    /* Enable all interrupts */
#define KFN_INT_DISABLE_ALL     0x06    /* Disable all interrupts */
#define KFN_INT_CLEAR           0x07    /* Clear (acknowledge) an interrupt */
#define KFN_INT_PENDING         0x08    /* Return true if the interrupt is pending */
#define KFN_SYS_GET_INFO        0x09    /* Get information about the computer */

/* Channel system calls */

#define KFN_CHAN_READ           0x10    /* Read bytes from an input channel */
#define KFN_CHAN_READ_B         0x11    /* Read a byte from an input channel */
#define KFN_CHAN_READ_LINE      0x12    /* Read a line from an input channel */
#define KFN_CHAN_WRITE          0x13    /* Write bytes to an output channel */
#define KFN_CHAN_WRITE_B        0x14    /* Write a byte to an output channel */
#define KFN_CHAN_FLUSH          0x15    /* Ensure that any pending write on a channel is committed */
#define KFN_CHAN_SEEK           0x16    /* Set the input/output cursor on a channel to a given position */
#define KFN_CHAN_STATUS         0x17    /* Get the status of a channel */
#define KFN_CHAN_IOCTRL         0x18    /* Send a command to a channel (channel dependent functionality) */
#define KFN_CHAN_REGISTER       0x19    /* Register a channel device driver */
#define KFN_CHAN_OPEN           0x1A    /* Open a channel device */
#define KFN_CHAN_CLOSE          0x1B    /* Close an open channel (not for files) */
#define KFN_CHAN_SWAP           0x1C    /* Swap two channels */
#define KFN_CHAN_DEVICE         0x1D    /* Return the Device ID of a channel */
#define KFN_TEXT_SETSIZES       0x1C    /* Adjusts the screen size based on the current graphics mode */


/* Block device system calls */

#define KFN_BDEV_GETBLOCK       0x20    /* Read a block from a block device */
#define KFN_BDEV_PUTBLOCK       0x21    /* Write a block to a block device */
#define KFN_BDEV_FLUSH          0x22    /* Ensure that any pending write on a block device is committed */
#define KFN_BDEV_STATUS         0x23    /* Get the status of a block device */
#define KFN_BDEV_IOCTRL         0x24    /* Send a command to a block device (device dependent functionality) */
#define KFN_BDEV_REGISTER       0x25    /* Register a block device driver */

/* File/Directory system calls */

#define KFN_OPEN                0x30    /* Open a file as a channel */
#define KFN_CLOSE               0x31    /* Close a file channel */
#define KFN_OPENDIR             0x32    /* Open a directory for reading */
#define KFN_CLOSEDIR            0x33    /* Close an open directory */
#define KFN_READDIR             0x34    /* Read the next directory entry in an open directory */
#define KFN_FINDFIRST           0x35    /* Find the first entry in a directory that matches a pattern */
#define KFN_FINDNEXT            0x36    /* Find the next entry in a directory that matches a pattern */
#define KFN_DELETE              0x37    /* Delete a file */
#define KFN_RENAME              0x38    /* Rename a file */
#define KFN_MKDIR               0x39    /* Create a directory */
#define KFN_LOAD                0x3A    /* Load a file into memory */
#define KFN_GET_LABEL           0x3B    /* Read the label of a volume */
#define KFN_SET_LABEL           0x3C    /* Set the label of a volume */
#define KFN_SET_CWD             0x3D    /* Set the current working directory */
#define KFN_GET_CWD             0x3E    /* Get the current working directory */
#define KFN_LOAD_REGISTER       0x3F    /* Register a file type handler for executable binaries */

/* System: Process and memory calls */

#define KFN_PROC_RUN            0x40    /* Load and execute a binary file */
#define KFN_MEM_GET_RAMTOP      0x41    /* Return limit of accessible RAM */
#define KFN_MEM_RESERVE         0x42    /* Reserve a block of memory from top of system RAM */
#define KFN_PROC_ELEVATE        0x43    /* Raise privilege of current program to highest level */
#define KFN_VAR_SET             0x44    /* Set value of a system variable */
#define KFN_VAR_GET             0x45    /* Return the value of a system variable */

/* System: Misc calls */

#define KFN_TIME_JIFFIES        0x50    /* Gets the current time code (increments since boot) */
#define KFN_TIME_SETRTC         0x51    /* Set the real time clock date-time */
#define KFN_TIME_GETRTC         0x52    /* Get the real time clock date-time */
#define KFN_KBD_SCANCODE        0x53    /* Get the next scan code from the keyboard */
#define KFN_KBD_LAYOUT          0x54    /* Set the translation tables for the keyboard */
#define KFN_ERR_MESSAGE         0x55    /* Return an error description, given an error number */

/* Text Display calls */
#define KFN_TXT_INIT_SCREEN     0x60    /* Reset a screen to its default text mode */
#define KFN_TXT_GET_CAPS        0x61    /* Return a description of a screen's capabilities */
#define KFN_TXT_SET_MODE        0x62    /* Set the display mode of a screen */
#define KFN_TXT_SETSIZES        0x63    /* Calculate the size of the text matrix */
#define KFN_TXT_SET_RESOLUTION  0x64    /* Set the base display resolution */
#define KFN_TXT_SET_BORDER      0x65    /* Set the border size */
#define KFN_TXT_SET_BORDER_COLOR    0x66    /* Set border color */
#define KFN_TXT_SET_FONT        0x67    /* Set text mode font for the display */
#define KFN_TXT_SET_CURSOR      0x68    /* Set cursor appearance for the display */
#define KFN_TXT_SET_REGION      0x69    /* Set clipping/scrolling region for display */
#define KFN_TXT_GET_REGION      0x6A    /* Get current clipping/scrolling region */
#define KFN_TXT_SET_COLOR       0x6B    /* Set foreground and background colors for text */
#define KFN_TXT_GET_COLOR       0x6C    /* Get current foreground and background colors */
#define KFN_TXT_SET_XY          0x6D    /* Set cursor position within current region */
#define KFN_TXT_GET_XY          0x6E    /* Get cursor position within current region */
#define KFN_TXT_SCROLL          0x6F    /* Scroll current region */
#define KFN_TXT_SET_CURSOR_VIS  0x71    /* Set cursor visibility */
#define KFN_TXT_GET_SIZES       0x72    /* Gets screensize in pixels and characters */


/*
 * Call into the kernel (provided by assembly)
 */
extern int32_t syscall(int32_t function, p_syscall_params params);

/***
 *** Core system calls
 ***/

/*
 * Quit the current user process
 *
 * NOTE: at the moment, this relaunches the CLI. In the future, this
 *       may cause execution to return to the program that started
 *       the user process.
 *
 * Inputs:
 * result = the code to return to the kernel
 */
extern void sys_exit(short result);

/*
 * Register a handler for a given interrupt.
 *
 * Inputs:
 * n = the number of the interrupt
 * handler = pointer to the interrupt handler to register
 *
 * Returns:
 * the pointer to the previous interrupt handler
 */
extern p_int_handler sys_int_register(unsigned short n, p_int_handler handler);

/*
 * Enable an interrupt
 *
 * Inputs:
 * n = the number of the interrupt
 */
extern void sys_int_enable(unsigned short n);

/*
 * Disable an interrupt by masking it
 *
 * Inputs:
 * n = the number of the interrupt: n[7..4] = group number, n[3..0] = individual number.
 */
extern void sys_int_disable(unsigned short n);

/*
 * Enable all interrupts
 *
 * NOTE: this is actually provided in the low level assembly
 */
extern void sys_int_enable_all();

/*
 * Disable all interrupts
 *
 * NOTE: this is actually provided in the low level assembly
 */
extern void sys_int_disable_all();

/*
 * Acknowledge an interrupt (clear out its pending flag)
 *
 * Inputs:
 * n = the number of the interrupt: n[7..4] = group number, n[3..0] = individual number.
 */
extern void sys_int_clear(unsigned short n);

/*
 * Return true (non-zero) if an interrupt is pending for the given interrupt
 *
 * Inputs:
 * n = the number of the interrupt: n[7..4] = group number, n[3..0] = individual number.
 *
 * Returns:
 * non-zero if interrupt n is pending, 0 if not
 */
extern short sys_int_pending(unsigned short n);

/*
 * Fill out a s_sys_info structure with the information about the current system
 *
 * Inputs:
 * info = pointer to a s_sys_info structure to fill out
 */
extern void sys_get_info(p_sys_info info);

/***
 *** Channel system calls
 ***/

/*
 * Read bytes from the channel
 *
 * Inputs:
 *  channel = the number of the channel
 *  buffer = the buffer into which to copy the channel data
 *  size = the size of the buffer.
 *
 * Returns:
 *  number of bytes read, any negative number is an error code
 */
extern short sys_chan_read(short channel, unsigned char * buffer, short size);

/*
 * Read a single byte from the channel
 *
 * Inputs:
 *  channel = the number of the channel
 *
 * Returns:
 *  the value read (if negative, error)
 */
extern short sys_chan_read_b(short channel);

/*
 * Read a line of text from the channel
 *
 * Inputs:
 *  channel = the number of the channel
 *  buffer = the buffer into which to copy the channel data
 *  size = the size of the buffer
 *
 * Returns:
 *  number of bytes read, any negative number is an error code
 */
extern short sys_chan_readline(short channel, unsigned char * buffer, short size);

/*
 * Write a byte to the channel
 *
 * Inputs:
 *  channel = the number of the channel
 *  b = the byte to write
 *
 * Returns:
 *  number of bytes written, any negative number is an error code
 */
extern short sys_chan_write(short channel, unsigned char * buffer, short size);

/*
 * Write a single byte to the device
 *
 * Inputs:
 *  channel = the number of the channel
 *  b = the byte to write
 *
 * Returns:
 *  0 on success, a negative value on error
 */
extern short sys_chan_write_b(short channel, unsigned char b);

/*
 * Ensure that any pending writes to teh device have been completed
 *
 * Inputs:
 *  channel = the number of the channel
 *
 * Returns:
 *  0 on success, any negative number is an error code
 */
extern short sys_chan_flush(short channel);

/*
 * Attempt to set the position of the channel cursor (if supported)
 *
 * Inputs:
 *  channel = the number of the channel
 *  position = the position of the cursor
 *  base = whether the position is absolute or relative to the current position
 *
 * Returns:
 *  0 = success, a negative number is an error.
 */
extern short sys_chan_seek(short channel, long position, short base);

/*
 * Return the status of the channel device
 *
 * Inputs:
 *  channel = the number of the channel
 *
 * Returns:
 *  the status of the device
 */
extern short sys_chan_status(short channel);

/*
 * Issue a control command to the device
 *
 * Inputs:
 *  channel = the number of the channel
 *  command = the number of the command to send
 *  buffer = pointer to bytes of additional data for the command
 *  size = the size of the buffer
 *
 * Returns:
 *  0 on success, any negative number is an error code
 */
extern short sys_chan_ioctrl(short channel, short command, uint8_t * buffer, short size);

/*
 * Register a channel device driver <>
 * 
 * Inputs:
 *  device = pointer to the device, including handler functions
 *
 * Returns:
 *  <>
 */
extern short sys_chan_register(struct s_dev_chan *device);

/*
 * Open a channel
 *
 * Inputs:
 * dev = the device number to have a channel opened
 * path = a "path" describing how the device is to be open
 * mode = is the device to be read, written, both? (0x01 = READ flag, 0x02 = WRITE flag, 0x03 = READ and WRITE)
 *
 * Returns:
 * the number of the channel opened, negative number on error
 */
extern short sys_chan_open(short dev, uint8_t * path, short mode);

/*
 * Close a channel
 *
 * Inputs:
 * chan = the number of the channel to close
 *
 * Returns:
 * nothing useful
 */
extern short sys_chan_close(short chan);

/* Swap two channels (given their IDS)
 *
 * Inputs:
 *  channel1, channel2 = channel IDs to be swapped
 *
 * Returns:
 *  0 on success, any other on error
 */
extern short sys_chan_swap(short channel1, short channel2);

/* Get the device ID of the device on  a channel
 *
 * Inputs:
 *  channel = channel of the device
 *
 * Returns:
 *  device ID of the device on the channel
 */
extern short sys_chan_device(short channel);

/***
 *** Block device system calls
 ***/

//
// Read a block from the device
//
// Inputs:
//  dev = the number of the device
//  lba = the logical block address of the block to read
//  buffer = the buffer into which to copy the block data
//  size = the size of the buffer.
//
// Returns:
//  number of bytes read, any negative number is an error code
//
extern short sys_bdev_getblock(short dev, long lba, unsigned char * buffer, short size);

//
// Write a block from the device
//
// Inputs:
//  dev = the number of the device
//  lba = the logical block address of the block to write
//  buffer = the buffer containing the data to write
//  size = the size of the buffer.
//
// Returns:
//  number of bytes written, any negative number is an error code
//
extern short sys_bdev_putblock(short dev, long lba, const unsigned char * buffer, short size);

//
// Ensure that any pending writes to teh device have been completed
//
// Inputs:
//  dev = the number of the device
//
// Returns:
//  0 on success, any negative number is an error code
//
extern short sys_bdev_flush(short dev);

//
// Return the status of the block device
//
// Inputs:
//  dev = the number of the device
//
// Returns:
//  the status of the device
//
extern short sys_bdev_status(short dev);

//
// Issue a control command to the device
//
// Inputs:
//  dev = the number of the device
//  command = the number of the command to send
//  buffer = pointer to bytes of additional data for the command
//  size = the size of the buffer
//
// Returns:
//  0 on success, any negative number is an error code
//
extern short sys_bdev_ioctrl(short dev, short command, unsigned char * buffer, short size);

//
// Register a block device driver
//
extern short sys_bdev_register(p_dev_block device);


/*
 * File System Calls
 */

/**
 * Attempt to open a file given the path to the file and the mode.
 *
 * Inputs:
 * path = the ASCIIZ string containing the path to the file.
 * mode = the mode (e.g. r/w/create)
 *
 * Returns:
 * the channel ID for the open file (negative if error)
 */
extern short sys_fsys_open(const char * path, short mode);

/**
 * Close access to a previously open file.
 *
 * Inputs:
 * fd = the channel ID for the file
 *
 * Returns:
 * 0 on success, negative number on failure
 */
extern short sys_fsys_close(short fd);

/**
 * Attempt to open a directory for scanning
 *
 * Inputs:
 * path = the path to the directory to open
 *
 * Returns:
 * the handle to the directory if >= 0. An error if < 0
 */
extern short sys_fsys_opendir(const char * path);

/**
 * Close a previously open directory
 *
 * Inputs:
 * dir = the directory handle to close
 *
 * Returns:
 * 0 on success, negative number on error
 */
extern short sys_fsys_closedir(short dir);

/**
 * Attempt to read an entry from an open directory
 *
 * Inputs:
 * dir = the handle of the open directory
 * file = pointer to the t_file_info structure to fill out.
 *
 * Returns:
 * 0 on success, negative number on failure
 */
extern short sys_fsys_readdir(short dir, p_file_info file);

/**
 * Open a directory given the path and search for the first file matching the pattern.
 *
 * Inputs:
 * path = the path to the directory to search
 * pattern = the file name pattern to search for
 * file = pointer to the t_file_info structure to fill out
 *
 * Returns:
 * the directory handle to use for subsequent calls if >= 0, error if negative
 */
extern short sys_fsys_findfirst(const char * path, const char * pattern, p_file_info file);

/**
 * Open a directory given the path and search for the first file matching the pattern.
 *
 * Inputs:
 * dir = the handle to the directory (returned by fsys_findfirst) to search
 * file = pointer to the t_file_info structure to fill out
 *
 * Returns:
 * 0 on success, error if negative
 */
extern short sys_fsys_findnext(short dir, p_file_info file);

/**
 * Delete a file or directory
 *
 * Inputs:
 * path = the path of the file or directory to delete.
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
extern short sys_fsys_delete(const char * path);

/**
 * Rename a file or directory
 *
 * Inputs:
 * old_path = the current path to the file
 * new_path = the new path for the file
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
extern short sys_fsys_rename(const char * old_path, const char * new_path);

/**
 * Create a directory
 *
 * Inputs:
 * path = the path of the directory to create.
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
extern short sys_fsys_mkdir(const char * path);

/*
 * Load a file into memory at the designated destination address.
 *
 * If destination = 0, the file must be in a recognized binary format
 * that specifies its own loading address.
 *
 * Inputs:
 * path = the path to the file to load
 * destination = the destination address (0 for use file's address)
 * start = pointer to the long variable to fill with the starting address
 *         (0 if not an executable, any other number if file is executable
 *         with a known starting address)
 *
 * Returns:
 * 0 on success, negative number on error
 */
extern short sys_fsys_load(const char * path, long destination, long * start);

/*
 * Get the label for the drive holding the path
 *
 * Inputs:
 * path = path to the drive
 * label = buffer that will hold the label... should be at least 35 bytes
 */
extern short sys_fsys_get_label(const char * path, char * label);

/*
 * Set the label for the drive holding the path
 *
 * Inputs:
 * drive = drive number
 * label = buffer that holds the label
 */
extern short sys_fsys_set_label(short drive, const char * label);

/**
 * Change the current working directory (and drive)
 *
 * Inputs:
 * path = the path that should be the new current
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
extern short sys_fsys_setcwd(const char * path);

/**
 * Get the current working drive and directory
 *
 * Inputs:
 * path = the buffer in which to store the directory
 * size = the size of the buffer in bytes
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
extern short sys_fsys_getcwd(char * path, short size);

/*
 * Register a file loading routine
 *
 * A file loader, takes a channel number to load from and returns a
 * short that is the status of the load.
 *
 * Inputs:
 * extension = the file extension to map to
 * loader = pointer to the file load routine to add
 *
 * Returns:
 * 0 on success, negative number on error
 */
extern short sys_fsys_register_loader(const char * extension, p_file_loader loader);

/* 
 * Process and memory calls
 */

/*
 * Load and run an executable binary file
 *
 * Inputs:
 *  path = pointer to path to the file to run
 *  argc = number of arguments to pass to the executable
 *  argv = array of strings containing the parameters
 *
 * Returns:
 *  Any value is an error (don't expect any return on susses)
 */
extern short sys_proc_run( const char *path, int argc, char *argv[]);

/*
 * Get the upper limit of accessible RAM
 *
 * Inputs:
 *  none
 *
 * Returns:
 *  Address of first byte of RAM block
 */
extern unsigned long sys_mem_get_ramtop();

/*
 * Reserve a block of memory from top of system RAM
 *
 * Inputs:
 *  size = number of bytes to reserve
 *
 * Returns:
 *  Address of first byte of non-accessible RAM area
 */
extern unsigned long sys_mem_reserve( unsigned long size );

/*
 * Raise the privilege level of this program/process to the highest level
 *
 * Inputs:
 *  none (single tasking operating system)
 *
 * Returns:
 *  none
 */
extern void sys_proc_elevate();

/*
 * Set the value of a system variable
 *
 * Inputs:
 *  name = name of the system variable (pointer to string)
 *  value = value of the system variable (pointer to string)
 *
 * Returns:
 *  0 on success, any other number on error
 */
extern short sys_var_set( const char *name, const char *value );

/*
 * Get the value of a system variable
 *
 * Inputs:
 *  name = name of the system variable (pointer to string)
 *
 * Returns:
 *  pointer to string as value of the system variable
 *  0 if name of variable was not found
 */
extern const char *sys_var_get( const char *name );

/*
 * Miscellaneous
 */

/*
 * Get the number of jiffies since the system last booted.
 *
 * NOTE: a jiffie is 1/60 of a second. This timer will not be
 *       100% precise, so it should be used for timeout purposes
 *       where precision is not critical.
 *
 * Returns:
 * the number of jiffies since the last reset
 */
extern long sys_time_jiffies();

/*
 * Set the time on the RTC
 *
 * Inputs:
 * time = pointer to a t_time record containing the correct time
 */
extern void sys_time_setrtc(p_time time);

/*
 * Get the time on the RTC
 *
 * Inputs:
 * time = pointer to a t_time record in which to put the current time
 */
extern void sys_time_getrtc(p_time time);

/*
 * Return the next scan code from the keyboard... 0 if nothing pending
 */
extern unsigned short sys_kbd_scancode();

/*
 * Set the keyboard translation tables
 *
 * The translation tables provided to the keyboard consist of eight
 * consecutive tables of 128 characters each. Each table maps from
 * the MAKE scan code of a key to its appropriate 8-bit character code.
 *
 * The tables included must include, in order:
 * - UNMODIFIED: Used when no modifier keys are pressed or active
 * - SHIFT: Used when the SHIFT modifier is pressed
 * - CTRL: Used when the CTRL modifier is pressed
 * - CTRL-SHIFT: Used when both CTRL and SHIFT are pressed
 * - CAPSLOCK: Used when CAPSLOCK is down but SHIFT is not pressed
 * - CAPSLOCK-SHIFT: Used when CAPSLOCK is down and SHIFT is pressed
 * - ALT: Used when only ALT is presse
 * - ALT-SHIFT: Used when ALT is pressed and either CAPSLOCK is down
 *   or SHIFT is pressed (but not both)
 * 
 * Inputs:
 * tables = pointer to the keyboard translation tables
 */
extern short sys_kbd_setlayout(const char * tables);

/*
 * Return an error message given an error number
 */
extern const char * sys_err_message(short err_number);


/**
 * Text Display calls
 **/

/*
 * Reset a screen to its default text mode
 *
 * Inputs:
 *  screen = screenID of the screen
 *
 * Returns:
 *  nothing
 */
extern void sys_txt_init_screen( short screen );

/*
 * Return a description of a screen's capabilities
 *
 * Inputs:
 *  screen = screenID of the screen
 *
 * Returns:
 *  pointer to txt_capabilities structure (p_txt_capabilities)
 */
const p_txt_capabilities sys_txt_get_caps( short screen );

/*
 * Set the display mode of a screen
 *
 * Inputs:
 *  screen = screenID of the screen
 *  mode = desired mode (one from TXT_MODE_TEXT, TXT_MODE_BITMAP, TXT_MODE_TILE, 
 *                          TXT_MODE_SPRITE, TXT_MODE_SLEEP)
 *
 * Returns:
 *  0 on success, any other number means error
 */
short sys_txt_set_mode( short screen, short mode );

/*
 * Set text screen device driver to current screen geometry (resolution, border size)
 *
 * Inputs:
 *  none
 *
 * Returns:
 *  0 on succcess or any other number on error
 */
void sys_txt_setsizes();

/*
 * Set the base display resolution of the screen
 *
 * Inputs:
 *  screen = screenID of the screen
 *  horizontal = number of horizontal pixels
 *  vertical = number of verticl pixels
 *
 * Returns:
 *  0 on success, any other number means error
 */
short sys_txt_set_resolution( short screen, short horizontal, short vertical );

/*
 * Set the size of the border (around the screen)
 *
 * Inputs:
 *  screen = screenID of the screen
 *  width = border width left and right of the screen in pixels
 *  height = border height top and bottom of the screen in pixels
 *
 * Returns:
 *  nothing
 */
void sys_txt_set_border( short screen, short width, short height );

/*
 * Set the color of the border (around the screen) with RGB components
 *
 * Inputs:
 *  screen = screenID of the screen
 *  red = red component of color (0-255)
 *  green = green component of color (0-255)
 *  blue = blue component of border (0-255)
 *
 * Returns:
 *  nothing
 */
void sys_txt_set_border_color( short screen, uint8_t red,
                                uint8_t green, uint8_t blue );

/*
 * Set the font to be used in text mode for the screen
 *
 * Inputs:
 *  screen = screenID of the screen
 *  width = width of the characters in pixels
 *  height = height of the characters in pixels
 *  data = pointer to font data
 *
 * Returns:
 *  0 on success, any other number means error (invalid screen, invalid font size)
 */
short sys_txt_set_font( short screen, short width, short height, 
                                unsigned char *data );

/*
 * Set the appearance of the text mode cursor
 *
 * Inputs:
 *  screen = screenID of the screen
 *  enable = hide(0) or show (any other number) cursor
 *  rate = blink rate of the cursor (in Hz, see MCP manual for ranges)
 *  character = ASCII code of the glyph from the screen's font as the cursor
 *
 * Returns:
 *  0 on success, any other number means error
 */
short sys_txt_set_cursor( short screen, short enable, short rate, char character );

/*
 * Set the rectangular region of the screen that will be used for printing,
 * scrolling and filling.
 *
 * Inputs:
 *  screen = screenID of the screen
 *  region = pointer to t_rect structure (upper left corner, width, height)
 *              coordinates in character cells. (0,0) is upper-left,
 *              size 0 means fullscreen
 *
 * Returns:
 *  0 on success, any other number means error
 */
short sys_txt_set_region( short screen, p_rect region );

/*
 * Set the foreground and background color for subsequent printing to the screen
 *
 * Inputs:
 *  screen = screenID of the screen
 *  foreground = color index for foreground color (0-15)
 *  background = color index for background color (0-15)
 *
 * Returns:
 *  0 on success, any other number means error
 */
short sys_txt_set_color( short screen, short foreground, short background );

/*
 * Get the current foreground and background color
 *
 * Inputs:
 *  screen = screenID of the screen
 *  foreground = pointer to retrieve color index for foreground color (0-15)
 *  background = pointer to retrieve color index for background color (0-15)
 *
 * Returns:
 *  0 on success, any other number means error
 */
 short sys_txt_get_color( short screen, short *foreground, short *background );

 /*
 * Set cursor position on the screen, relative to origin of current region
 *
 * Inputs:
 *  screen = screenID of the screen
 *  x = relative x position (in character positions)
 *  y = relative y position (in character positions)
 *
 * Returns:
 *  nothing
 */
void sys_txt_set_xy( short screen, short x, short y );

/*
 * Get cursor position on the screen, relative to origin of current region
 *
 * Inputs:
 *  screen = screenID of the screen
 *  position = pointer to x,y structure to retrive position
 *
 * Returns:
 *  nothing
 */
void sys_txt_get_xy( short screen, p_point position );

/*
 * Scroll the text in the current region
 *
 * Inputs:
 *  screen = screenID of the screen
 *  horizontal = number of horizontal pixels to scroll
 *  vertical = number of verticl pixels to scroll
 *
 * Returns:
 *  nothing
 */
void sys_txt_scroll( short screen, short horizontal, short vertical );

/*
 * Set visibility of the cursor
 *
 * Inputs:
 *  screen = screenID of the screen
 *  is_visible = hidden (FALSE or 0) or visible (any other number)
 *
 * Returns:
 *  nothing
 */
void sys_txt_set_cursor_vis( short screen, short is_visible );

/*
 * SGet screensize in total pixels (so without taking the border into consideration)
 *
 * Inputs:
 *  screen = screenID of the screen
 *  text_size = pointer to t_extent structure to retrieve size in visible characters
 *  pixel_size = pointer to t_extent structure to retrieve size in pixels
 *
 * Returns:
 *  nothing
 */
void sys_txt_get_sizes( short screen, p_extent text_size, p_extent pixel_size );


#endif
