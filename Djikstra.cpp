#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;;


struct Pos{
	int x;
	int y;
};
Pos sPos, ePos;

struct Map{
	char str;
	bool isVisited;
	Pos currPos;
	Map* before;
};

Map xMap[10][15];

char MapChar[10][16] = {
	"###############",
	"#E###         #",
	"#   #         #",
	"###       #####",
	"##         ####",
	"#    ##########",
	"###           #",
	"#######   #####",
	"#             #",
	"###############",
};

void mapGenerate(){
	for(int i = 0 ; i < 10 ; i++){
		for(int j = 0 ; j < 15 ; j++){
			char curr = MapChar[i][j];
			Pos currPos;
			currPos.y = i;
			currPos.x = j;
			 if(curr == 'S'){
			 	sPos = currPos;
			 }
			 if(curr == 'E'){
			 	ePos = currPos;
			 }
			 xMap[i][j].currPos = currPos;
			 xMap[i][j].str = curr;
			 xMap[i][j].before = NULL;
			 xMap[i][j].isVisited = false;
		}
	}
}
int dirX[4] = {0,1,0,-1};
int dirY[4] = {-1,0,1,0};

void printmap(){
	for(int i  = 0 ; i < 10 ; i++){
		for(int j = 0 ; j < 15 ; j++){
			printf("%c", xMap[i][j].str);
		}
		printf("\n");
	}
}

void astar(){
	vector<Map *> listMap;
	listMap.push_back(&xMap[sPos.y][sPos.x]);
	Map *currMap;
			printf("GA");

	while (!listMap.empty()){
		currMap = listMap[0];
		listMap.erase(listMap.begin());
	
		currMap->isVisited = true;
		
		if(currMap->str == 'E'){
			break;
		}
		for(int i = 0; i < 4 ; i++){
			Map *newMap = &xMap[currMap->currPos.y + dirY[i]][currMap->currPos.x + dirX[i]];
			
			bool list = false;
					

			for(int j = 0 ; j < listMap.size() ; j++){
				if(listMap[j] == newMap){
					list = true;
					break;
				}
			}
			
			if(newMap->isVisited || newMap->str == '#' || list) continue;
			
			listMap.push_back(newMap);
			newMap->before = currMap;
		}
	}
	while(currMap != NULL){
		if(currMap->str != 'S'  && currMap->str != 'E') currMap->str = '*';
		currMap = currMap->before;
	}
	
	printmap();
	
}
int main(){
	mapGenerate();
	astar();
	return 0;
}
