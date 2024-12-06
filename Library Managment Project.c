#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int serialNumber;
    char ISBN[20];
    char title[50];
    char edition[20];
    char author[50];
    int isReserved;
};

//Functions

void addBook(FILE *file) {
    struct Book book;

    printf("\nEnter Book Details:\n");
    printf("Serial Number: ");
    scanf("%d", &book.serialNumber);
    printf("ISBN: ");
    scanf("%s", book.ISBN);
    printf("Title: ");
    scanf(" %[^\n]", book.title);
    printf("Edition: ");
    scanf(" %[^\n]", book.edition);
    printf("Author: ");
    scanf(" %[^\n]", book.author);
    printf("Is Reserved (1 for Yes, 0 for No): ");
    scanf("%d", &book.isReserved);

    fprintf(file, "%d %s %s %s %s %d\n", book.serialNumber, book.ISBN, book.title, book.edition, book.author, book.isReserved);
    printf("Book added successfully!\n");
}

void deleteBook(FILE *file) {
    int serialNumber;
    int found = 0;
    FILE *tempFile = fopen("temp.txt", "w");

    printf("\nEnter the Serial Number of the book to delete: ");
    scanf("%d", &serialNumber);

    struct Book book;

    while (fscanf(file, "%d %s %[^\n] %[^\n] %[^\n] %d", &book.serialNumber, book.ISBN, book.title, book.edition, book.author, &book.isReserved) != EOF) {
        if (book.serialNumber != serialNumber) {
            fprintf(tempFile, "%d %s %s %s %s %d\n", book.serialNumber, book.ISBN, book.title, book.edition, book.author, book.isReserved);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("library_database.txt");
    rename("temp.txt", "library_database.txt");

    if (found) {
        printf("Book deleted successfully!\n");
    } else {
        printf("Book not found!\n");
    }
    file = fopen("library_database.txt", "a+");
}

void searchBookByISBN(FILE *file) {
    char searchISBN[20];
    int found = 0;
    printf("\nEnter ISBN to search: ");
    scanf("%s", searchISBN);
    struct Book book;

    while (fscanf(file, "%d %s %[^\n] %[^\n] %[^\n] %d", &book.serialNumber, book.ISBN, book.title, book.edition, book.author, &book.isReserved) != EOF) {
        if (strcmp(book.ISBN, searchISBN) == 0) {
            printf("\nBook Details:\n");
            printf("Serial Number: %d\n", book.serialNumber);
            printf("ISBN: %s\n", book.ISBN);
            printf("Title: %s\n", book.title);
            printf("Edition: %s\n", book.edition);
            printf("Author: %s\n", book.author);
            printf("Is Reserved: %d\n", book.isReserved);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

void searchBookByTitle(FILE *file) {
    char searchTitle[50];
    int found = 0;
    printf("\nEnter Book Title to search: ");
    scanf(" %[^\n]", searchTitle);
    struct Book book;

    while (fscanf(file, "%d %s %[^\n] %[^\n] %[^\n] %d", &book.serialNumber, book.ISBN, book.title, book.edition, book.author, &book.isReserved) != EOF) {
        if (strcmp(book.title, searchTitle) == 0) {
            printf("\nBook Details:\n");
            printf("Serial Number: %d\n", book.serialNumber);
            printf("ISBN: %s\n", book.ISBN);
            printf("Title: %s\n", book.title);
            printf("Edition: %s\n", book.edition);
            printf("Author: %s\n", book.author);
            printf("Is Reserved: %d\n", book.isReserved);
            found = 1;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

void searchBookByAuthor(FILE *file) {
    char searchAuthor[50];
    int found = 0;
    printf("\nEnter Author Name to search: ");
    scanf(" %[^\n]", searchAuthor);
    struct Book book;

    while (fscanf(file, "%d %s %[^\n] %[^\n] %[^\n] %d", &book.serialNumber, book.ISBN, book.title, book.edition, book.author, &book.isReserved) != EOF) {
        if (strcmp(book.author, searchAuthor) == 0) {
            printf("\nBook Details:\n");
            printf("Serial Number: %d\n", book.serialNumber);
            printf("ISBN: %s\n", book.ISBN);
            printf("Title: %s\n", book.title);
            printf("Edition: %s\n", book.edition);
            printf("Author: %s\n", book.author);
            printf("Is Reserved: %d\n", book.isReserved);
            found = 1;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

void modifyBook(FILE *file) {
    int serialNumber;
    int found = 0;
    printf("\nEnter the Serial Number of the book to modify: ");
    scanf("%d", &serialNumber);
    struct Book book;

    while (fscanf(file, "%d %s %[^\n] %[^\n] %[^\n] %d", &book.serialNumber, book.ISBN, book.title, book.edition, book.author, &book.isReserved) != EOF) {
        if (book.serialNumber == serialNumber) {
            found = 1;
            printf("\nEnter the new details for the book:\n");
            printf("ISBN: ");
            scanf("%s", book.ISBN);
            printf("Title: ");
            scanf(" %[^\n]", book.title);
            printf("Edition: ");
            scanf(" %[^\n]", book.edition);
            printf("Author: ");
            scanf(" %[^\n]", book.author);
            printf("Is Reserved (1 for Yes, 0 for No): ");
            scanf("%d", &book.isReserved);
        }
        fprintf(file, "%d %s %s %s %s %d\n", book.serialNumber, book.ISBN, book.title, book.edition, book.author, book.isReserved);
    }

    if (!found) {
        printf("Book not found!\n");
    } else {
        printf("Book modified successfully!\n");
    }
}

void displayAllBooks(FILE *file) {
    struct Book book;
    rewind(file);
    printf("\nAll Books in Library:\n");

    while (fscanf(file, "%d %s %[^\n] %[^\n] %[^\n] %d", &book.serialNumber, book.ISBN, book.title, book.edition, book.author, &book.isReserved) != EOF) {
        printf("\nBook Details:\n");
        printf("Serial Number: %d\n", book.serialNumber);
        printf("ISBN: %s\n", book.ISBN);
        printf("Title: %s\n", book.title);
        printf("Edition: %s\n", book.edition);
        printf("Author: %s\n", book.author);
        printf("Is Reserved: %d\n", book.isReserved);
    }
}

void issueBook(FILE *file) {
    int serialNumber;
    int found = 0;
    printf("\nEnter the Serial Number of the book to issue: ");
    scanf("%d", &serialNumber);
    struct Book book;

    while (fscanf(file, "%d %s %[^\n] %[^\n] %[^\n] %d", &book.serialNumber, book.ISBN, book.title, book.edition, book.author, &book.isReserved) != EOF) {
        if (book.serialNumber == serialNumber) {
            found = 1;
            if (book.isReserved == 0) {
                book.isReserved = 1;
                printf("Book issued successfully!\n");
            } else {
                printf("Book is already reserved!\n");
            }
        }
        fprintf(file, "%d %s %s %s %s %d\n", book.serialNumber, book.ISBN, book.title, book.edition, book.author, book.isReserved);
    }

    if (!found) {
        printf("Book not found!\n");
    }
}


int main() {
    FILE *file;
    file = fopen("library_database.txt", "a+");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Modify/Update a Book\n");
        printf("5. Display All Books\n");
        printf("6. Issue Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(file);
                break;
            case 2:
                deleteBook(file);
                break;
            case 3:
                printf("\nSearch By:\n");
                printf("a. ISBN\n");
                printf("b. Book Title\n");
                printf("c. Author Name\n");
                printf("Enter your choice: ");
                scanf(" %d", &choice);

                switch (choice) {
                    case 'a':
                        searchBookByISBN(file);
                        break;
                    case 'b':
                        searchBookByTitle(file);
                        break;
                    case 'c':
                        searchBookByAuthor(file);
                        break;
                    default:
                        printf("Invalid choice!\n");
                        break;
                }
                break;
            case 4:
                modifyBook(file);
                break;
            case 5:
                displayAllBooks(file);
                break;
            case 6:
                issueBook(file);
                break;
            case 7:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 7);

    fclose(file);
    return 0;
}

