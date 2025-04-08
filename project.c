#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *fileMatches;
FILE *filePlayers;
FILE *fileMatchReader;
int matchCount = 0;

struct Game {
    char p1[50];
    char p2[50];
    char s1[50];
    char s2[50];
};

int count_matches() {
    fileMatchReader = fopen("matches", "r");
    if (!fileMatchReader) {
        perror("Unable to open matches file");
        return 0;
    }

    int lines = 0;
    char line[256];
    while (fgets(line, sizeof(line), fileMatchReader)) {
        lines++;
    }

    fclose(fileMatchReader);
    return lines;
}

void show_menu() {
    system("cls");
    printf("======Table Tennis Results======\n");
    printf("=========== MENU ===============\n");
    printf("1. Enter Players\n");
    printf("2. Show Rankings\n");
    printf("3. View Match History\n");
    printf("================================\n");
    printf("0. Exit Application\n");
}

void insert_matches() {
    matchCount = count_matches();
    filePlayers = fopen("players", "a");
    fileMatches = fopen("matches", "a");

    struct Game g;
    system("cls");
    int total;
    printf("How many matches to record? ");
    scanf("%d", &total);

    for (int i = 0; i < total; i++) {
        printf("\n--- Match #%d ---\n", i + 1);

        printf("Player 1 Name: ");
        scanf("%s", g.p1);

        printf("Player 1 Score: ");
        while (1) {
            scanf("%s", g.s1);
            if (strspn(g.s1, "0123456789") == strlen(g.s1)) {
                int sc = atoi(g.s1);
                if (sc >= 0 && sc <= 21) break;
                else {
                    printf("Score must be 0 to 21. Try again: ");
                }
            } else {
                printf("Invalid input! Use digits only: ");
            }
        }

        printf("Player 2 Name: ");
        scanf("%s", g.p2);

        printf("Player 2 Score: ");
        while (1) {
            scanf("%s", g.s2);
            if (strspn(g.s2, "0123456789") == strlen(g.s2)) {
                int sc = atoi(g.s2);
                if (sc >= 0 && sc <= 21) break;
                else {
                    printf("Score must be 0 to 21. Try again: ");
                }
            } else {
                printf("Invalid input! Use digits only: ");
            }
        }

        fprintf(fileMatches, "%d. [%s] %s / %s [%s]\n", matchCount, g.p1, g.s1, g.s2, g.p2);
        fprintf(filePlayers, "%s\n", g.p1);
        fprintf(filePlayers, "%s\n", g.p2);
        matchCount++;
    }

    fclose(filePlayers);
    fclose(fileMatches);

    int choice;
    while (1) {
        system("cls");
        printf("================================\n");
        printf("1. Add More Matches\n");
        printf("9. Return to Main Menu\n");
        printf("================================\n");
        scanf("%d", &choice);

        if (choice == 1) {
            insert_matches();
            break;
        } else if (choice == 9) {
            system("cls");
            show_menu();
            return;
        }
    }
}

void display_ranking() {
    filePlayers = fopen("players", "r");
    if (!filePlayers) {
        printf("Player file not found.\n");
        return;
    }

    char nameLine[256];
    system("cls");
    printf("======= Player Rankings =======\n");
    printf("===[Name] [WINS]/[LOSSES]======\n\n");

    while (fgets(nameLine, sizeof(nameLine), filePlayers)) {
        printf("%s", nameLine);
    }

    fclose(filePlayers);
    printf("\n");

    int input;
    while (1) {
        printf("Press 9 to return to Main Menu: ");
        scanf("%d", &input);
        if (input == 9) {
            system("cls");
            show_menu();
            return;
        }
    }
}

void view_history() {
    fileMatches = fopen("matches", "r");
    if (!fileMatches) {
        printf("No match history available.\n");
        return;
    }

    char record[256];
    system("cls");
    printf("======= Match History =======\n\n");

    while (fgets(record, sizeof(record), fileMatches)) {
        printf("%s", record);
    }

    fclose(fileMatches);
    printf("\n");

    int input;
    while (1) {
        printf("Press 9 to return to Main Menu: ");
        scanf("%d", &input);
        if (input == 9) {
            system("cls");
            show_menu();
            return;
        }
    }
}

void exit_program() {
    system("cls");
    printf("Program terminated. Goodbye!\n");
}

int main() {
    fopen("matches", "r");
    fclose(fileMatches);

    int menuOptions[] = {1, 2, 3};
    int userChoice = -1;

    show_menu();

    while (userChoice != 0) {
        scanf("%d", &userChoice);

        if (userChoice == menuOptions[userChoice - 1] || userChoice == 9) {
            switch (userChoice) {
                case 1:
                    insert_matches();
                    break;
                case 2:
                    display_ranking();
                    break;
                case 3:
                    view_history();
                    break;
                case 9:
                    system("cls");
                    show_menu();
                    break;
            }
        } else if (userChoice == 0) {
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    exit_program();
    return 0;
}
