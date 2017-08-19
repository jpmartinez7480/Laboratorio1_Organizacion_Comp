#include "Instrucciones.h"


Instrucciones::Instrucciones()
{
	registro1 = "";
	registro2 = "";
	registro3 = "";
}

void Instrucciones::setRegistro1(string r){
	registro1 = r;
}

void Instrucciones::setRegistro2(string r){
	registro2 = r;
}

void Instrucciones::setRegistro3(string r){
	registro3 = r;
}

char Instrucciones::getTipo(){
	return tipo;
}

string Instrucciones::getRegistro1(){
	return registro1;
}

string Instrucciones::getRegistro2(){
	return registro2;
}

string Instrucciones::getRegistro3(){
	return registro3;
}

char Instrucciones::Operacion(string op){
	//return () ? 'I':'R';
	if(op == "addi" || op == "subi" || op == "beq" || op == "lw" || op == "sw") return 'I';
	else if(op == "j") return 'J';
	else return 'R';
}

void Instrucciones::establecerInstruccion(string op,string r1,string r2, string r3)
{
	tipo = Operacion(op);
	setRegistro1(r1);
	setRegistro2(r2);
	setRegistro3(r3);
}

void Instrucciones::establecerInstruccion(string r1)
{
	tipo = 'J';
	setRegistro1(r1);
}