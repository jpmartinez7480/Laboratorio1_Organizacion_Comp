#include <iostream>
#include <fstream>
#include <cstdlib>
#include "controlador.h"

using namespace std;

const string controlador::regs[32]  = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

const string controlador::operaciones[11] = {"add","sub","mul","div","addi","subi","lw","sw","beq","j"};

int controlador::readFile_Mips(string nfile)
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
			if(line[line.length() - 1] == ':'){
				Instrucciones i;
				i.setOperando(linea);
				i.setTipo('L');
				inst_mips[cnt] = i;
				cnt++;
			}
			else if(line[line.length()-1]!=':'){
				while(linea){
				inst[j] = linea;
				j++;
				linea = strtok(NULL,",");
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
		}
		return 1;
	}
	
}

int controlador::readFile_lineasC(string nfile)
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

void controlador::showContent_Mips()
{
	string pause;
	for(int i = 0; i < cnt; i++)
	{
		if(inst_mips[i].getTipo()!='l')
			cout << "tipo: " << inst_mips[i].getTipo() << " " << "instruccion: " <<inst_mips[i].getOperando() << " " << inst_mips[i].getRegistro1() << " " << inst_mips[i].getRegistro2() << " " << inst_mips[i].getRegistro3() << endl;
		else
			cout << "Label " << inst_mips[i].getOperando() << endl;
	}
	cout << "Presione cualquier tecla para continuar...";
	cin >> pause;
}

void controlador::showContent_lineasC()
{
	string pause;
	for(int i = 0; i < cnt_lineas_control; i++)
		cout << inst_lineas_control[i].getRegDst() << " " << inst_lineas_control[i].getJump() << " " << inst_lineas_control[i].getBranch() << " " << inst_lineas_control[i].getMemRead() << " " << inst_lineas_control[i].getMemToReg() << " " << inst_lineas_control[i].getALUOp() << " " <<inst_lineas_control[i].getMemWrite() << " " << inst_lineas_control[i].getALUSrc() << " " << inst_lineas_control[i].getRegWrite() << endl;
	cout << "Presione cualquier tecla para continuar...";
	cin >> pause; 
}

void controlador::initRegisters()
{
	for(int i = 0; i < 32; i++)
		registros[i] =Registro();   
}

void controlador::initStackPointer()
{
	for(int i = 0; i < 1000; i++)
		sp[i] = stackPointer();
}

void controlador::showContent_Registros()
{
	cout << "Registro" << "  " << "valor" << endl;
	for(int i = 0; i < 32; i++)
		cout << regs[i] << "        " <<registros[i].getRegistro() << endl;
}

int controlador::buscarRegistro(string r)
{
	int cnt = 0;
	while(regs[cnt] != r)
		cnt++;
	return cnt;
}

int controlador::add(int r1,int r2){
	return r1+r2;
}

int controlador::sub(int r1,int r2){
	return r1-r2;
}

int controlador::mul(int r1, int r2){
	return r1*r2;
}

int controlador::div(int r1, int r2){
	return r1/r2;
}

int controlador::addi(int r1,int n){
	return r1 + n;
}

int controlador::subi(int r1, int n){
	return r1 - n;
}

void controlador::lw(string r, int pos){	
	registros[buscarRegistro(r)].setRegistro(sp[1000-pos/4].getValue());
}

void controlador::sw(string r, int pos){
	sp[1000-pos/4].setValue(registros[buscarRegistro(r)].getRegistro());
}

bool controlador::beq(int r1, int r2){
	return r1 == r2;
}

void controlador::j(string label)
{
	int i = 1;
	while(inst_mips[i].getOperando()!=label) i++;
	ejecutarInstruccion(i);
}

void controlador::compilar()
{
	index = 0;
	for(index; inst_mips[index].getOperando()!=""; index++)
		ejecutarInstruccion(index);
}

void controlador::ejecutarInstruccion(int pos)
{
	int r1;
	int r2;
	int r3;
	switch(inst_mips[pos].getTipo())
	{
		case 'R':
			r1 = buscarRegistro(inst_mips[pos].getRegistro1());
			r2 =  registros[buscarRegistro(inst_mips[pos].getRegistro2())].getRegistro();
			r3 = registros[buscarRegistro(inst_mips[pos].getRegistro3())].getRegistro();
			if(inst_mips[pos].getOperando() == "add")
				registros[r1].setRegistro(add(r2,r3));
			else if(inst_mips[pos].getOperando() == "sub")
				registros[r1].setRegistro(sub(r2,r3));
			else if(inst_mips[pos].getOperando() == "mul")
				registros[r1].setRegistro(mul(r2,r3));
			else if(inst_mips[pos].getOperando() == "div")
				registros[r1].setRegistro(div(r2,r3));
			showContent_Registros();
			break;

		case 'I':
			if(inst_mips[pos].getOperando() == "addi"){
				r1 = buscarRegistro(inst_mips[pos].getRegistro1());
				r2 = registros[buscarRegistro(inst_mips[pos].getRegistro2())].getRegistro();
				r3 = atoi(inst_mips[pos].getRegistro3().c_str()); //pasar a int
				registros[r1].setRegistro(addi(r2,r3));
			}
			else if(inst_mips[pos].getOperando() == "subi"){
				r1 = buscarRegistro(inst_mips[pos].getRegistro1());
				r2 = registros[buscarRegistro(inst_mips[pos].getRegistro2())].getRegistro();
				r3 = atoi(inst_mips[pos].getRegistro3().c_str()); //pasar a int
				registros[r1].setRegistro(subi(r2,r3));
			}
			else if(inst_mips[pos].getOperando() == "lw")
				lw(inst_mips[pos].getRegistro1(),atoi(inst_mips[pos].getRegistro2().c_str()));
			else if(inst_mips[pos].getOperando() == "sw")
				sw(inst_mips[pos].getRegistro1(),atoi(inst_mips[pos].getRegistro2().c_str()));
			/*else if(inst_mips[pos].getOperando() == "beq"){
				if(beq(registros[buscarRegistro(inst_mips[pos].getRegistro1())].getRegistro(),registros[buscarRegistro(inst_mips[pos].getRegistro2())].getRegistro())){
					//ir al label indicado
					ejecutarInstruccion()
				} 
					//j(pos+1);  recuerda que j es tipo J y beq es tipo I
			}*/
			showContent_Registros();
			break;
		case 'J':
			j(inst_mips[pos].getRegistro3());
			break;
	}
	
}




