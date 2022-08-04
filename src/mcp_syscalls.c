#include <mcp/syscalls.h>

/***
 *** Core system calls
 ***/

/*
 * Stop running the current user program
 *
 * Inputs:
 * result = the result code to return to the kernel
 */
void sys_exit(short result) {
    t_syscall_params params = {.arg1 = result};
    syscall(KFN_EXIT, &params);
}

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
p_int_handler sys_int_register(unsigned short n, p_int_handler handler) {
    t_syscall_params params = {.arg1 = n, .arg2 = (int32_t) handler};
    return (p_int_handler) syscall(KFN_INT_REGISTER, &params);
}

/*
 * Enable an interrupt
 *
 * Inputs:
 * n = the number of the interrupt
 */
void sys_int_enable(unsigned short n) {
    t_syscall_params params = {.arg1 = n};
    syscall(KFN_INT_ENABLE, &params);
}

/*
 * Disable an interrupt by masking it
 *
 * Inputs:
 * n = the number of the interrupt: n[7..4] = group number, n[3..0] = individual number.
 */
void sys_int_disable(unsigned short n) {
    t_syscall_params params = {.arg1 = n};
    syscall(KFN_INT_DISABLE, &params);
}
/*
 * Enable all interrupts
 *
 * NOTE: this is actually provided in the low level assembly
 */
void sys_int_enable_all() {
    t_syscall_params params = {0};
    syscall(KFN_INT_ENABLE_ALL, &params);
}

/*
 * Disable all interrupts
 *
 * NOTE: this is actually provided in the low level assembly
 */
void sys_int_disable_all() {
    t_syscall_params params = {0};
    syscall(KFN_INT_DISABLE_ALL, &params);
}

/*
 * Acknowledge an interrupt (clear out its pending flag)
 *
 * Inputs:
 * n = the number of the interrupt: n[7..4] = group number, n[3..0] = individual number.
 */
void sys_int_clear(unsigned short n) {
    t_syscall_params params = {.arg1 = n};
    syscall(KFN_INT_CLEAR, &params);
}

/*
 * Return true (non-zero) if an interrupt is pending for the given interrupt
 *
 * Inputs:
 * n = the number of the interrupt: n[7..4] = group number, n[3..0] = individual number.
 *
 * Returns:
 * non-zero if interrupt n is pending, 0 if not
 */
short sys_int_pending(unsigned short n) {
    t_syscall_params params = {.arg1 = n};
    return syscall(KFN_INT_PENDING, &params);
}
/*
 * Fill out a s_sys_info structure with the information about the current system
 *
 * Inputs:
 * info = pointer to a s_sys_info structure to fill out
 */
void sys_get_info(p_sys_info info) {
    t_syscall_params params = {.arg1 = (int32_t) info};
    syscall(KFN_SYS_GET_INFO, &params);
}

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
short sys_chan_read(short channel, unsigned char * buffer, short size) {
    t_syscall_params params = {.arg1 = channel, .arg2 = (int32_t) buffer, .arg3 = size};
    return syscall(KFN_CHAN_READ, &params);
}

/*
 * Read a single byte from the channel
 *
 * Inputs:
 *  channel = the number of the channel
 *
 * Returns:
 *  the value read (if negative, error)
 */
short sys_chan_read_b(short channel) {
    t_syscall_params params = {.arg1 = channel};
    return syscall(KFN_CHAN_READ_B, &params);
}
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
short sys_chan_readline(short channel, unsigned char * buffer, short size) {
    t_syscall_params params = {.arg1 = channel, .arg2 = (int32_t) buffer, .arg3 = size};
    return syscall(KFN_CHAN_READ_LINE, &params);
}

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
short sys_chan_write(short channel, unsigned char * buffer, short size) {
    t_syscall_params params = {.arg1 = channel, .arg2 = (int32_t) buffer, .arg3 = size};
    return syscall(KFN_CHAN_WRITE, &params);
}

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
short sys_chan_write_b(short channel, unsigned char b) {
    t_syscall_params params = {.arg1 = channel, .arg2 = b};
    return syscall(KFN_CHAN_WRITE_B, &params);
}

/*
 * Ensure that any pending writes to teh device have been completed
 *
 * Inputs:
 *  channel = the number of the channel
 *
 * Returns:
 *  0 on success, any negative number is an error code
 */
short sys_chan_flush(short channel) {
    t_syscall_params params = {.arg1 = channel};
    return syscall(KFN_CHAN_FLUSH, &params);
}

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
short sys_chan_seek(short channel, long position, short base) {
    t_syscall_params params = {.arg1 = channel, .arg2 = position, .arg3 = base};
    return syscall(KFN_CHAN_SEEK, &params);
}

/*
 * Return the status of the channel device
 *
 * Inputs:
 *  channel = the number of the channel
 *
 * Returns:
 *  the status of the device
 */
short sys_chan_status(short channel) {
    t_syscall_params params = {.arg1 = channel};
    return syscall(KFN_CHAN_STATUS, &params);
}

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
short sys_chan_ioctrl(short channel, short command, uint8_t * buffer, short size) {
    t_syscall_params params = {.arg1 = channel, .arg2 = command, .arg3 = (int32_t) buffer, .arg4 = size};
    return syscall(KFN_CHAN_IOCTRL, &params);
}

/*
 * Register a channel device driver (NOT TESTED) <>
 *
 * Inputs:
 *  device = pointer to the device, including handler functions
 *
 * Returns:
 *  <>
 */
short sys_chan_register(struct s_dev_chan *device) {
    t_syscall_params params = {.arg1 = (int32_t)device};
    return syscall(KFN_CHAN_REGISTER, &params);
}

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
short sys_chan_open(short dev, uint8_t * path, short mode) {
    t_syscall_params params = {.arg1 = (int32_t) path, .arg2 = mode};
    return syscall(KFN_CHAN_OPEN, &params);
}

/*
 * Close a channel
 *
 * Inputs:
 * chan = the number of the channel to close
 *
 * Returns:
 * nothing useful
 */
short sys_chan_close(short chan) {
    t_syscall_params params = {.arg1 = chan};
    return syscall(KFN_CHAN_CLOSE, &params);
}

/* Swap two channels (given their IDS)
 *
 * Inputs:
 *  channel1, channel2 = channel IDs to be swapped
 *
 * Returns:
 *  0 on success, any other on error
 */
short sys_chan_swap(short channel1, short channel2) {
    t_syscall_params params = {.arg1 = channel1, .arg2 = channel2};
    return syscall(KFN_CHAN_SWAP, &params);
}

/* Get the device ID of the device on  a channel
 *
 * Inputs:
 *  channel = channel of the device
 *
 * Returns:
 *  device ID of the device on the channel
 */
short sys_chan_device(short channel) {
    t_syscall_params params = {.arg1 = channel};
    return syscall(KFN_CHAN_DEVICE, &params);
}


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
short sys_bdev_getblock(short dev, long lba, unsigned char * buffer, short size) {
    t_syscall_params params = {.arg1 = dev, .arg2 = lba, .arg3 = (int32_t) buffer, .arg4 = size};
    return syscall(KFN_BDEV_GETBLOCK, &params);
}

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
short sys_bdev_putblock(short dev, long lba, const unsigned char * buffer, short size) {
    t_syscall_params params = {.arg1 = dev, .arg2 = lba, .arg3 = (int32_t) buffer, .arg4 = size};
    return syscall(KFN_BDEV_PUTBLOCK, &params);
}

//
// Ensure that any pending writes to teh device have been completed
//
// Inputs:
//  dev = the number of the device
//
// Returns:
//  0 on success, any negative number is an error code
//
short sys_bdev_flush(short dev) {
    t_syscall_params params = {.arg1 = dev};
    return syscall(KFN_BDEV_FLUSH, &params);
}

//
// Return the status of the block device
//
// Inputs:
//  dev = the number of the device
//
// Returns:
//  the status of the device
//
short sys_bdev_status(short dev) {
    t_syscall_params params = {.arg1 = dev};
    return syscall(KFN_BDEV_STATUS, &params);
}


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
short sys_bdev_ioctrl(short dev, short command, unsigned char * buffer, short size) {
    t_syscall_params params = {.arg1 = dev, .arg2 = command, .arg3 = (int32_t) buffer, .arg4 = size};
    return syscall(KFN_BDEV_IOCTRL, &params);
}

//
// Register a block device driver
//
short sys_bdev_register(p_dev_block device) {
    t_syscall_params params = {.arg1 = (int32_t) device};
    return syscall(KFN_BDEV_REGISTER, &params);
}


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
short sys_fsys_open(const char * path, short mode) {
    t_syscall_params params = {.arg1 = (int32_t) path, .arg2 = mode};
    return syscall(KFN_OPEN, &params);
}

/**
 * Close access to a previously open file.
 *
 * Inputs:
 * fd = the channel ID for the file
 *
 * Returns:
 * 0 on success, negative number on failure
 */
short sys_fsys_close(short fd) {
    t_syscall_params params = {.arg1 = fd};
    return syscall(KFN_CLOSE, &params);
}

/**
 * Attempt to open a directory for scanning
 *
 * Inputs:
 * path = the path to the directory to open
 *
 * Returns:
 * the handle to the directory if >= 0. An error if < 0
 */
short sys_fsys_opendir(const char * path) {
    t_syscall_params params = {.arg1 = (int32_t) path};
    return syscall(KFN_OPENDIR, &params);
}

/**
 * Close a previously open directory
 *
 * Inputs:
 * dir = the directory handle to close
 *
 * Returns:
 * 0 on success, negative number on error
 */
short sys_fsys_closedir(short dir) {
    t_syscall_params params = {.arg1 = dir};
    return syscall(KFN_CLOSEDIR, &params);
}

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
short sys_fsys_readdir(short dir, p_file_info file) {
    t_syscall_params params = {.arg1 = dir, .arg2 = (int32_t) file};
    return syscall(KFN_READDIR, &params);
}

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
short sys_fsys_findfirst(const char * path, const char * pattern, p_file_info file) {
    t_syscall_params params = {.arg1 = (int32_t) path, .arg2 = (int32_t) pattern, .arg3 = (int32_t) file};
    return syscall(KFN_FINDFIRST, &params);
}

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
short sys_fsys_findnext(short dir, p_file_info file) {
    t_syscall_params params = {.arg1 = dir, .arg2 = (int32_t) file};
    return syscall(KFN_FINDNEXT, &params);
}

/**
 * Delete a file or directory
 *
 * Inputs:
 * path = the path of the file or directory to delete.
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
short sys_fsys_delete(const char * path) {
    t_syscall_params params = {.arg1 = (int32_t) path};
    return syscall(KFN_DELETE, &params);
}

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
short sys_fsys_rename(const char * old_path, const char * new_path) {
    t_syscall_params params = {.arg1 = (int32_t) old_path, .arg2 = (int32_t) new_path};
    return syscall(KFN_RENAME, &params);
}

/**
 * Create a directory
 *
 * Inputs:
 * path = the path of the directory to create.
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
short sys_fsys_mkdir(const char * path) {
    t_syscall_params params = {.arg1 = (int32_t) path};
    return syscall(KFN_MKDIR, &params);
}

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
short sys_fsys_load(const char * path, long destination, long * start) {
    t_syscall_params params = {.arg1 = (int32_t) path, .arg2 = destination, .arg3 = (int32_t) start};
    return syscall(KFN_LOAD, &params);
}

/*
 * Get the label for the drive holding the path
 *
 * Inputs:
 * path = path to the drive
 * label = buffer that will hold the label... should be at least 35 bytes
 */
short sys_fsys_get_label(const char * path, char * label) {
    t_syscall_params params = {.arg1 = (int32_t) path, .arg2 = (int32_t) label};
    return syscall(KFN_GET_LABEL, &params);
}

/*
 * Set the label for the drive holding the path
 *
 * Inputs:
 * drive = drive number
 * label = buffer that holds the label
 */
short sys_fsys_set_label(short drive, const char * label) {
    t_syscall_params params = {.arg1 = drive, .arg2 = (int32_t) label};
    return syscall(KFN_SET_LABEL, &params);
}

/**
 * Change the current working directory (and drive)
 *
 * Inputs:
 * path = the path that should be the new current
 *
 * Returns:
 * 0 on success, negative number on failure.
 */
short sys_fsys_set_cwd(const char * path) {
    t_syscall_params params = {.arg1 = (int32_t) path};
    return syscall(KFN_SET_CWD, &params);
}

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
short sys_fsys_get_cwd(char * path, short size) {
    t_syscall_params params = {.arg1 = (int32_t) path, .arg2 = size};
    return syscall(KFN_GET_CWD, &params);
}

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
short sys_fsys_register_loader(const char * extension, p_file_loader loader) {
    t_syscall_params params = {.arg1 = (int32_t) extension, .arg2 = (int32_t) loader};
    return syscall(KFN_LOAD_REGISTER, &params);
}


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
short sys_proc_run( const char *path, int argc, char *argv[]) {
    t_syscall_params params = {.arg1 = (int32_t)path, .arg2 = argc, (int32_t)argv};
    return syscall(KFN_PROC_RUN, &params);
}

/*
 * Get the upper limit of accessible RAM
 *
 * Inputs:
 *  none
 *
 * Returns:
 *  Address of first byte of non-accessible RAM area
 */
unsigned long sys_mem_get_ramtop() {
    t_syscall_params params = {0};
    return syscall(KFN_MEM_GET_RAMTOP, &params);
}

/*
 * Get the upper limit of accessible RAM
 *
 * Inputs:
 *  none
 *
 * Returns:
 *  Address of first byte of RAM block
 */
unsigned long sys_mem_reserve( unsigned long size ) {
    t_syscall_params params = {.arg1 = (uint32_t)size};
    return syscall(KFN_MEM_RESERVE, &params);
}

/*
 * Raise the privilege level of this program/process to the highest level
 *
 * Inputs:
 *  none (single tasking operating system)
 *
 * Returns:
 *  none
 */
void sys_proc_elevate() {
    t_syscall_params params = {0};
    syscall(KFN_PROC_ELEVATE, &params);
}

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
extern short sys_var_set( const char *name, const char *value ) {
    t_syscall_params params = {.arg1 = (uint32_t)name, .arg2= (uint32_t)value};
    return syscall(KFN_VAR_SET, &params);
}

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
const char *sys_var_get( const char *name ) {
    t_syscall_params params = {.arg1 = (uint32_t)name};
    return (const char *)syscall(KFN_VAR_GET, &params);
}

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
long sys_time_jiffies() {
    t_syscall_params params = {0};
    return syscall(KFN_TIME_JIFFIES, &params);
}

/*
 * Set the time on the RTC
 *
 * Inputs:
 * time = pointer to a t_time record containing the correct time
 */
void sys_time_setrtc(p_time time) {
    t_syscall_params params = {.arg1 = (int32_t) time};
    syscall(KFN_TIME_SETRTC, &params);
}

/*
 * Get the time on the RTC
 *
 * Inputs:
 * time = pointer to a t_time record in which to put the current time
 */
void sys_time_getrtc(p_time time) {
    t_syscall_params params = {.arg1 = (int32_t) time};
    syscall(KFN_TIME_GETRTC, &params);
}

/*
 * Return the next scan code from the keyboard... 0 if nothing pending
 */
unsigned short sys_kbd_scancode() {
    t_syscall_params params = {0};
    return syscall(KFN_KBD_SCANCODE, &params);
}

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
short sys_kbd_setlayout(const char * tables) {
    t_syscall_params params = {.arg1 = (int32_t) tables};
    return syscall(KFN_KBD_LAYOUT, &params);
}

/*
 * Return an error message given an error number
 */
const char * sys_err_message(short err_number) {
    t_syscall_params params = {.arg1 = err_number};
    return (const char *) syscall(KFN_ERR_MESSAGE, &params);
}

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
extern void sys_txt_init_screen( short screen ) {
    t_syscall_params params = {.arg1 = screen};
    syscall(KFN_TXT_INIT_SCREEN, &params);
}

/*
 * Return a description of a screen's capabilities
 *
 * Inputs:
 *  screen = screenID of the screen
 *
 * Returns:
 *  pointer to txt_capabilities structure (p_txt_capabilities)
 */
const p_txt_capabilities sys_txt_get_caps( short screen ) {
    t_syscall_params params = {.arg1 = screen};
    return (p_txt_capabilities) syscall(KFN_TXT_GET_CAPS, &params);
}

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
short sys_txt_set_mode( short screen, short mode ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = mode};
    return syscall(KFN_TXT_SET_MODE, &params);
}

/*
 * Set text screen device driver to current screen geometry (resolution, border size)
 *
 * Inputs:
 *  none
 *
 * Returns:
 *  0 on succcess or any other number on error
 */
void sys_txt_setsizes() {
    t_syscall_params params = {0};
    syscall(KFN_TXT_SETSIZES, &params);
}

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
short sys_txt_set_resolution( short screen, short horizontal, short vertical ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = horizontal, .arg3 = vertical};
    return syscall(KFN_TXT_SET_RESOLUTION, &params);
}

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
void sys_txt_set_border( short screen, short width, short height ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = width, .arg3 = height};
    syscall(KFN_TXT_SET_BORDER, &params);
}

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
                                uint8_t green, uint8_t blue ) {
    t_syscall_params params = {.arg1 = screen,
                                .arg2 = red, .arg3 = green, .arg4 = blue};
    syscall(KFN_TXT_SET_BORDER_COLOR, &params);
}

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
                                unsigned char *data ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = width, .arg3 = height,
                                .arg4 = (uint32_t)data};
    return syscall(KFN_TXT_SET_FONT, &params);
}

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
short sys_txt_set_cursor( short screen, short enable, short rate, char character ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = enable,
                                .arg3 = rate, .arg4 = character};
    return syscall(KFN_TXT_SET_CURSOR, &params);
}

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
short sys_txt_set_region( short screen, p_rect region ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = (uint32_t)region};
    return syscall(KFN_TXT_SET_REGION, &params);
}

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
short sys_txt_set_color( short screen, short foreground, short background ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = foreground, .arg3 = background};
    return syscall(KFN_TXT_SET_COLOR, &params);
}

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
 short sys_txt_get_color( short screen, short *foreground, short *background ) {
    t_syscall_params params = {.arg1 = screen,
                                .arg2 = (uint32_t)foreground,
                                .arg3 = (uint32_t)background};
    return syscall(KFN_TXT_GET_COLOR, &params);
 }

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
void sys_txt_set_xy( short screen, short x, short y ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = x, .arg3 = y};
    syscall(KFN_TXT_SET_XY, &params);
}

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
void sys_txt_get_xy( short screen, p_point position ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = (uint32_t)position};
    syscall(KFN_TXT_GET_XY, &params);
}

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
void sys_txt_scroll( short screen, short horizontal, short vertical ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = horizontal,
                                .arg3 = vertical};
    syscall(KFN_TXT_SCROLL, &params);
}

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
void sys_txt_set_cursor_vis( short screen, short is_visible ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = is_visible};
    syscall(KFN_TXT_SET_CURSOR_VIS, &params);
}

/*
 * Get screensize in total pixels (so without taking the border into consideration)
 *
 * Inputs:
 *  screen = screenID of the screen
 *  text_size = pointer to t_extent structure to retrieve size in visible characters
 *  pixel_size = pointer to t_extent structure to retrieve size in pixels
 *
 * Returns:
 *  nothing
 */
void sys_txt_get_sizes( short screen, p_extent text_size, p_extent pixel_size ) {
    t_syscall_params params = {.arg1 = screen, .arg2 = (uint32_t)text_size,
                                (uint32_t)pixel_size};
    syscall(KFN_TXT_GET_SIZES, &params);
}
