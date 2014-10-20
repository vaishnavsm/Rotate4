#include "iostream"
#include "math.h"
#include "time.h"
#include "vector"
#include "queue"
#include "cstdlib"
#include "algorithm"
#include "iterator"
#include "conio.h"
#include "precompiler.h"
#include "utils.h"
#include "windows.h"

#define BLOCK  '\xDB'
#define TOP  '\xDF'
#define BOTTOM  '\xDC'

using namespace std;

void init();
void display();
void player_game(bool);
void update();
void gravity();
void updatestate();
void rotr(int);
void cyclic_roll(char &a, char &b, char &c, char &d);
void mainscr();
void helpscr();
void play1p();
void play2p();

char field[8][8];
int state1[8][8];
int state2[8][8];
bool running = true;
bool player = true;
int cursor=0;

int state = 0;

int main(){
	
	init();
	initutils();
	srand(time(NULL));
	int cursor = 0;
	player = true;

	setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);

	while(running){
		switch(state){
		case 0: mainscr(); break;
		case 2:	play2p();break;
		case 3: helpscr(); break;
		case 1: play1p(); break;
	}}
	
	return 0;
}

void play2p(){
	if(player) player_game(player);
		else player_game(player);
		player=!player;
}

void mainscr(){
	system("cls");
	setColor( BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	

addspaces();cout<<"______      _        _           _____ "<<endl;
addspaces();cout<<"| ___ \\    | |      | |         / /   |"<<endl;
addspaces();cout<<"| |_/ /___ | |_ __ _| |_ ___   / / /| |"<<endl;
addspaces();cout<<"|    // _ \\| __/ _` | __/ _ \\ / / /_| |"<<endl;
addspaces();cout<<"| |\\ | (_) | || (_| | ||  __// /\\___  |"<<endl;
addspaces();cout<<"\\_| \\_\\___/ \\__\\__,_|\\__\\___/_/     |_/"<<endl;
cout<<"\n\nChoose: \n\t1)Play Game(1 Player);\n\t2)Play Game(2 Player);\n\t3)Help;\n\t4)Quit :'(\nChoice: ";
char x;
bool loop = true;
x=tolower(getch());
do{
	if(x=='1'){state=1;loop=false;}
	else if(x=='2') {
	state = 2;loop=false;}
	else if(x=='3'){ state=3;loop=false;}
	else if(x=='4'||x=='q'){running = false;loop=false;}
	else{
		cout<<"\nTry Again: ";
		x=getch();}
}while(loop);
	
}

void helpscr(){
	setColor( BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	system("cls");
	cout<<"\t\t\t\t"<<BLOCK<<" ROTATE 4 "<<BLOCK;
	cout<<endl<<"\nInstructions-\n\t1)A - Move Cursor Left\n\t2)D - Move Cursor Right\n\t3)S(or)Space - Place piece at cursor\n\t";
	cout<<"4)J - Rotate board anticlockwise\n\t5)D - Rotate board clockwise\n\t6)K - Rotate Twice(Upside Down)\n\n\t7)q - Quit";
	cout<<endl<<endl<<endl;
	cout<<endl<<"\n\nVaishnav (Me) - Everything you see on the screen, however bad it is.\nEdwin - The idea of the game(good one!)\nAnand,Unni,Advaith,Gopal, Vinu and others, for\n\t\t1)\"Helping\" with the aglos and stuff";
	cout<<"\n\t\t2)For giving me a reason to actually do this stuff.\n\t\t3)For coping with my otherworldly language\n\t\t\t and behavioural patterns\n"<<endl;
	cout<<"Press SPACE to continue";
	char x = getch();
	while(x!=' ') x=getch();
	system("cls");
	state = 0;	
}

void player_game(bool move){
	display();
	char inp = getch();
	while(1){
		inp=tolower(inp);
		if(inp=='d' && cursor<7) cursor++;
		else if(inp=='a' && cursor>0) cursor--;
		else if(inp=='q') {
		running = false;return;}
		else if(inp=='s'||inp==' '){
			if(field[0][cursor]==' '){
				field[0][cursor] = move?'X':'O';
				update();
				break;
			}
		}
		else if(inp=='l') {rotr(1);break;}
		else if(inp=='k') {rotr(2);break;}
		else if(inp=='j') {rotr(-1);break;}
		display();
		inp = getch();
	}
}
void init(){
	
	for(int i = 0;i<8;i++)for(int j=0;j<8;j++){
	field[i][j] = ' ';
	state1[i][j]=0; state2[i][j]=0;
}
}

void rotr(int degree){
	int n = 8;
	if(degree==1){
		for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cyclic_roll(field[i][j], field[n-1-j][i], field[n-1-i][n-1-j], field[j][n-1-i]);
    
    update();
	}
	if(degree==2){
		for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cyclic_roll(field[i][j], field[n-1-j][i], field[n-1-i][n-1-j], field[j][n-1-i]);
    	for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cyclic_roll(field[i][j], field[n-1-j][i], field[n-1-i][n-1-j], field[j][n-1-i]);
    update();
	}
	if(degree==-1){
		for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cyclic_roll(field[i][j], field[j][n-1-i], field[n-1-i][n-1-j], field[n-1-j][i]);
	update();
	}
	return;
}

void cyclic_roll(char &a, char &b, char &c, char &d)
{
   char temp = a;
   a = b;
   b = c;
   c = d;
   d = temp;
}

void update(){
	//Gravity
	gravity();
	updatestate();
	//Win Check
	if(wincheck(state1)){
		cursor=0;
		display();
		cout<<"\n\n";
		setColor(BACKGROUND_RED|BACKGROUND_INTENSITY);
		addspaces();
		cout<<"RED WINS!!!";
		setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
		cout<<"\n\nPress anything to return to menu...";getch();state=0;
		init();
	}

	if(wincheck(state2)){
		cursor = 0;
		display();
		cout<<"\n\n";
		setColor(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
		addspaces();
		cout<<"YELLOW WINS!!!";
		setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
		cout<<"\n\nPress anything to return to menu...";getch();state=0;
		init();
	}
}

void updatestate(){
	if(player){
		for(int i=0;i<8;i++)for(int j=0;j<8;j++) {
		if(field[i][j]=='X') state1[i][j] = 1;
		else state1[i][j]=0;	
		}
	}else{
		for(int i=0;i<8;i++)for(int j=0;j<8;j++) {
		if(field[i][j]=='O') state2[i][j] = 1;
		else state2[i][j]=0;	
		}
	}
}

void gravity(){
		for(int i = 0;i<8; i++){
		int spot=0;
		for(int j=7;j>0;j--){
			if(field[j][i]==' ') {spot = j;
				for(int x = j;x>=0;x--){
					if(field[x][i]!=' '){
						field[spot][i]=field[x][i];
						field[x][i]=' ';
						spot=0;
						break;
					}
				}
			}
		}
	}
}

void display(){
	
	system("cls");
	addspaces();
	setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	putHalfBlockLine(false);putchar('\n');
	for(int i = 0;i<8;i++){
//		setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		addspaces();
		putchar(BLOCK);
		for(int j=0;j<8;j++) {
			char ch = field[i][j];
			if(ch=='X'){
				setColor(FOREGROUND_RED|FOREGROUND_INTENSITY);
				cout <<BLOCK<<BLOCK<<BLOCK;
				setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout<<BLOCK;
			} 
			else if(ch=='O') {
				setColor(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
				cout <<BLOCK<<BLOCK<<BLOCK;
				setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout<<BLOCK;
			}
			else{
			 setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);	
			 cout <<" "<<ch<<" "<<BLOCK;
			 
			}
		}
		putchar('\n');
		addspaces();
		putBlockLine();
		cout<<endl;
	}
	setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	cout<<endl;
	addspaces();
	for(int i=0;i<cursor;i++) cout<<"    ";
	cout<<" "<<TOP<<TOP<<TOP;
	cout<<endl<<"\n\n\n";
	if(player){
		setColor(BACKGROUND_RED|BACKGROUND_INTENSITY);
		addspaces();
		cout<<"REDS TURN!";
		setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	}
	else{
		setColor(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
		addspaces();
		cout<<"YELLOW'S TURN!";
		setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);	}
	cout<<endl;
}

// 1 Player Logic

void player_chance();
void ai_chance();

void play1p(){
	
	player = (rand()%5)>=2;
	while(state==1){
		if(player){
			player_chance();
		}
		else{
			ai_chance();	
		}
		player = !player;
		display();
	}
}

void player_chance(){
		char inp = getch();
		while(1){
		inp=tolower(inp);
		if(inp=='d' && cursor<7) cursor++;
		else if(inp=='a' && cursor>0) cursor--;
		else if(inp=='q') {
		running = false;return;}
		else if(inp=='s'||inp==' '){
			if(field[0][cursor]==' '){
				field[0][cursor] = 'X';
				update();
				break;
			}
		}
		else if(inp=='l') {rotr(1);break;}
		else if(inp=='k') {rotr(2);break;}
		else if(inp=='j') {rotr(-1);break;}
		display();
		inp = getch();
	}
}

void ai_chance(){
	cout<<"LOL";
	getch();	
}
