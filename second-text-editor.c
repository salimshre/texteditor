#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024                        // Max size for the buffer
#define FILENAME "editor.txt"                // File in the current directory

// Function to read the contents of the file
void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");       // Open the file for reading
    if (file == NULL) {
        printf("Could not open file %s for reading.\n", filename);
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {      // Read each character from the file until EOF
        putchar(ch);                         // Print the character to the console
    }
    fclose(file);                            // Close the file
}

// Function to write content to the file
void writeFile(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");       // Open the file for writing
    if (file == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }
    
    fprintf(file, "%s", content);            // Write the content to the file
    fclose(file);                            // Close the file
}

// Function to get user input and store it in a buffer
void getUserInput(char *buffer, size_t size) {
    char line[256];                          // Temporary buffer for each line of input
    size_t len = 0;                          // Current length of the buffer
    printf("Enter text (end with a single dot '.' on a new line):\n");
    while (fgets(line, sizeof(line), stdin) != NULL) { // Read a line of input from the user
        if (line[0] == '.' && line[1] == '\n') { // Check for termination condition
            break;
        }
        size_t lineLen = strlen(line);        // Get the length of the current line
        if (len + lineLen < size - 1) {       // Check if the buffer has enough space
            strcpy(&buffer[len], line);       // Copy the line to the buffer
            len += lineLen;                   // Update the total length
        } else {
            printf("Buffer full. Cannot add more text.\n");
            break;                            // Exit if the buffer is full
        }
    }
    buffer[len] = '\0';                       // Null-terminate the buffer
}

int main() {
    char buffer[MAX_SIZE] = {0};              // Buffer to hold the user input
    int num;
    
    while (1) { // Infinite loop to keep the program running until the user chooses to exit
        printf("Welcome to the editor!\n");
        printf("\nEnter 1 for writing text\nEnter 2 for reading text\nEnter 0 to exit: ");
        scanf("%d", &num);
        getchar();  // Clear the newline character from the input buffer

        if (num == 1) {
            printf("Writing contents of %s:\n", FILENAME);
            getUserInput(buffer, MAX_SIZE);       // Get input content from the user
            writeFile(FILENAME, buffer);          // Write content to the file
            printf("File saved successfully.\n\n");
        } else if (num == 2) {
            printf("Reading contents of %s:\n", FILENAME);
            readFile(FILENAME);                   // Read content from the file
        } else if (num == 0) {
            printf("Exiting the program. Thank you!\n");
            break; // Exit the loop and terminate the program
        } else {
            printf("Invalid option. Please enter 1, 2, or 0.\n");
        }
    }

    return 0;
}
