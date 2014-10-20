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
//			cout<<"BUFF "<<buff<<endl;
	for(set<uint64_t>::iterator iter=sol.begin();iter!=sol.end();iter++) {/*cout<<(*iter&buff)<<","<<*iter<<endl;*/ if((*iter&buff)==*iter) return true;}
	
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
