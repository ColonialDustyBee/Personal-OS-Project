#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
#include "../drivers/fileSystem.h"


void kernel_main() {
    init_memory_manager(); // Initializes memory manager
    isr_install();
    irq_install();
    kprint("Welcome to J OS\n");
    kprint("Type something, it will go through the kernel\n"
        "Type END to terminate the OS\n"
        "Type HELP for a list of commands\n>");
}

void user_input(char *input) { // allows for user input thru the kernel
    // Allows for input - MAKE filename.txt and so on
    char* command = strtok(input, " ");  // Tokenize the input to get the command
    char* filename = strtok(NULL, " ");  // Tokenize further to get the filename (if required)
    char* secondFileName = strtok(NULL, " "); // For another file
    if (strcmp(input, "END") == 0) {
        kprint("Terminated the OS!\n");
        asm volatile("hlt");
    }
    else if(strcmp(command, "HELP") == 0){
        kprint("===LIST OF COMMANDS===\n");
        kprint("MAKE filename - use the command MAKE and the filename to make a new file in the directory\n");
        kprint("COPY filename - use the command COPY and filename to find the filename and copy it within the directory\n");
        kprint("MOVE firstfile secondfile - use command MOVE firstfile secondfile to swap the two. Ensure that there is a space between firstfile and secondfile for it to work\n");
        kprint("DEL filename - use DEL filename to delete file\n");
        kprint("RENAME filename desiredfilename - use RENAME filename desiredfilename to rename a filename to something else. Again ensure there is a space between filename and desiredfilename for it to work\n");
        kprint("LIST - use LIST to list current directory\n");
    } 
    else if (strcmp(command, "MAKE") == 0) {
        kprint("Creating file: ");
        kprint(filename);
        kprint("\n");
        makeFile(filename);
    }
    else if(strcmp(command, "COPY") == 0){
        kprint("Copying file: ");
        kprint(filename);
        kprint("\n");
        copyFile(filename);
    }
    else if(strcmp(command, "MOVE") == 0){
        kprint("Moving files: ");
        kprint(filename);
        kprint(" and ");
        kprint(secondFileName);
        kprint("\n");
        moveFile(filename, secondFileName);
    }
    else if(strcmp(command, "DEL") == 0){
        kprint("Deleting file: ");
        kprint(filename);
        kprint("\n");
        deleteFile(filename);
    }
    else if(strcmp(command, "RENAME") == 0){
        kprint("Renaming: ");
        kprint(filename);
        kprint(" to ");
        kprint(secondFileName);
        kprint("\n");
        renameFile(filename, secondFileName);
    }
    else if(strcmp(command, "LIST") == 0){
        listOfFiles();
    }
    kprint("\n>");
}
