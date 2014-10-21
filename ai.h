#ifndef ROT4_AI_MODULE
#define ROT4_AI_MODULE

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
