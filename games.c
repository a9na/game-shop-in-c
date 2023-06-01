#define _CRT_SECURE_NO_WARNINGS

//1 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "games.h"
#include <ctype.h>

// 8

void printMainMenu() {
	printf("Main Menu:\n");
	printf("1. Search by genre\n");
	printf("2. Search by title\n");
	printf("3. Exit\n");
}

static void printGenreMenu() {      // 5
	printf("Genre Menu:\n");
	printf("0. Back\n");
	printf("1. Action-Adventure\n");
	printf("2. RPG\n");
	printf("3. FPS\n");
	printf("4. Puzzle\n");
	printf("5. Sports\n");
}

static void printGameMenu() {
	printf("Game Menu:\n");
	printf("0. Back\n");
	printf("1. Add to Cart\n");
	printf("2. Add to Wishlist\n");
	printf("3. Purchase\n");
}

// 9  10  11   12

int compareGames(const void* a, const void* b) {
	Game* gameA = (Game*)a;
	Game* gameB = (Game*)b;
	return strcmp(gameA->title, gameB->title);
}

void sortGames(GameCollection* collection) {
	GameNode* games = collection->head;
	int gameCount = collection->count;
	Game* gameArray = (Game*)malloc(sizeof(Game) * gameCount);   // 13 14   
	if (gameArray == NULL) {
		printf("Memory allocation failed.\n");
		return;
	}

	for (int i = 0; i < gameCount; i++) {
		gameArray[i] = games->data;
		games = games->next;
	}

	qsort(gameArray, gameCount, sizeof(Game), compareGames);   //20

	games = collection->head;
	for (int i = 0; i < gameCount; i++) {
		games->data = gameArray[i];
		games = games->next;
	}

	free(gameArray);   // 15
}

void renameGameFile(const char* oldName, const char* newName) {
	int status = rename(oldName, newName);    //18
	if (status == 0) {
		printf("File '%s' renamed to '%s'.\n", oldName, newName);
	}
	else {
		printf("Error renaming file '%s' to '%s': %s\n", oldName, newName, strerror(errno));
	}
}
// 16 17 19
void saveGameToFile(Game game) {
	FILE* file = fopen("games.txt", "a");
	if (file == NULL) {
		printf("Error opening file for saving game: %s\n", strerror(errno));
		return;
	}

	if (fseek(file, 0, SEEK_END) != 0) {
		printf("Error seeking to the end of the file: %s\n", strerror(errno));
		fclose(file);
		return;
	}

	long fileSize = ftell(file);
	if (fileSize == -1) {
		printf("Error getting file position: %s\n", strerror(errno));
		fclose(file);
		return;
	}

	fprintf(file, "Title: %s\n", game.title);
	fprintf(file, "Genre: %d\n", game.genre);
	fprintf(file, "Price: %.2f\n\n", game.price);

	fclose(file);
}


void searchByGenre(GameCollection* collection) {
	printGenreMenu();

	int genreChoice;
	printf("Enter the genre number: ");
	scanf("%d", &genreChoice);
	getchar();

	if (genreChoice == 0) {
		return;
	}
	else if (genreChoice < 1 || genreChoice > 5) {
		printf("Invalid genre choice. Please try again.\n");
		return;
	}

	Genre genre;
	switch (genreChoice) {
	case 1:
		genre = ACTION_ADVENTURE;
		break;
	case 2:
		genre = RPG;
		break;
	case 3:
		genre = FPS;
		break;
	case 4:
		genre = PUZZLE;
		break;
	case 5:
		genre = SPORTS;
		break;
	}

	printf("Games in the selected genre:\n");

	GameNode* games = collection->head;
	int gameFound = 0;
	for (int i = 0; i < collection->count; i++) {
		if (games->data.genre == genre) {
			printf("%d. %s\n", i + 1, games->data.title);
			gameFound = 1;
		}
		games = games->next;
	}

	if (!gameFound) {
		printf("No games found in the selected genre.\n");
		return;
	}

	int gameChoice;
	printf("Enter the game number to view options: ");
	scanf("%d", &gameChoice);
	getchar();

	if (gameChoice < 1 || gameChoice > collection->count) {
		printf("Invalid game choice. Please try again.\n");
		return;
	}

	games = collection->head;
	for (int i = 0; i < gameChoice - 1; i++) {
		games = games->next;
	}

	Game selectedGame = games->data;
	printf("Selected game: %s\n", selectedGame.title);
	printGameMenu();

	int menuChoice;
	printf("Enter your choice: ");
	scanf("%d", &menuChoice);
	getchar();

	switch (menuChoice) {
	case 0:
		break;
	case 1:
		printf("Added \"%s\" to the cart.\n", selectedGame.title);
		break;
	case 2:
		printf("Added \"%s\" to the wishlist.\n", selectedGame.title);
		break;
	case 3:
		saveGameToFile(selectedGame);
		printf("Purchased \"%s\". The game has been saved to games.txt.\n", selectedGame.title);
		break;
	default:
		printf("Invalid choice. Please try again.\n");
		break;
	}

	sortGames(collection);
	renameGameFile("games.txt", "games_new.txt");
}
void searchByTitleBinary(GameCollection* collection) {
	char searchTitle[MAX_TITLE_LENGTH];
	printf("Enter the game title: ");
	fgets(searchTitle, sizeof(searchTitle), stdin);
	searchTitle[strcspn(searchTitle, "\n")] = '\0';

	Game key;
	strcpy(key.title, searchTitle);

	GameNode* games = collection->head;
	size_t gameCount = collection->count;

	sortGames(collection);

	Game* result = (Game*)bsearch(&key, games, gameCount, sizeof(Game), compareGames);    //21
	if (result != NULL) {
		printf("Game found: %s\n", result->title);
		printGameMenu();

		int menuChoice;
		printf("Enter your choice: ");
		scanf("%d", &menuChoice);
		getchar();

		switch (menuChoice) {
		case 0:
			break;
		case 1:
			printf("Added \"%s\" to the cart.\n", result->title);
			break;
		case 2:
			printf("Added \"%s\" to the wishlist.\n", result->title);
			break;
		case 3:
			saveGameToFile(*result);
			printf("Purchased \"%s\". The game has been saved to games.txt.\n", result->title);
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	}
	else {
		printf("Game not found.\n");
	}
}

// 4
void initializeGames(GameCollection* collection) {
	collection->count = MAX_GAMES;
	collection->head = NULL;
	GameNode* tail = NULL;

	static Game allGames[MAX_GAMES] = {
		{ "Assassin's Creed", ACTION_ADVENTURE, 59.99f },
		{ "Uncharted", ACTION_ADVENTURE, 49.99f },
		{ "Batman: Arkham Asylum", ACTION_ADVENTURE, 39.99f },
		{ "The Witcher 3", RPG, 69.99f },
		{ "Final Fantasy VII Remake", RPG, 59.99f },
		{ "Fallout 4", RPG, 49.99f },
		{ "Call of Duty", FPS, 59.99f },
		{ "Battlefield 1", FPS, 49.99f },
		{ "DOOM", FPS, 39.99f },
		{ "Portal", PUZZLE, 29.99f },
		{ "Tetris", PUZZLE, 19.99f },
		{ "Sudoku", PUZZLE, 9.99f },
		{ "FIFA", SPORTS, 49.99f },
		{ "NBA 2K", SPORTS, 39.99f },
		{ "Madden NFL", SPORTS, 29.99f }
	};

	for (int i = 0; i < MAX_GAMES; i++) {
		GameNode* newNode = (GameNode*)malloc(sizeof(GameNode));
		newNode->data = allGames[i];
		newNode->next = NULL;

		if (collection->head == NULL) {
			collection->head = newNode;
		}
		else {
			tail->next = newNode;
		}

		tail = newNode;
	}
}

void freeGames(GameCollection* collection) {
	GameNode* games = collection->head;
	while (games != NULL) {
		GameNode* current = games;
		games = games->next;
		free(current);   
	}
	collection->count = 0;
	collection->head = NULL;
}
