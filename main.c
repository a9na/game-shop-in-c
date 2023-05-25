#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "games.h"

int main() {
	Game* games = NULL;
	int gameCount = 0;

	initializeGames(&games, &gameCount);

	int choice = 0;
	while (choice != 2) {
		printMainMenu();

		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		switch (choice) {
		case 1:
			searchByGenre(&games, &gameCount);
			break;
		case 2:
			printf("Exiting the program.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	}

	free(games);
	games = NULL;

	return 0;
}
