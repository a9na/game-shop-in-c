#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "games.h"

static void printMainMenu() {
    printf("Main Menu:\n");
    printf("1. Search by genre\n");
    printf("2. Exit\n");
}

static void printGenreMenu() {
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

int compareGames(const void* a, const void* b) {
    Game* gameA = (Game*)a;
    Game* gameB = (Game*)b;
    return strcmp(gameA->title, gameB->title);
}

void sortGames(Game** games, int gameCount) {
    qsort(*games, gameCount, sizeof(Game), compareGames);
}

void renameGameFile(const char* oldName, const char* newName) {
    int status = rename(oldName, newName);
    if (status == 0) {
        printf("File '%s' renamed to '%s'.\n", oldName, newName);
    } else {
        printf("Error renaming file '%s' to '%s'.\n", oldName, newName);
    }
}

void searchByGenre(Game** games, int* gameCount) {
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

    char genre[50];
    switch (genreChoice) {
    case 1:
        strcpy(genre, "Action-Adventure");
        break;
    case 2:
        strcpy(genre, "RPG");
        break;
    case 3:
        strcpy(genre, "FPS");
        break;
    case 4:
        strcpy(genre, "Puzzle");
        break;
    case 5:
        strcpy(genre, "Sports");
        break;
    }

    printf("Games in the genre \"%s\":\n", genre);

    int gameFound = 0;
    for (int i = 0; i < *gameCount; i++) {
        if (strcmp((*games)[i].genre, genre) == 0) {
            printf("%d. %s\n", i + 1, (*games)[i].title);
            gameFound = 1;
        }
    }

    if (!gameFound) {
        printf("No games found in the selected genre.\n");
        return;
    }

    int gameChoice;
    printf("Enter the game number to view options: ");
    scanf("%d", &gameChoice);
    getchar();

    if (gameChoice < 1 || gameChoice > *gameCount) {
        printf("Invalid game choice. Please try again.\n");
        return;
    }

    Game selectedGame = (*games)[gameChoice - 1];
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
    
 sortGames(games, *gameCount);
 renameGameFile("games.txt", "games_new.txt");
}

void initializeGames(Game** games, int* gameCount) {
    *gameCount = MAX_GAMES;

    *games = (Game*)malloc(sizeof(Game) * (*gameCount));
    if (*games == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    static Game allGames[MAX_GAMES] = {
        { "Assassin's Creed", "Action-Adventure", 59.99f },
        { "Uncharted", "Action-Adventure", 49.99f },
        { "Batman: Arkham Asylum", "Action-Adventure", 39.99f },
        { "The Witcher 3: Wild Hunt", "RPG", 49.99f },
        { "Final Fantasy XV", "RPG", 59.99f },
        { "Skyrim", "RPG", 39.99f },
        { "Call of Duty: Modern Warfare", "FPS", 59.99f },
        { "Battlefield 1", "FPS", 49.99f },
        { "Overwatch", "FPS", 39.99f },
        { "Portal", "Puzzle", 29.99f },
        { "Tetris", "Puzzle", 19.99f },
        { "Sudoku", "Puzzle", 9.99f },
        { "FIFA 21", "Sports", 49.99f },
        { "NBA 2K21", "Sports", 59.99f },
        { "Madden NFL 21", "Sports", 39.99f }
    };

    memcpy(*games, allGames, sizeof(Game) * (*gameCount));
}

static void saveGameToFile(Game game) {
    FILE* file = fopen("games.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);  
    long fileSize = ftell(file);    

    printf("Size of the file: %ld bytes\n", fileSize);
    
    rewind(file);
    
    fprintf(file, "Title: %s\n", game.title);
    fprintf(file, "Genre: %s\n", game.genre);
    fprintf(file, "Price: $%.2f\n\n", game.price);

    fclose(file);
}
