#include <stdio.h>
#include "games.h"

int main() {
    Game games[MAX_GAMES];
    int gameCount = 0;

    // Hard-coded game names
    initializeGames(games, &gameCount);

    // Display the main menu
    int choice = 0;
    while (choice != 2) {
        printMainMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
        case 1:
            searchByGenre(games, gameCount);
            break;
        case 2:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}
