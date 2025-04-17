#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 999

// Main function at line 186
// Greeting
void welcome() {
	printf("\n============================\n");
	printf("\n         FileInsight     \n");
	printf("\n============================\n");
	printf("\n");
}

// Function to add text to opened file
void add_text(FILE *file) {
    char text[MAX_LINE_LENGTH];
    
    fseek(file, 0, SEEK_END);
    
    while (getchar() != '\n' && getchar() != EOF);
    printf("Enter text to add to the file:\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    if (strlen(text) > 0) {
        fprintf(file, "%s\n", text);
        printf("Text added successfully.\n");
    } else {
        printf("No text entered, nothing added.\n");
    }
}

// Function to capitalize all letters in the file
void capitalize(FILE *file) {
    char ch;
    rewind(file); // Move file pointer to the beginning
    while ((ch = fgetc(file)) != EOF) {
        putchar(toupper(ch));
    }
    printf("\n");
}

// Function to convert all letters to lowercase
void lowercase(FILE *file) {
    char ch;
    rewind(file);
    while ((ch = fgetc(file)) != EOF) {
        putchar(tolower(ch));
    }
    printf("\n");
}

// Function to search for a word in the file
void search_word(FILE *file, const char *word) {
    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    int found = 0;
    rewind(file);
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, word)) {
            printf("Found \"%s\" at line %d: %s", word, line_number, line);
            found = 1;
        }
        line_number++;
    }
    if (found != 1) {
        printf("Word \"%s\" not found in the file.\n", word);
    }
}

// Function to count the frequency of a word in the file
void word_frequency(FILE *file, const char *word) {
    char line[MAX_LINE_LENGTH];
    int frequency = 0; 
    rewind(file);

    while (fgets(line, sizeof(line), file)) {
        for (char *ptr = line; (ptr = strstr(ptr, word)) != NULL; ptr++) {
            frequency++;
        }
    }

    printf("The word \"%s\" appears %d times in the file.\n", word, frequency);
}

// Function to count total number of words in the file
void word_count(FILE *file) {
    int count = 0;
    char ch;
    int in_word = 0;

    rewind(file);

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }

    printf("Total number of words in the file: %d\n", count);
}

// Function to convert a text file to a binary file (encryption)
void encrypt(const char *input_filename, const char *output_filename) {
    FILE *input_file, *output_file;
    char ch;
    
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Could not open the input file %s for reading.\n", input_filename);
        return;
    }

    // Open the output binary file in write mode
    output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        printf("Could not open the output file %s for writing.\n", output_filename);
        fclose(input_file);
        return;
    }

    while ((ch = fgetc(input_file)) != EOF) {
        fwrite(&ch, sizeof(char), 1, output_file);
    }

    printf("File %s has been encrypted and saved as %s\n", input_filename, output_filename);

    fclose(input_file);
    fclose(output_file);
}

// Function to view the contents of the opened file
void view(FILE *file) {
    char ch;
    rewind(file);

    printf("File contents:\n");

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    printf("\nEnd of file.\n");
}

// Function to auto-punctuate (capitalize the first letter after a period, question mark or an exclamation mark
void punctuate(FILE *file) {
    int ch;
    int capitalizeNext = 1;
    rewind(file);

    while ((ch = fgetc(file)) != EOF) {
        if (capitalizeNext && isalpha(ch)) {
            ch = toupper(ch);
            capitalizeNext = 0;
        }

        if (ch == '.' || ch == '?' || ch == '!') {
            capitalizeNext = 1;
        }
        fseek(file, -1, SEEK_CUR);
        fputc(ch, file);
    }
}

// Function that details the uses of the program to the user
void help() {
	puts("Welcome to FileInsight.");
	puts("This program allows you to open an already existing file or create a file with a name of your choosing.");
	puts("The functions at hand include capitalizing all text, or simple setting it all to lowercase.");
	puts("You can also search for a particular word, or see how many times it occurs in the document.");
	puts("The total word count is also available.");
	puts("You can also encrypt the document to binary code, making it unreadable to humans.");
	puts("Or you could simply view the contents of the opened file.");
	puts("You could also auto-punctuate text which simply capitalizes a sentences after a period (full stop).");
}

// Main function
int main() {
    FILE *file;
    char filename[MAX_LINE_LENGTH], word[MAX_LINE_LENGTH], bin_filename[MAX_LINE_LENGTH];
    int choice;
    char create_choice;

    welcome();

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open the file %s.\n", filename);
        printf("Do you wish to create a file %s? (Y/y for Yes, N/n for No): ", filename);
        
        getchar();
        scanf("%c", &create_choice);

        switch (create_choice) {
            case 'Y':
            case 'y':
                printf("Creating file: %s.\n", filename);
                file = fopen(filename, "w");
                if (file == NULL) {
                    printf("File could not be created.\n");
                    return 1;
                }
                printf("File created successfully.\n");
                break;
            case 'N':
            case 'n':
                printf("File creation cancelled.\n");
                return 1;
            default:
                printf("Please provide appropriate input.\n");
                return 1;
        }
    } else {
        printf("File opened successfully.\n");
    }

    do {
        printf("\nSelect an option:\n");
        printf("1. Add text\n");
        printf("2. Capitalize all letters\n");
        printf("3. Convert to lowercase\n");
        printf("4. Search for a word\n");
        printf("5. Word frequency\n");
        printf("6. Word count\n");
        printf("7. Encrypt file\n");
        printf("8. View contents\n");
        printf("NOTE: Please re-run the program to view contents of the file if any operations have previously been performed on it.\n");
        printf("9. Auto-punctuate\n");
        printf("10. Help menu\n");
        printf("11. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                file = fopen(filename, "a+");
                if (file == NULL) {
                    printf("Unable to open file to append.\n");
                    return 1;
                }
                printf("File opened successfully to append to.\n");
                add_text(file);
                fclose(file);
                break;
            case 2:
                capitalize(file);
                break;
            case 3:
                lowercase(file);
                break;
            case 4:
                printf("Enter the word to search: ");
                scanf("%s", word);
                search_word(file, word);
                break;
            case 5:
                printf("Enter the word to find frequency: ");
                scanf("%s", word);
                word_frequency(file, word);
                break;
            case 6:
                word_count(file);
                break;
            case 7:
                printf("Enter the name for the output encrypted (binary) file: ");
                scanf("%s", bin_filename);
                encrypt(filename, bin_filename);
                break;
            case 8:
                view(file);
                break;
            case 9:
                punctuate(file);
                break;
            case 10:
                help();
                break;
            case 11:
                printf("Exiting...\n");
                printf("\n");
                puts("Thank you for using FileInsight.");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 11);

    fclose(file);
    return 0;
}
