/*
Team Number: 
Team Name: 

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Message {
    char sender[50];
    char receiver[50];
    char content[256];
    struct Message* next;
} Message;

typedef struct MessageBox {
    Message* head;
} MessageBox;

void createMessageBox(MessageBox* box) {
    box->head = NULL;
}

void sendMessage(MessageBox* box, const char* sender, const char* receiver, const char* content) {
    Message* newMessage = (Message*)malloc(sizeof(Message));
    strcpy(newMessage->sender, sender);
    strcpy(newMessage->receiver, receiver);
    strcpy(newMessage->content, content);
    newMessage->next = NULL;

    newMessage->next = box->head;
    box->head = newMessage;
}

void displayMessages(const MessageBox* box) {
    if (box->head == NULL) {
        printf("\nYour message box is empty. No messages to display.\n");
    } else {
        printf("\nYour Messages:\n");
        Message* current = box->head;
        while (current != NULL) {
            printf("\tFrom: %s\n\tTo: %s\n\tMessage: %s\n\n", current->sender, current->receiver, current->content);
            current = current->next;
        }
        printf("\n");
    }
}

void sortMessages(MessageBox* box) {
    if (box->head == NULL || box->head->next == NULL) {
        printf("\nYou don't have enough messages to sort.\n");
        return;
    }

    int swapped;
    Message* last = NULL;

    do {
        swapped = 0;
        Message* current = box->head;
        Message* prev = NULL;

        while (current->next != last) {
            if (strcmp(current->sender, current->next->sender) > 0) {
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    box->head = current->next;
                }

                Message* temp = current->next;
                current->next = current->next->next;
                temp->next = current;

                current = temp;
                swapped = 1;
            }

            prev = current;
            current = current->next;
        }
        last = current;
    } while (swapped);

    printf("\nMessages sorted.\n");
}

void filterMessages(const MessageBox* box, const char* receiver) {
    if (box->head == NULL) {
        printf("\nYour message box is empty. No messages to filter.\n");
        return;
    }

    printf("\nMessages for %s\n", receiver);
    Message* current = box->head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->receiver, receiver) == 0) {
            printf("\tFrom: %s\n\tMessage: %s\n\n", current->sender, current->content);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No messages found for %s.\n", receiver);
    }

    printf("\n");
}

void searchMessages(const MessageBox* box, const char* keyword) {
    if (box->head == NULL) {
        printf("\nYour message box is empty. No messages to search.\n");
        return;
    }

    printf("\nSearch Results for \"%s\"\n", keyword);
    Message* current = box->head;
    int found = 0;
    while (current != NULL) {
        if (strstr(current->content, keyword) != NULL) {
            printf("\tFrom: %s\n\tTo: %s\n\tMessage: %s\n\n", current->sender, current->receiver, current->content);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No messages found containing \"%s\".\n", keyword);
    }

    printf("\n");
}

void deleteMessage(MessageBox* box, const char* sender, const char* receiver, const char* content) {
    if (box->head == NULL) {
        printf("\nYour message box is empty. No messages to delete.\n");
        return;
    }

    Message* current = box->head;
    Message* prev = NULL;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->sender, sender) == 0 &&
            strcmp(current->receiver, receiver) == 0 &&
            strcmp(current->content, content) == 0) {
            
            if (prev == NULL) {
                box->head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            found = 1;
            printf("Message deleted successfully.\n");
            break;
        }

        prev = current;
        current = current->next;
    }

    if (!found) {
        printf("No matching message found to delete.\n");
    }
}

void cleanupMessageBox(MessageBox* box) {
    Message* current = box->head;
    while (current != NULL) {
        Message* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    MessageBox messageBox;
    createMessageBox(&messageBox);

    int choice;
    char sender[50], receiver[50], content[256], keyword[50];

    printf("Welcome to Your Message Box!\n");

    do {
        printf("\nHow can I assist you today?\n");
        printf("1. Send a Message\n");
        printf("2. View Messages\n");
        printf("3. Sort Messages\n");
        printf("4. Filter Messages by Receiver\n");
        printf("5. Search Messages by Keyword\n");
        printf("6. Delete a Message\n");
        printf("7. Quit\n");

        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("I'm sorry, I didn't understand that. Please enter a number.\n");
            scanf("%*s");
            continue;
        }

        switch (choice) {
            case 1:
                printf("\nSure thing! Let's send a message.\n");
                printf("Your name: ");
                scanf("%s", sender);
                printf("Recipient's name: ");
                scanf("%s", receiver);
                printf("Your message: ");
                getchar();
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                sendMessage(&messageBox, sender, receiver, content);
                printf("Message sent!\n");
                break;

            case 2:
                displayMessages(&messageBox);
                break;

            case 3:
                sortMessages(&messageBox);
                break;

            case 4:
                printf("\nWhich recipient's messages would you like to see?\nRecipient's name: ");
                scanf("%s", receiver);
                filterMessages(&messageBox, receiver);
                break;

            case 5:
                printf("\nWhat keyword are you searching for in the messages?\nKeyword: ");
                scanf("%s", keyword);
                searchMessages(&messageBox, keyword);
                break;

            case 6:
                printf("\nLet's delete a message.\n");
                printf("Enter sender's name: ");
                scanf("%s", sender);
                printf("Enter receiver's name: ");
                scanf("%s", receiver);
                printf("Enter message content: ");
                getchar();
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                deleteMessage(&messageBox, sender, receiver, content);
                break;
            
            case 7:
                printf("\nThank you for using Your Message Box. Have a wonderful day!\n");
                break;

            default:
                printf("I'm sorry, I didn't understand that. Please choose a valid option.\n");
        }
    } while (choice != 7);

    cleanupMessageBox(&messageBox);

    return 0;
}