#ifndef GAMES_H
#define GAMES_H

#define MAX_GAMES 15
#define MAX_TITLE_LENGTH 50

typedef enum {
	ACTION_ADVENTURE,
	RPG,
	FPS,
	PUZZLE,
	SPORTS
} Genre;

typedef struct {
	char title[MAX_TITLE_LENGTH];
	Genre genre;
	float price;
} Game;

typedef struct GameNode {
	Game data;
	struct GameNode* next;
} GameNode;

typedef struct {
	GameNode* head;
	int count;
} GameCollection;

void printMainMenu();
void printGenreMenu();
void printGameMenu();
void searchByGenre(GameCollection* collection);
void searchByTitle(GameCollection* collection);
void initializeGames(GameCollection* collection);
void saveGameToFile(Game game);
void sortGames(GameCollection* collection);
void renameGameFile(const char* oldName, const char* newName);

#endif // GAMES_H
