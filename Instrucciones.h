#include <string>

using std::string;

class Instrucciones
{
	public:
		Instrucciones();
		//~Instrucciones();
		void establecerInstruccion(string op,string r1,string r2, string r3);
		void establecerInstruccion(string r1);
		void setRegistro1(string r);
		void setRegistro2(string r);
		void setRegistro3(string r);
		char Operacion(string op);
		char getTipo();
		string getRegistro1();
		string getRegistro2();
		string getRegistro3();
	private:
		char tipo;
		string registro1;
		string registro2;
		string registro3;
};