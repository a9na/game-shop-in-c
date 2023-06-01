#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "games.h"


int main() {
	GameCollection collection;
	initializeGames(&collection);

	int choice;
	do {
		printMainMenu();     // 4
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		switch (choice) {
		case 1:
			searchByGenre(&collection);
			break;
		case 2:
			searchByTitleBinary(&collection);
			break;
		case 3:
			printf("Exiting the program. Goodbye!\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 3);

	freeGames(&collection);   
	return 0;
}
