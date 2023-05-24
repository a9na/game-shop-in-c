#include <stdio.h>
#include <string.h>
#include "games.h"

void printMainMenu() {
    printf("Main Menu:\n");
    printf("1. Search by genre\n");
    printf("2. Exit\n");
}

void printGenreMenu() {
    printf("Genre Menu:\n");
    printf("0. Back\n");
    printf("1. Action-Adventure\n");
    printf("2. RPG\n");
    printf("3. FPS\n");
    printf("4. Puzzle\n");
    printf("5. Sports\n");
}

void printGameMenu() {
    printf("Game Menu:\n");
    printf("0. Back\n");
    printf("1. Add to Cart\n");
    printf("2. Add to Wishlist\n");
    printf("3. Purchase\n");
}

void searchByGenre(Game games[], int gameCount) {
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
    for (int i = 0; i < gameCount; i++) {
        if (strcmp(games[i].genre, genre) == 0) {
            printf("%d. %s\n", i + 1, games[i].title);
            gameFound = 1;
        }
    }

    if (!gameFound) {
        printf("No games found in the selected genre.\n");
    }
}

void initializeGames(Game games[], int* gameCount) {
    // Hard-coded game data for different genres
    Game actionAdventureGames[] = {
        { "Assassin's Creed", "Action-Adventure", 59.99 },
        { "Uncharted", "Action-Adventure", 49.99 },
        { "Batman: Arkham Asylum", "Action-Adventure", 39.99 }
    };

    Game rpgGames[] = {
        { "The Witcher 3: Wild Hunt", "RPG", 49.99 },
        { "Final Fantasy XV", "RPG", 59.99 },
        { "Skyrim", "RPG", 39.99 }
    };

    Game fpsGames[] = {
        { "Call of Duty: Modern Warfare", "FPS", 59.99 },
        { "Battlefield 1", "FPS", 49.99 },
        { "Overwatch", "FPS", 39.99 }
    };

    Game puzzleGames[] = {
        { "Portal", "Puzzle", 29.99 },
        { "Tetris", "Puzzle", 19.99 },
        { "Sudoku", "Puzzle", 9.99 }
    };

    Game sportsGames[] = {
        { "FIFA 21", "Sports", 49.99 },
        { "NBA 2K21", "Sports", 59.99 },
        { "Madden NFL 21", "Sports", 39.99 }
    };

    int genreChoice;
    printf("Enter the genre number: ");
    scanf("%d", &genreChoice);
    getchar(); // Consume newline character

    if (genreChoice == 0) {
        return;
    }
    else if (genreChoice < 1 || genreChoice > 5) {
        printf("Invalid genre choice. Please try again.\n");
        return;
    }

    switch (genreChoice) {
    case 1:
        *gameCount = sizeof(actionAdventureGames) / sizeof(actionAdventureGames[0]);
        memcpy(games, actionAdventureGames, sizeof(actionAdventureGames));
        break;
    case 2:
        *gameCount = sizeof(rpgGames) / sizeof(rpgGames[0]);
        memcpy(games, rpgGames, sizeof(rpgGames));
        break;
    case 3:
        *gameCount = sizeof(fpsGames) / sizeof(fpsGames[0]);
        memcpy(games, fpsGames, sizeof(fpsGames));
        break;
    case 4:
        *gameCount = sizeof(puzzleGames) / sizeof(puzzleGames[0]);
        memcpy(games, puzzleGames, sizeof(puzzleGames));
        break;
    case 5:
        *gameCount = sizeof(sportsGames) / sizeof(sportsGames[0]);
        memcpy(games, sportsGames, sizeof(sportsGames));
        break;
    }
}
