#include "Instrucciones.cpp"
#include "Control.cpp"

class controlador
{
	public:
		//controlador();
		//~controlador();
		int lecturaArchivo_Mips(string nfile);
		int lecturaArchivo_lineasC(string nfile);
		void mostrarContenido_Mips();
		void mostrarContenido_lineasC();
		//funciones....
	private:
		int cnt;
		int cnt_lineas_control;
		Instrucciones inst_mips[10000];
		Control inst_lineas_control[10000];
};