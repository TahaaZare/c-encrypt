#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h> // For Sleep() on Windows
#else
#include <unistd.h> // For sleep() on Unix-like systems
#endif

// Function for Caesar Cipher encryption
void caesar_cipher(char *message, int shift) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        if (isalpha(message[i])) {
            char base = (isupper(message[i])) ? 'A' : 'a';
            message[i] = (message[i] - base + shift) % 26 + base;
        }
    }
}

// Function for XOR Cipher encryption
void xor_cipher(char *message, char key) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        message[i] = message[i] ^ key;
    }
}

// Function to copy text to clipboard
void copy_to_clipboard(const char *text) {
#if defined(_WIN32) || defined(_WIN64)
    FILE *clipboard = _popen("clip", "w");
    if (clipboard) {
        fputs(text, clipboard);
        _pclose(clipboard);
        printf("Encrypted message copied to clipboard.\n");
    } else {
        printf("Failed to copy to clipboard.\n");
    }
#elif defined(__APPLE__) || defined(__MACH__)
    FILE *clipboard = popen("pbcopy", "w");
    if (clipboard) {
        fputs(text, clipboard);
        pclose(clipboard);
        printf("Encrypted message copied to clipboard.\n");
    } else {
        printf("Failed to copy to clipboard.\n");
    }
#elif defined(__linux__)
    FILE *clipboard = popen("xclip -selection clipboard", "w");
    if (!clipboard) {
        clipboard = popen("xsel --clipboard --input", "w");
    }
    if (clipboard) {
        fputs(text, clipboard);
        pclose(clipboard);
        printf("Encrypted message copied to clipboard.\n");
    } else {
        printf("Failed to copy to clipboard. Ensure xclip or xsel is installed.\n");
    }
#else
    printf("Clipboard functionality not supported on this OS.\n");
#endif
}

// Encryption function
void encrypt() {
    char *message = NULL;
    size_t buffer_size = 0;
    int choice;
    int shift = 3; // Shift for Caesar cipher
    char xor_key = 'K'; // Key for XOR cipher

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__linux__)
    system("clear");
#endif

START:
    printf("Please choose an encryption algorithm:\n");
    printf("1. Caesar Cipher\n");
    printf("2. XOR Cipher\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Consume newline character
    getchar();

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__linux__)
    system("clear");
#endif

    printf("Please enter your message:\n");

#if defined(_WIN32) || defined(_WIN64)
    message = (char *)malloc(1024 * sizeof(char));
    if (fgets(message, 1024, stdin) == NULL) {
        printf("Error reading input.\n");
        free(message);
        return;
    }
#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__linux__)
    ssize_t length = getline(&message, &buffer_size, stdin);
    if (length == -1) {
        printf("Error reading input.\n");
        free(message);
        return;
    }
#else
    printf("Unsupported OS.\n");
    return;
#endif

    ssize_t length = strlen(message);
    if (message[length - 1] == '\n') {
        message[length - 1] = '\0';
    }

    if (choice == 1) {
        caesar_cipher(message, shift);
    } else if (choice == 2) {
        xor_cipher(message, xor_key);
    } else {
        printf("Invalid choice. Try again.\n");
        free(message);
        goto START;
    }

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__linux__)
    system("clear");
#endif

    printf("Encrypted message: %s\n", message);
    copy_to_clipboard(message);
    free(message);

    // Wait for 3 seconds
#if defined(_WIN32) || defined(_WIN64)
    Sleep(3000); // Sleep takes milliseconds on Windows
#else
    sleep(3); // Sleep takes seconds on Unix-like systems
#endif
}

int main(void) {
    int command;

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
    system("color 0a");
#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__linux__)
    system("clear");
#endif

    while (1) {
        printf("CHOOSE ONE OF THESE:\n");
        printf("1: Encrypt\n");
        printf("2: Decrypt (Not implemented yet)\n");
        printf("0: EXIT\n");
        scanf("%d", &command);

        switch (command) {
            case 1:
                encrypt();
                break;
            case 2:
                printf("Decrypt functionality is not implemented yet.\n");
                break;
            case 0:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid option. Try again.\n");
        }

#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__linux__)
        system("clear");
#endif
    }

    return 0;
}
