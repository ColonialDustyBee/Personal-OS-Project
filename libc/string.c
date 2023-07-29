#include "string.h"

// Functions to print strings
void int_to_ascii(int n, char str[]){ // Simple implementation of itoa
    int index, sign;
    if((sign = n) < 0){
        n = -n;
    }
    index = 0;
    do{
        str[index++] = n % 10 + '0'; // changes to ascii value
    }while((n /= 10) > 0);
    
    if(sign < 0){
        str[index++] = '-';
    }
    str[index] = '\0';
    reverse(str);
}
void hex_to_ascii(int n, char str[]){ // Allows hex to be displayed
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t temp;
    int i;
    for(i = 28; i >0; i -= 4){
        temp = (n >> i) & 0xF;
        if(temp == 0 && zeros == 0){
            continue;
        }
        zeros = 1;
        if(temp > 0xA){
            append(str, temp - 0xA + 'a');
        }
        else{
            append(str, temp + '0');
        }
    }
    temp = n & 0xF;
    if(temp >= 0xA){
        append(str, temp - 0xA + 'a');
    
    }
    else{
        append(str, temp + '0');
    }

}
void reverse(char s[]){ // Used to allow screen to scroll without overflowing at the bottom
    int character, index, overflow;
    for(index = 0, overflow = strlen(s) - 1; index < overflow; index++, overflow--){ // Swaps characters to prevent overflow of screen
        character = s[index];
        s[index] = s[overflow];
        s[overflow] = character;
    }
}

int strlen(char s[]){ // Determines length of string
    int length = 0;
    while(s[length] != '\0') 
        ++length;
    return length;
}
void append(char s[], char n){ // used to add stuff
    int length = strlen(s);
    s[length] = n;
    s[length + 1] = '\0';
}
void backspace(char s[]){ // used for backspace
    int length = strlen(s);
    s[length - 1] = '\0';
}

int strcmp(char s1[], char s2[]){ // Used to compare strings 
    int index;
    for (index = 0; s1[index] == s2[index]; index++){
        if(s1[index] == '\0'){
            return 0;
        }
    }
    return s1[index] - s2[index];
}


char* strdup(char* org){
    size_t orgSize; // it CANT be negative
    static char* dup; // Makes a duplicates, different from strcmp
    char* duplicate_offset;

    orgSize = strlen(org); // Gets string length first
    dup = (char* )kmalloc(sizeof(char)*orgSize + 1); // Allocates space for the duplicate
    if(dup == NULL){
        return ((char* )NULL);
    }
    duplicate_offset = dup;
    while(*org){ // Copies the string
        *duplicate_offset = *org;
        duplicate_offset++;
        org++;
    }
    *duplicate_offset = '\0';
    return dup;
}
char* strtok(char* str, const char* delimiters) {
    static char* next_token = NULL; // Keeps track of token
    char* token_start = NULL; // where the string starts

    if (str != NULL) {
       
        next_token = str;
    }

    // Finds start of string with the delimeter
    while (*next_token != '\0') { // Strings usually have the null terminator at the end
        if (!is_delimiter(*next_token, delimiters)) {
            token_start = next_token;
            break;
        }
        next_token++;
    }

    if (token_start == NULL) {
        // No token found
        return NULL;
    }

    // Find the end of the token
    while (*next_token != '\0') {
        if (is_delimiter(*next_token, delimiters)) {
            // Replace the delimiter with null terminator and update the next_token pointer
            *next_token = '\0';
            next_token++;
            break;
        }
        next_token++;
    }

    return token_start;
}
// Helper function to check if a character is a delimiter
static bool is_delimiter(char c, const char* delimiters) {
    while (*delimiters != '\0') {
        if (*delimiters == c) {
            return true;
        }
        delimiters++;
    }
    return false;
}
