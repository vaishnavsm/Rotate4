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
#include <vector>

using namespace std;

vector<int> ddvec;
vector<int> prefvec;

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
	ddvec.clear();
	
	memcpy(s0,*field,sizeof(*field));
	memcpy(s1,*field,sizeof(*field)); rot(1,&s1);
	memcpy(s2,*field,sizeof(*field)); rot(2,&s2);
	memcpy(s3,*field,sizeof(*field)); rot(-1,&s3);
	
	memcpy(t0,s0,sizeof(s0));
	memcpy(t1,s1,sizeof(s1)); rot(1,&t1);
	memcpy(t2,s2,sizeof(s2)); rot(2,&t2);
	memcpy(t3,s3,sizeof(s3)); rot(-1,&t3);
	
	bool res=false;
	stage1(&res);
	if(!res) stage2(&res);
	if(!res && rand()%10>=7) stage3(&res);
	if(!res) noise();
	done();
}

void setmark(map<int,int> *m, int x, int y){
	if(((*m)[x]*(*m)[x])<(y*y)){(*m)[x] = y;}
}

void Ai::stage1(bool *res){
	cout<<"\n[NIC: ] OK,my turn...";
	map<int,int> mark;
	for(int i=0;i<11;i++) mark[i]=0;
	//Same field
	for(int i=0;i<8;i++){
		if(s0[0][i]==' '){ s0[0][i] = 'O';
		grav(&s0);
		int state[8][8];
		getstate(&state,s0, 'O');
		if(wincheck(state)){setmark(&mark, i, 1000);break;}
		
		for(int j=0;j<8;j++){
			memcpy(t0,*field,sizeof(*field));
			
			if(t0[0][j]==' '){ t0[0][j] = 'X';
			grav(&t0);	
			int st2[8][8];
			getstate(&st2, t0, 'X');
			if(wincheck(st2)){if(j==i) {setmark(&mark, i, 500); break;}else setmark(&mark, i, -499);}}
		}
		
		}
		
		memcpy(t0,s0,sizeof(s0));
			int st2[8][8];
			
		if(t0[0][i]==' '){t0[0][i] = 'X';
		grav(&t0);	
		getstate(&st2, t0, 'X');
		if(wincheck(st2)){setmark(&mark, i, -250);}}
		
		memcpy(t0,s0,sizeof(s0));
		
		rot(1,&t0);
		getstate(&st2, t0, 'X');
		if(wincheck(st2)){setmark(&mark, i, -250);}
		
		memcpy(t0,s0,sizeof(s0));
		
		rot(2,&t0);
		getstate(&st2, t0, 'X');
		if(wincheck(st2)){setmark(&mark, i, -250);}
		
		memcpy(t0,s0,sizeof(s0));
		
		rot(-1,&t0);
		getstate(&st2, t0, 'X');
		if(wincheck(st2)){setmark(&mark, i, -250);}
		
		memcpy(s0,*field,sizeof(*field));
		memcpy(t0,s0,sizeof(s0));
	}
	//Rotate mech
	int st[8][8];
	getstate(&st,s1,'O');
	if(wincheck(st)) mark[8]=999;
	getstate(&st,s1,'X');
	if(wincheck(st)) mark[8]=-800;
	
	getstate(&st,s2,'O');
	if(wincheck(st)) mark[9]=999;
	getstate(&st,s2,'X');
	if(wincheck(st)) mark[9]=-800;
	
	getstate(&st,s3,'O');
	if(wincheck(st)) mark[10]=999;
	getstate(&st,s3,'X');
	if(wincheck(st)) mark[10]=-800;
	
	auto mov = max_element(mark.begin(), mark.end(), [](const pair<int,int> &p1, const pair<int,int> &p2){return (p1.second)<(p2.second);});
	mark.erase(mov->first);
	auto mov2 = max_element(mark.begin(), mark.end(), [](const pair<int,int> &p1, const pair<int,int> &p2){return (p1.second)<(p2.second);});
	
	for(auto iter = mark.begin(); iter!=mark.end();iter++){ if(iter->second<0) ddvec.push_back(iter->first);
	else if(iter->second == mov->second && mov->second!=0) prefvec.push_back(iter->first);}
	
	if((mov->second != mov2->second) && mov->second!=0){
			cout<<"\n[NIC: ]I think I'll do this\n";
			if(mov->first<8){cout<<"Nic puts a piece in the "<<mov->first +1<<(mov->first+1==1?"st":mov->first+1==2?"nd":mov->first+1==3?"rd":"th")<<" Row";getch(); AIF::placeAt(mov->first);}
			else if(mov->first==8){cout<<"Nic Rotates the board clockwise";getch(); AIF::rotateClock();}
			else if(mov->first==9){cout<<"Nic Rotates the board Upside Down";getch(); AIF::rotateUSD();}
			else if(mov->first==10){cout<<"Nic Rotates the board Anti-Clockwise";getch(); AIF::rotateAnti();}
			*res = true;
	}
	else{
		*res = false;
	}
}
void Ai::stage2(bool *res){
	//Learning
	
	
	*res = false;
}
void Ai::stage3(bool *res){
	//Entropy Maximising
	/* Entropy of a board, G = S(O) - S(X)
	 *
	 * S(h) = [(Number of placements such that no h's are next to others) + (Number of placements such that a group of 2 is formed)
	 *		  +(Number of placements such that a group of 3 is formed)]/4
	 * Note, If a group of 4 is formed, that is a win condition, and will be dealt with in stage1().
	 * Also note, it seems that all the criteria have same weightage, but in reality, the first is counted once, the second twice and the third thrice.
	 */
	 int besti=0,bestent=0;
	for(int i=0;i<8;i++){
		memcpy(s0,*field,sizeof(*field));
		if(s0[0][i]==' '){s0[0][i]='O'; grav(&s0);
		int ent = getEntropy(&s0);
		if(ent>bestent){besti=i; bestent=ent;}
	}}
	if(bestent>0){
		cout<<"\n[NIC: ] OK... Let me try this.\n";
		if(besti<8){cout<<"Nic puts a piece in the "<<besti +1<<(besti+1==1?"st":besti+1==2?"nd":besti+1==3?"rd":"th")<<" Row";getch(); AIF::placeAt(besti);}
		
		*res=true;
		return;
	}
	*res = false;
}

int comp(char (*field)[8][8], int i, int j, int i1,int j1, char c){
	int s=0;
	if(i>=0&&i<8){if((*field)[i][j]==c) {s+=2;	if(i1>=0&&i1<8){if((*field)[i1][j1]==c)		{s+=2;} else if((*field)[i1][j1]==' '){s++;}}}
	else if((*field)[i][j]==' '){s++;}}
}

long int getEntropy(char (*field)[8][8]){
	 long int G,S_O,S_X; G=0;S_O=0;S_X=0;
	 for(int i=0;i<8;i++)for(int j=0;j<8;j++){
	 	char c = (*field)[i][j];
	 	int s = 0,s0=0;
	 	if(c=='X'||c=='O'){
	 	s=comp(field, i-1,j,i-2,j, c);
	 	if(s){s0+=s+1;s=0;}
	 	s=comp(field, i-1, j-1, i-2, j-2, c);
		if(s){s0+=s+1;s=0;}
	 	s=comp(field, i, j-1, i, j-2, c);
	 	if(s){s0+=s+1;s=0;}
	 	s=comp(field, i+1, j-1, i+2, j-2, c);
	 	if(s){s0+=s+1;s=0;}
	 	s=comp(field, i+1, j, i+2, j, c);
	 	if(s){s0+=s+1;s=0;}
	 	s=comp(field, i+1, j+1, i+2, j+2, c);
	 	if(s){s0+=s+1;s=0;}
	 	s=comp(field, i, j+1, i, j+2, c);
	 	if(s){s0+=s+1;s=0;}
	 	s=comp(field, i-1, j+1, j-2, j+2, c);
	 	if(s){s0+=s+1;}
	 	if(s0==0) s0=1;
	 	}
	 	
	 	if(c=='X') S_X+=s0;
	 	else if(c=='O') S_O+=s0;
	 }
	G=(S_O-S_X);
	return G;	
	
}

void Ai::noise(){
	int r;
	bool flag = true;
	if(prefvec.empty()){
	do{
		flag=false;
		r = rand()%18;
		for(auto iter=ddvec.begin();iter!=ddvec.end();iter++) if((r/2==*iter)||((r==15)&&(*iter==8))||((r==16)&&(*iter==9))||((r==17)&&(*iter==10))){
			flag=true;break;
		}
		if(r/2<8) if((*field)[0][r/2] !=' ') flag = true;
	}while(flag);
	}else{
		r = prefvec.at(rand()%prefvec.size());
	}
	
	
	cout<<"\n[NIC: ] Hmm, I don't know...  I think I'll do this...\n";
	if(r<15){cout<<"Nic puts a piece in the "<<(r/2 + 1)<<(r/2+1==1?"st":r/2+1==2?"nd":r/2+1==3?"rd":"th")<<" Row";getch(); AIF::placeAt(r/2);}
	else if(r==15){cout<<"Nic Rotates the board Clockwise";getch();AIF::rotateClock();}
	else if(r==16){cout<<"Nic Rotates the board Upside Down";getch();AIF::rotateUSD();}
	else if(r==17){cout<<"Nic Rotates the board Anti Clockwise";getch();AIF::rotateAnti();}
	else {cout<<"FATAL ERROR";exit(-1);}
}

void getstate(int (*state)[8][8], char a[8][8], char x){
	for(int i=0;i<8;i++)for(int j=0;j<8;j++){
		if(tolower(a[i][j])==tolower(x)){ (*state)[i][j] = 1;}
		else{ (*state)[i][j] = 0;}
	}
}
