#include <string>
using std::string;

class Control
{
	//Control();
	//~Control();
	public:
		void setRegDst(bool rd);
		void setJump(bool j);
		void setBranch(bool b);
		void setMemRead(bool mr);
		void setMemToReg(bool mtr);
		void setALUOp(string aop);
		void setMemWrite(bool mw);
		void setALUSrc(bool as);
		void setRegWrite(bool rw);
		bool getRegDst();
		bool getJump();
		bool getBranch();
		bool getMemRead();
		bool getMemToReg();
		string getALUOp();
		bool getMemWrite();
		bool getALUSrc();
		bool getRegWrite();
		void establecerControl(bool rd, bool j, bool b, bool mr, bool mtr, string aop, bool mw, bool as, bool rw);
	private:
		bool regDst;
		bool jump;
		bool branch;
		bool memRead;
		bool memToReg;
		string ALUOp;
		bool memWrite;
		bool ALUSrc;
		bool regWrite;
};