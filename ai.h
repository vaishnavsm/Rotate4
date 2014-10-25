#ifndef ROT4_AI_MODULE
#define ROT4_AI_MODULE

#include <iostream>

void cr(char &a, char &b, char &c, char &d);
//void log(char x[8][8]){std::cout<<std::endl<<"---\n";for(int i=0;i<8;i++){for(int j=0;j<8;j++) {std::cout<<x[i][j]<<" ";}std::cout<<std::endl;}std::cout<<"---"<<std::endl;}
//void log(int x[8][8]){std::cout<<std::endl<<"---\n";for(int i=0;i<8;i++){for(int j=0;j<8;j++) {std::cout<<x[i][j]<<" ";}std::cout<<std::endl;}std::cout<<"---"<<std::endl;}
void getstate(int (*state)[8][8], char a[8][8], char x);
long int getEntropy(char (*field)[8][8]);

class  Ai{
	// Private section
		Ai(){};
		char (*field)[8][8];
		char s0[8][8],s1[8][8], s2[8][8], s3[8][8];
		char t0[8][8],t1[8][8], t2[8][8], t3[8][8];
		void grav(char (*f)[8][8]);
		void rot(int,char (*f)[8][8]);
		bool dn = false;
		void done(){dn=true;}
		void notdone(){dn=false;}
		
		void stage1(bool *res);
		void stage2(bool *res);
		void stage3(bool *res);
		void noise();
	public:
		// Public Declarations
		Ai(char (*_field)[8][8]){field = _field;}
		void play();
		bool isdone(){return dn;}
};

#endif
