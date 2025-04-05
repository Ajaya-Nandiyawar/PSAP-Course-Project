#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

// Function prototypes
void caesarEncrypt(char *text, int shift);
void caesarDecrypt(char *text, int shift);
void toLowerCase(char *str);
void processFile(const char *inputFile, const char *outputFile, void (*cipherFunction)(char *, int), int shift);

// Caesar Cipher encryption
void caesarEncrypt(char *text, int shift)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (char)((text[i] - base + shift) % 26 + base);
        }
    }
}

// Caesar Cipher decryption
void caesarDecrypt(char *text, int shift)
{
    caesarEncrypt(text, 26 - (shift % 26)); // Decryption is encryption with reverse shift
}

// Convert string to lowercase
void toLowerCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// Process file for Caesar cipher
void processFile(const char *inputFile, const char *outputFile, void (*cipherFunction)(char *, int), int shift)
{
    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");

    if (!fin || !fout)
    {
        perror("Error opening file");
        return;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, fin))
    {
        cipherFunction(buffer, shift);
        fputs(buffer, fout);
    }

    fclose(fin);
    fclose(fout);
    printf("File processed successfully. Output written to %s\n", outputFile);
}

int main()
{
    char inputFile[MAX_LENGTH], outputFile[MAX_LENGTH];
    int choice, shift;

    while (1)
    {
        printf("\nCryptography Menu:\n");
        printf("1. Caesar Cipher Encryption (File)\n");
        printf("2. Caesar Cipher Decryption (File)\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 3)
        {
            printf("Exiting program.\n");
            break;
        }

        printf("Enter input file path: ");
        fgets(inputFile, MAX_LENGTH, stdin);
        inputFile[strcspn(inputFile, "\n")] = 0; // Remove newline

        printf("Enter output file path: ");
        fgets(outputFile, MAX_LENGTH, stdin);
        outputFile[strcspn(outputFile, "\n")] = 0; // Remove newline

        switch (choice)
        {
        case 1:
            printf("Enter shift value (0-25): ");
            scanf("%d", &shift);
            processFile(inputFile, outputFile, caesarEncrypt, shift);
            break;

        case 2:
            printf("Enter shift value (0-25): ");
            scanf("%d", &shift);
            processFile(inputFile, outputFile, caesarDecrypt, shift);
            break;

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
