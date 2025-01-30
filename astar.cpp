#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <math.h>
#include <limits.h>
#include <windows.h>

using namespace std;

const char startCharacter = 'S';
const char destinationCharacter = 'C';
const char wallCharacter = '#';
const char visitedCharacter = '.';
const char pathCharacter = 'O';

const int directionX[] = {1, -1, 0, 0};
const int directionY[] = {0, 0, 1, -1};
const int directionAmount = 4;

const int mapHeight = 21;
const char map[][100] = {
    "###############################",
    "#        #     #  #     #     #",
    "#######  #  ####  #  #######  #",
    "#           #                 #",
    "#  #######  #  ####  ##########",
    "#        #     #           #  #",
    "#######  #  #############  #  #",
    "#     #  #        #     #     #",
    "#  #######  ####  #  #  #  #  #",
    "#           #  S  #  #     #  #",
    "#  #  #######  #  ####  #######",
    "#  #  #        #  #        #  #",
    "#  ####  #  #  # #####  ####  #",
    "#  #  #  #  #  #        #     #",
    "#  #  ##########  ####  ####  #",
    "#  #           #  #  #        #",
    "#  ####  ##########  #  #  #  #",
    "#              #  #  #  #  #  #",
    "#  #######  #  #  #  ####  ####",
    "#     #     #     #          C#",
    "###############################"
	};


struct Position{
	int x;
	int y;
};

struct Tile{
	Position position;
	char ch;
	int distance;
	bool isVisit;
	Tile *before;
};



Tile *createTile(Position position, char ch){
	Tile *tile = (Tile *)malloc(sizeof(Tile));
	tile->ch = ch;
	tile->position = position;
	tile->distance = INT_MAX;
	tile->isVisit = false;
	tile->before = NULL;
	return tile;
}

vector<vector<Tile *> > tiles;
Tile *startingTile = NULL, *destination = NULL;

void printMap(){
	Sleep(100);
	system("cls");

	const int mapWidth = strlen(map[0]);
	for(int i = 0 ; i < mapHeight ;i++){
		for(int j = 0 ; j < mapWidth ; j++){
			Tile *current = tiles.at(i).at(j);
			printf("%c", current->ch);
		}
		puts("");
	}
}
bool init(){
	const int mapWidth = strlen(map[0]);
	for(int i = 0 ; i < mapHeight ;i++){
		vector<Tile *> rowTile;
		for(int j = 0 ; j < mapWidth ; j++){

			char chara = map[i][j];
			
			Position position;
			position.x = j;
			position.y = i;
		
			Tile *tile = createTile(position, chara);
			rowTile.push_back(tile);
//			puts("a");
			if(chara == startCharacter){
				startingTile = tile;
			}else if(chara == destinationCharacter){
				destination = tile;
			}
		}
//		puts("a");
		tiles.push_back(rowTile);
	}
	printMap();
	startingTile->distance = 0;
	startingTile->isVisit = true;
	return true;
}



Tile *getTile(Position position){
	Tile *current = tiles.at(position.y).at(position.x);
	if(current->ch == wallCharacter) return NULL;
	else if(current->isVisit || current->ch == wallCharacter) return NULL;
	return current;
}

double calculateDistance(const Tile *tile){
	return sqrt(pow(tile->position.x - destination->position.x, 2) 
			  + pow(tile->position.y - destination->position.y, 2) );
}

struct Compare{
	bool operator() (const Tile *a, const Tile *b){
		return a->distance+calculateDistance(a) > b->distance+calculateDistance(b);
	}
};

void process(){
	priority_queue<Tile *, vector<Tile* > ,Compare> tileContainer;
	tileContainer.push(startingTile);
	
	while(tileContainer.empty() == false){
		Tile *curr = tileContainer.top();
		tileContainer.pop();
		for(int i = 0 ; i < directionAmount ; i++){
			Position position;
			position.x = curr->position.x + directionX[i];
			position.y = curr->position.y + directionY[i];
			Tile *target = getTile(position);
			if(target == NULL) continue;
			
			target->isVisit = true;
			target->ch = visitedCharacter;
			if(target->distance > curr->distance + 1){
				target->distance = curr->distance + 1;
				target->before = curr;
			}
			
			tileContainer.push(target);
			
			if(target == destination){
				return;
			}
			printMap();
		}
	}
	
}
void backtrack(){
	Tile *current = destination;
	while(current){
		current->ch = pathCharacter;
		current = current->before;
		printMap();
	}
}

void djikstra(){
	const bool initResult = init();
	if(!initResult) NULL;
	
	process();
	backtrack();
}


int main()
{
//	init();

//	printMap();
	djikstra();	
    return 0;
}
