# Personal-OS-Project [Project created for CS 421 - Operating Systems]


This project was developed over the course of a month utilizing cfenollosa's OS tutorial found here: https://github.com/cfenollosa/os-tutorial and a bit of the OSDev Wiki

Overall the OS functions as a monolithic kernel, has a working shell, and very barebones memory management system that simply allocates a memory pool that can be used by the program. 


I added commands that make manipulation of memory to be possible, these commands help with the simulation of a file management system which I attempted to implement utilizing a single linked list. These commands are:

Make - reserves a block of memory to create a 'file' or variable (depending on what you want to classify this as)

Copy - copies a 'file'/variable depending on if its found

Move - swaps two files/variables

Delete - deletes a select file/variable if its within memory

Rename - renames a selected file/variable if its within memory

List - lists the current files/variables inside the memory pool

You can feel free to play around with each of these commands and for the syntax you can type in "help" within the command to get further explanations of each of these commands
