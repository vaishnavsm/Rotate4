#include "precompiler.h"
#include <iostream>
#include <set>
#include <cstdint>
#include <fstream>

using namespace std;

	int f[8][8];
	void zerofield();
	uint64_t genmask();

void precompile(){
	set<uint64_t> sol;
	int count=0;
	zerofield();
	for(int i=0;i<8;i++)for(int j=0;j<8;j++){
		if(j<5) // Horizontal right
		{
			f[i][j]=1; f[i][j+1]=1; f[i][j+2]=1; f[i][j+3]=1;
			sol.insert(genmask());
			zerofield();
		}
		if(j>2) { //Left
			f[i][j]=1; f[i][j-1]=1; f[i][j-2]=1; f[i][j-3]=1;
			sol.insert(genmask());
			zerofield();
		}
		if(i>2){ //UP
			f[i][j]=1; f[i-1][j]=1; f[i-2][j]=1; f[i-3][j]=1;
			sol.insert(genmask());
			zerofield();
		}
		if(i<5){ //DOWN
			f[i][j]=1; f[i+1][j]=1; f[i+2][j]=1; f[i+3][j]=1;
			sol.insert(genmask());
			zerofield();
		}
		if(i<5&&j>2){ //Bottom left diag
			f[i][j]=1; f[i+1][j-1]=1; f[i+2][j-2]=1; f[i+3][j-3]=1;
			sol.insert(genmask());
			zerofield();
		}
		if(i<5&&j<5){ //Down Right
			f[i][j]=1; f[i+1][j+1]=1; f[i+2][j+2]=1; f[i+3][j+3]=1;
			sol.insert(genmask());
			zerofield();
		}
		if(i>2&&j>2){ //Up left
			f[i][j]=1; f[i-1][j-1]=1; f[i-2][j-2]=1; f[i-3][j-3]=1;
			sol.insert(genmask());
			zerofield();
		}
		if(i>2&&j<5){ //Up Right
			f[i][j]=1; f[i-1][j+1]=1; f[i-2][j+2]=1; f[i-3][j+3]=1;
			sol.insert(genmask());
			zerofield();
		}
		cout<<endl<<(j+i)/16.0*100<<endl;
	}
	
	cout<<sol.size();
	cout<<endl<<"Writing...";
	
	ofstream file;
	file.open("masks.dat");
	
	for(set<uint64_t>::iterator iter = sol.begin();iter!=sol.end();iter++){
		file <<*iter<<'\n';
	}
	
	file.close();
	
}

void zerofield(){
		for(int _i=0;_i<8;_i++)for(int _j=0;_j<8;_j++) f[_i][_j]=0;
}

uint64_t genmask(){
	uint64_t buff=0;
	for(int p=0;p<8;p++){
			for(int q=0;q<8;q++) {
					buff = (buff<<1); 
					buff+=f[p][q];
			}}
			return buff;
}
