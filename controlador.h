#include "Instrucciones.cpp"
#include "Control.cpp"
#include "Registro.cpp"
#include "stackPointer.cpp"

class controlador
{
	public:
		//controlador();
		//~controlador();
		int readFile_Mips(string nfile);
		int readFile_lineasC(string nfile);
		void showContent_Mips();
		void showContent_lineasC();
		void showContent_Registros();
		void initRegisters();
		void initStackPointer();
		int buscarRegistro(string r);
		int add(int,int);
		int sub(int,int);
		int mul(int,int);
		int div(int,int);
		int addi(int,int);
		int subi(int,int);
		void lw(string,int);
		void sw(string,int);
		bool beq(int,int);
		void j(string);
		void compilar();
		void ejecutarInstruccion(int);
		static const string regs[32];
		static const string operaciones[11];
		//funciones....
	private:
		int cnt;
		int cnt_lineas_control;
		int index;
		Instrucciones inst_mips[10000];
		Control inst_lineas_control[10000];
		Registro registros[32];
		stackPointer sp[1000];
};
