#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h> // For Sleep() on Windows
#else
#include <unistd.h> // For sleep() on Unix-like systems
#endif

// Function prototypes
void caesar_cipher(char *message, int shift);

void xor_cipher(char *message, char key);

void caesar_cipher_decrypt(char *message, int shift);

void xor_cipher_decrypt(char *message, char key);

void copy_to_clipboard(const char *text);

void encrypt();

void decrypt();

void caesar_cipher(char *message, int shift) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        if (isalpha(message[i])) {
            char base = (isupper(message[i])) ? 'A' : 'a';
            message[i] = (message[i] - base + shift) % 26 + base;
        }
    }
}

void xor_cipher(char *message, char key) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        message[i] ^= key;
    }
}

void caesar_cipher_decrypt(char *message, int shift) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        if (isalpha(message[i])) {
            char base = (isupper(message[i])) ? 'A' : 'a';
            message[i] = (message[i] - base - shift + 26) % 26 + base;
        }
    }
}

void xor_cipher_decrypt(char *message, char key) {
    xor_cipher(message, key); // XOR decryption is symmetric
}

void encrypt() {
    char *message = NULL;
    size_t buffer_size = 0;
    int choice;
    int shift = 3; // Shift for Caesar cipher
    char xor_key = 'K'; // Key for XOR cipher

#if defined(_WIN32) || defined(_WIN64)
    system("color 0a");
    system("cls");
#else
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
    system("color 0c");
    system("cls");
#else
    system("clear");
#endif

    printf("Please enter your message to encrypt:\n");

#if defined(_WIN32) || defined(_WIN64)
    message = (char *) malloc(1024 * sizeof(char));
    if (fgets(message, 1024, stdin) == NULL) {
        printf("Error reading input.\n");
        free(message);
        return;
    }
#else
    ssize_t length = getline(&message, &buffer_size, stdin);
    if (length == -1) {
        printf("Error reading input.\n");
        free(message);
        return;
    }
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
    system("color 0c");
    system("cls");
#else
    system("clear");
#endif

    printf("Encrypted message: %s\n", message);
    copy_to_clipboard(message);
    free(message);

#if defined(_WIN32) || defined(_WIN64)
    Sleep(3000);
#else
    sleep(3);
#endif
}

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

void copy_to_clipboard(const char *text) {
    const size_t length = strlen(text) + 1; // Include null terminator
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, length);
    if (hMem == NULL) {
        printf("Failed to allocate memory for clipboard.\n");
        return;
    }

    memcpy(GlobalLock(hMem), text, length);
    GlobalUnlock(hMem);

    if (!OpenClipboard(NULL)) {
        printf("Failed to open clipboard.\n");
        GlobalFree(hMem);
        return;
    }

    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();

    printf("Text copied to clipboard!\n");
}
#else
#include <stdio.h>
#include <stdlib.h>
void copy_to_clipboard(const char *text) {
    // Use the `xclip` command on Unix-like systems
    FILE *clipboard = popen("xclip -selection clipboard", "w");
    if (clipboard == NULL) {
        printf("Failed to access clipboard.\n");
        return;
    }

    fprintf(clipboard, "%s", text);
    pclose(clipboard);

    printf("Text copied to clipboard!\n");
}
#endif


void decrypt() {
    char *message = NULL;
    size_t buffer_size = 0;
    int choice;
    int shift = 3; // Shift for Caesar cipher
    char xor_key = 'K'; // Key for XOR cipher

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
    system("color 0a");
#else
    system("clear");
#endif

START:
    printf("Please choose a decryption algorithm:\n");
    printf("1. Caesar Cipher\n");
    printf("2. XOR Cipher\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Consume newline character
    getchar();

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif

    printf("Please enter your encrypted message:\n");

#if defined(_WIN32) || defined(_WIN64)
    message = (char *) malloc(1024 * sizeof(char));
    if (fgets(message, 1024, stdin) == NULL) {
        printf("Error reading input.\n");
        free(message);
        return;
    }
#else
    ssize_t length = getline(&message, &buffer_size, stdin);
    if (length == -1) {
        printf("Error reading input.\n");
        free(message);
        return;
    }
#endif

    ssize_t length = strlen(message);
    if (message[length - 1] == '\n') {
        message[length - 1] = '\0';
    }

    if (choice == 1) {
        caesar_cipher_decrypt(message, shift);
    } else if (choice == 2) {
        xor_cipher_decrypt(message, xor_key);
    } else {
        printf("Invalid choice. Try again.\n");
        free(message);
        goto START;
    }

#if defined(_WIN32) || defined(_WIN64)
    system("color 0c");
    system("cls");
#else
    system("clear");
#endif

    printf("Decrypted message: %s\n", message);
    copy_to_clipboard(message);
    free(message);

#if defined(_WIN32) || defined(_WIN64)
    Sleep(3000);
#else
    sleep(3);
#endif
}

int main(void) {
    int command;

#if defined(_WIN32) || defined(_WIN64)
    system("color 0a");
    system("cls");
#else
    system("clear");
#endif

    while (1) {
        printf("CHOOSE ONE OF THESE:\n");
        printf("1: Encrypt\n");
        printf("2: Decrypt\n");
        printf("0: EXIT\n");
        scanf("%d", &command);

        switch (command) {
            case 1:
                encrypt();
                break;
            case 2:
                decrypt();
                break;
            case 0:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid option. Try again.\n");
        }

#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
    }

    return 0;
}
