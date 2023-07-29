#include "fileSystem.h"
#include "screen.h"
#include <stdbool.h>
#include <stddef.h>
#include "../libc/string.h"
#include "../libc/mem.h"
// Simulates a linked sequential file structure
// It should be worth noting that there is a minor bug with copy, where sometimes using it in conjuction with move will cause one of the 'files' to be overwritten, same with rename
// Otherwise, on their own they work
struct directory {
    char* filename; // Saves filename into the directory
    struct directory *next; 
};
struct directory* head = NULL;
size_t numOfNodes = 0; 
// Helper function
struct directory* createNode(const char* data) {
    struct directory* newNode = (struct directory*)kmalloc(sizeof(struct directory));
    newNode->filename = strdup(data); // Basically allocates memory to the character
    newNode->next = NULL;
    return newNode;
}

void makeFile(const char *fileName){ 
    struct directory* newFile = createNode(fileName);
    if(head == NULL){
        head = newFile;
        numOfNodes++;
    }
    else{
        struct directory* current = head;
        while(current->next != NULL){
            current = current->next;

        }
        current->next = newFile;
        numOfNodes++;
    }
}
void copyFile(const char *fileName){ 
    // Find node with filename
    bool found = false;
    char* newFileName;
    struct directory* current = head;
    if(head == NULL){
        kprint("The directory is empty");
        kprint("\n");
        return; // meaning there's no files
    }
    // If found, copy name, allocate new node, and add it to the file system
    while(current != NULL){ // searches for current
        if(strcmp(fileName, current->filename) == 0){ // If they are the same
            newFileName = current->filename; // Save filename
            found = true; // Mark that it was foun
            break;
        }
        current = current->next;
    }
    if(found){
        makeFile(newFileName); // Makes copy of file
    }
    else{
        kprint("There are no files to copied");
        kprint("\n");
    }  
}
void deleteFile(char *fileName){
    // Needs to find filename
    // If not found, nothing is deleted
    if(head == NULL){
        kprint("The directory is empty.");
        kprint("\n");
        return;
    }
    struct directory* current = head;
    struct directory* previous = NULL;
    while(current != NULL && strcmp(fileName, current->filename) != 0){ // Finds node
        previous = current; // Keeps track of node
        current = current->next;
    }
    // If found, delete node
    if(current != NULL){
        if(previous == NULL){
            head = current->next;
            numOfNodes--;
        }
        else{
            previous->next = current->next; // Link other files together
            numOfNodes--;
        }
    }

}
void listOfFiles(){
    struct directory* current = head;
    kprint("===CURRENT DIRECTORY===\n");
    for(int i = 0; i < numOfNodes; i++){
        kprint(current->filename);
        kprint("\n");
        current = current->next;
    }
}
void moveFile(char *firstFile, char* secondFile){
    if(strcmp(firstFile, secondFile) == 0){ 
        kprint("These files are the same");
        return;
    }
    struct directory* previousFirstFile = NULL;
    struct directory* currentFirstFile = head;
    while(currentFirstFile && strcmp(currentFirstFile->filename, firstFile) != 0){ // Search for the first file
        previousFirstFile = currentFirstFile;
        currentFirstFile = currentFirstFile->next; // Traversal
    }
    struct directory* previousSecondFile = NULL;
    struct directory* currentSecondFile = head;
    while(currentSecondFile && strcmp(currentSecondFile->filename, secondFile) != 0){ // Search for the second file
        previousSecondFile = currentSecondFile;
        currentSecondFile = currentSecondFile->next; // Traversal
    }
    if(currentFirstFile == NULL || currentSecondFile == NULL){ // if one or the other is not found
        kprint("One or both of the files was not found.");
    }
    if(previousFirstFile != NULL){ // if first file isn't at the beginning of the directory
        previousFirstFile->next = currentSecondFile;
    }
    else{
        head = currentSecondFile;
    }
    if(previousSecondFile != NULL){ // if second file isn't at the beginning of the directory
        previousSecondFile->next = currentFirstFile;
    }
    else{
        head = currentFirstFile;
    }
    // Swap the two files
    struct directory* placeholder = currentSecondFile->next;
    currentSecondFile->next = currentFirstFile->next; 
    currentFirstFile->next = placeholder;
}
void renameFile(char* fileName, char* desiredFileName){
    bool found = false;
     if(head == NULL){
        kprint("The directory is empty.");
        kprint("\n");
        return;
    }
    struct directory* current = head;
    while(current != NULL){ // Finds file and traverses
        if(strcmp(fileName, current->filename) == 0){ // If they are the same
            current->filename = desiredFileName; // Changes filename
            found = true;
            break; // Break from file search
        }
        current = current->next;
    }
    if(!found){
        kprint("File doesn't exist");
    }
}
