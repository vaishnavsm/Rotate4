#include "utils.h"
#include "set"
#include "string"
#include "iostream"
#include "fstream"
#include "cstdlib"
#include "windows.h"


#define BLOCK  '\xDB'
#define TOP  '\xDF'
#define BOTTOM  '\xDC'
#define BGATTR BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY
using namespace std;

set<uint64_t> sol;
HANDLE hCon;

void initutils(){
	ifstream file;
	string line;
	file.open("masks.dat");
	if(file.is_open()){
		while(getline(file,line)){
			sol.insert(stoull(line));
		}
	}
	file.close();
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
}

bool wincheck(int state[8][8]){
	uint64_t buff=0;
	for(int p=0;p<8;p++){
			for(int q=0;q<8;q++) {
					buff = (buff<<1); 
					buff+=state[p][q];
			}}
	for(set<uint64_t>::iterator iter=sol.begin();iter!=sol.end();iter++) {if((*iter&buff)==*iter) return true;}
	
	return false;
	
}

void putBlockLine(){
	cout<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK<<BLOCK;
}

void putHalfBlockLine(bool top){
	if(top) cout<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP<<TOP;
	else cout<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM<<BOTTOM;
}

void putAtPoint(const int x, const int y){
	COORD cursor;
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(hCon, cursor);
}

void setColor(WORD attr){
	SetConsoleTextAttribute(hCon, attr);
}

void addspaces(){
		WORD attr;
		CONSOLE_SCREEN_BUFFER_INFO   csbi;

		if(GetConsoleScreenBufferInfo(hCon, &csbi))
 	    attr = csbi.wAttributes;

		SetConsoleTextAttribute (hCon,BGATTR);
		cout<<"\t\t";
		SetConsoleTextAttribute(hCon,attr);
}

void winpiece(int (*arr)[8], const int (*st)[8][8]){
		uint64_t buff=0,bx;
	for(int p=0;p<8;p++){
			for(int q=0;q<8;q++) {
					buff = (buff<<1); 
					buff+=(*st)[p][q];
			}}
	for(set<uint64_t>::iterator iter=sol.begin();iter!=sol.end();iter++) {if((*iter&buff)==*iter){buff = (*iter&buff); break;}}
	bx=buff;
	int pos[4] = {0,0,0,0};
	int i=1,c=0;
	while(bx!=0 && i<65 && c<4){
		if ((bx&1)==1) {pos[c]=64-i; c++;}
		bx/=2;
		i++;
	}
	for(int s=0;s<4;s++){
		(*arr)[2*s] = (pos[s]/8);
		(*arr)[(2*s)+1] = (pos[s]%8);
	}
}
