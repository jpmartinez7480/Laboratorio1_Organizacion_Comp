#include <iostream>
#include <fstream>
#include "controlador.h"

using namespace std;

int controlador::lecturaArchivo_Mips(string nfile)
{
	cnt = 0;
	fstream FILE;
	char *linea;
	FILE.open(nfile.c_str(),ios::in);
	if(!FILE){
		cout << "No se pudo abrir el archivo. Comprueba el nombre del archivo o la existencia de este." << endl;
		return 0;
	}
	else
	{
		string line;
		int j = 0;
		while(!FILE.eof())
		{
			string inst[5];
			getline(FILE,line);
			char *cstr = new char[line.length() + 1];
			strcpy(cstr,line.c_str());
			linea = strtok(cstr," ");
			while(linea){
				inst[j] = linea;
				j++;
				linea = strtok(NULL,",");
				cout << inst[j];
			}
			j = 0;
			Instrucciones i;
			if(i.Operacion(inst[0]) == 'R' || i.Operacion(inst[0]) == 'I')
				i.establecerInstruccion(inst[0],inst[1],inst[2],inst[3]);
			else if(inst[0] == "j")
				i.establecerInstruccion(inst[1]);
			inst_mips[cnt] = i;
			cnt++;
		}
		return 1;
	}
	
}

int controlador::lecturaArchivo_lineasC(string nfile)
{
	cnt_lineas_control = 0;
	fstream FILE;
	bool regDst;
	bool jump;
	bool branch;
	bool memRead;
	bool memToReg;
	string ALUOp;
	bool memWrite;
	bool ALUSrc;
	bool regWrite;
	FILE.open(nfile.c_str(),ios::in);
	if(!FILE){
		cout << "No se pudo abrir el archivo. Compruebe el nombre del archivo o la existencia de este" << endl;
		return 0;
	}
	else
	{
		string linea;
		getline(FILE,linea);
		while(FILE >> regDst >> jump >> branch >> memRead >> memToReg >> ALUOp >> memWrite >> ALUSrc >> regWrite){
			Control c;
			c.establecerControl(regDst,jump,branch,memRead,memToReg, ALUOp,memWrite, ALUSrc, regWrite);
			inst_lineas_control[cnt_lineas_control] = c;
			cnt_lineas_control++;
		}
		return 1;
	}
}

void controlador::mostrarContenido_Mips()
{
	string pause;
	for(int i = 0; i < cnt; i++)
		cout << inst_mips[i].getTipo() << " " << inst_mips[i].getRegistro1() << " " << inst_mips[i].getRegistro2() << " " << inst_mips[i].getRegistro3() << endl;
	cout << "Presione cualquier tecla para continuar...";
	cin >> pause;
}

void controlador::mostrarContenido_lineasC()
{
	string pause;
	for(int i = 0; i < cnt_lineas_control; i++)
		cout << inst_lineas_control[i].getRegDst() << " " << inst_lineas_control[i].getJump() << " " << inst_lineas_control[i].getBranch() << " " << inst_lineas_control[i].getMemRead() << " " << inst_lineas_control[i].getMemToReg() << " " << inst_lineas_control[i].getALUOp() << " " <<inst_lineas_control[i].getMemWrite() << " " << inst_lineas_control[i].getALUSrc() << " " << inst_lineas_control[i].getRegWrite() << endl;
	cout << "Presione cualquier tecla para continuar...";
	cin >> pause; 
}