/*
Currently this is a mock file system that saves bits of data within the memory itself, 
it doesn't have many capabilities of actual file management or safeguards, this is more so a scaffolding that will simulate the real thing if I ever get around to
implementing a file driver and file management system like FAT
*/
#ifndef FILESYSTEM_H
#define FILESYSTEM_H
// make, copy, delete, dir/ls, move, rename
void makeFile(const char *fileName);
void copyFile(const char *fileName);
void deleteFile(char *fileName);
void listOfFiles();
void moveFile(char *firstFile, char *secondFile);
void renameFile(char* fileName, char* desiredFileName); 
#endif