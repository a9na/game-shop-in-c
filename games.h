#ifndef GAMES_H
#define GAMES_H

#define MAX_GAMES 15

typedef struct {
	char title[50];
	char genre[50];
	float price;
} Game;

void printMainMenu();
void printGenreMenu();
void printGameMenu();
void searchByGenre(Game** games, int* gameCount);
void initializeGames(Game** games, int* gameCount);
void saveGameToFile(Game game);

#endif  // GAMES_H
