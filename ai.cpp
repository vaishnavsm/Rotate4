#include "ai.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <process.h>
#include "main.h"
#include "utils.h"
#include <map>
#include <ctype.h>
#include <iterator>
#include <algorithm>

using namespace std;

void cr(char &a, char &b, char &c, char &d);
void log(char x[8][8]){cout<<endl<<"---\n";for(int i=0;i<8;i++){for(int j=0;j<8;j++) {cout<<x[i][j]<<" ";}cout<<endl;}cout<<"---"<<endl;}
void log(int x[8][8]){cout<<endl<<"---\n";for(int i=0;i<8;i++){for(int j=0;j<8;j++) {cout<<x[i][j]<<" ";}cout<<endl;}cout<<"---"<<endl;}
void getstate(int (*state)[8][8], char a[8][8], char x);

void Ai::rot(int degree, char(*f)[8][8]){
	int n = 8;
	if(degree==1){
		for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cr((*f)[i][j], (*f)[n-1-j][i], (*f)[n-1-i][n-1-j], (*f)[j][n-1-i]);
    
    grav(f);
	}
	if(degree==2){
		for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cr((*f)[i][j], (*f)[n-1-j][i], (*f)[n-1-i][n-1-j], (*f)[j][n-1-i]);
    	for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cr((*f)[i][j], (*f)[n-1-j][i], (*f)[n-1-i][n-1-j], (*f)[j][n-1-i]);
    grav(f);
	}
	if(degree==-1){
		for(int i=0; i<n/2; i++)
  		 for(int j=0; j<(n+1)/2; j++)
    	   cr((*f)[i][j], (*f)[j][n-1-i], (*f)[n-1-i][n-1-j], (*f)[n-1-j][i]);
	grav(f);
	}
	return;
}

void cr(char &a, char &b, char &c, char &d)
{
   char temp = a;
   a = b;
   b = c;
   c = d;
   d = temp;
}

void Ai::grav(char (*f)[8][8]){
		for(int i = 0;i<8; i++){
		int spot=0;
		for(int j=7;j>0;j--){
			if((*f)[j][i]==' ') {spot = j;
				for(int x = j;x>=0;x--){
					if((*f)[x][i]!=' '){
						(*f)[spot][i]=(*f)[x][i];
						(*f)[x][i]=' ';
						spot=0;
						break;
					}
				}
			}
		}
	}
}

void Ai::play(){
	memcpy(s0,*field,sizeof(*field));
	memcpy(s1,*field,sizeof(*field)); rot(1,&s1);
	memcpy(s2,*field,sizeof(*field)); rot(2,&s2);
	memcpy(s3,*field,sizeof(*field)); rot(-1,&s3);
	
	memcpy(t0,s0,sizeof(s0));
	memcpy(t1,s1,sizeof(s1)); rot(1,&t1);
	memcpy(t2,s2,sizeof(s2)); rot(2,&t2);
	memcpy(t3,s3,sizeof(s3)); rot(-1,&t3);
	
	bool res=true;
	stage1(&res);
	if(!res) stage2(&res);
	if(!res) stage3(&res);
	if(!res) noise();
	done();
}

void setmark(map<int,int> *m, int x, int y){
	if((*m)[x]*(*m)[x]<y*y){/*cout<<endl<<"changing from "<<(*m)[x]<<" to "<<y<<endl;*/ (*m)[x] = y;}
	//else{cout<<endl<<"not changing from "<<(*m)[x]<<" to "<<y<<endl;
	//}
}

void Ai::stage1(bool *res){
	map<int,int> mark;
	for(int i=0;i<8;i++) mark[i]=0;
	for(int i=0;i<8;i++){
		s0[0][i] = 'O';
		grav(&s0);
		int state[8][8];
		getstate(&state,s0, 'O');
		if(wincheck(state)){setmark(&mark, i, 1000);break;}
		
		for(int j=0;j<8;j++){
			memcpy(t0,*field,sizeof(*field));
		//	memcpy(t1,*field,sizeof(*field)); rot(1,&t1);
		//	memcpy(t2,*field,sizeof(*field)); rot(2,&t2);
		//	memcpy(t3,*field,sizeof(*field)); rot(-1,&t3);
			
			t0[0][j] = 'X';
//			log(t0);
			grav(&t0);	
//			log(t0);
			int st2[8][8];
			getstate(&st2, t0, 'X');
			if(wincheck(st2)){if(j==i) {setmark(&mark, i, 500); break;}else setmark(&mark, i, -499);}
			
//		getch();
		}
		//TO IMPLEMENT -
		/*
		*You turn board and win
		*Enemy turns board and he wins(prevent)
		*You turn board and enemy win(prevent)
		*/
		memcpy(s0,*field,sizeof(*field));
		//memcpy(s1,*field,sizeof(*field)); rot(1,&s1);
		//memcpy(s2,*field,sizeof(*field)); rot(2,&s2);
		//memcpy(s3,*field,sizeof(*field)); rot(-1,&s3);
		
		memcpy(t0,s0,sizeof(s0));
		//memcpy(t1,s1,sizeof(s1)); rot(1,&t1);
		//memcpy(t2,s2,sizeof(s2)); rot(2,&t2);
		//memcpy(t3,s3,sizeof(s3)); rot(-1,&t3);
	}
	
	auto mov = max_element(mark.begin(), mark.end(), [](const pair<int,int> &p1, const pair<int,int> &p2){return (p1.second)<(p2.second);});
	mark.erase(mov->first);
	auto mov2 = max_element(mark.begin(), mark.end(), [](const pair<int,int> &p1, const pair<int,int> &p2){return (p1.second)<(p2.second);});
	
	if((mov->second != mov2->second) && mov->second!=0){
			cout<<"\nI think I'll put my piece here";getch(); AIF::placeAt(mov->first);
			*res = true;
	}
	else{
		*res = false;
	}
}
void Ai::stage2(bool *res){
	*res = false;
}
void Ai::stage3(bool *res){
	*res = false;
}

void Ai::noise(){
	int r = rand()%18;
	if(r<15){cout<<"\nI think I'll put my piece here";getch(); AIF::placeAt(r/2);}
	else if(r==15){cout<<"\nI think I'll Rotate the board this way";getch();AIF::rotateClock();}
	else if(r==16){cout<<"\nI think I'll Rotate the board this way";getch();AIF::rotateAnti();}
	else if(r==17){cout<<"\nI think I'll Rotate the board this way";getch();AIF::rotateUSD();}
	else {cout<<"FATAL ERROR";exit(-1);}
}

void getstate(int (*state)[8][8], char a[8][8], char x){
	//cout<<endl<<x<<endl;
	for(int i=0;i<8;i++)/*{*/for(int j=0;j<8;j++){
		if(tolower(a[i][j])==tolower(x)){ (*state)[i][j] = 1;}
		else{ (*state)[i][j] = 0;}
		//cout<<"|"<<a[i][j]<<"|";
	}//cout<<endl;}getch();
}
