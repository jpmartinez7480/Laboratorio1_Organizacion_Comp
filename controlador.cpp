#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "controlador.h"

using namespace std;

const string controlador::regs[32]  = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

const string controlador::operaciones[11] = {"add","sub","mul","div","addi","subi","lw","sw","beq","j"};

bool controlador::exitFile(string nfile)
{
	fstream FILE;
	FILE.open(nfile.c_str(),ios::out);
	if(FILE){
		FILE << "Estado" << setw(14) << "RegDst " << setw(6) << "Jump " << setw(6) << "Branch " << setw(7) << "MemRead "<< setw(7) << "MemToReg " << setw(8) << "ALUOp " << setw(6) << "MemWr " << setw(6) << "ALUSrc " << setw(7) << "RegWrite " << endl;
		for(int i = 0; i < controlSignal; i++){
			if(searchError(i))
				FILE << "Error" << setw(12) << lines_control_sign[i].getRegDst() << setw(6) << lines_control_sign[i].getJump() << setw(6) << lines_control_sign[i].getBranch() << setw(9) << lines_control_sign[i].getMemRead() << setw(8) << lines_control_sign[i].getMemToReg() << setw(8) << lines_control_sign[i].getALUOp() << setw(8) << lines_control_sign[i].getMemWrite() << setw(7) << lines_control_sign[i].getALUSrc() << setw(9) << lines_control_sign[i].getRegWrite() << endl;
			else FILE << "Correcto" << endl;
		}
		FILE.close();
		return 1;
	}
	return 0;
}

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
			if(line!=""){
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
		}
		FILE.close();
		return 1;
	}
}

int controlador::readFile_lineasC(string nfile)
{
	cnt_lineas_control = 0;
	fstream FILE;
	char regDst;
	char jump;
	char branch;
	char memRead;
	char memToReg;
	string ALUOp;
	char memWrite;
	char ALUSrc;
	char regWrite;
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
		FILE.close();
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

void controlador::initControlSign(){
	for(int i = 0; i < 1000; i++)
		lines_control_sign[i] = Control();
}

void controlador::showContent_Registros()
{
	cout << endl;
	cout << "********** Registros **********"<<endl;
	cout << "-------" << "-----" << endl; 
	cout << "|" <<regs[0] << setw(2) << "| " <<  registros[0].getRegistro() << "  |" <<endl;
	cout << "-------" << "-----" << endl;
	for(int i = 1; i < 32; i++){
		cout << "|" <<regs[i] << setw(4) << "| " <<registros[i].getRegistro() << "  |"<< endl;
		cout << "-------" << "-----" << endl;
	}
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
	registros[buscarRegistro(r)].setRegistro(sp[999-pos/4].getValue());
}

void controlador::sw(string r, int pos){
	sp[999-pos/4].setValue(registros[buscarRegistro(r)].getRegistro());
}

bool controlador::beq(int r1, int r2){
	return r1 == r2;
}

void controlador::j(string label)
{
	int i = 0;
	while(inst_mips[i].getOperando()!=label) i++;
	LC = i;
	PC = i+1;
	ejecutarInstruccion(PC);
}

void controlador::compilar()
{
	PC = 0;
	LC = 0;
	controlSignal = 0;
	for(PC; inst_mips[PC].getOperando()!=""; PC++)
		ejecutarInstruccion(PC);
}

void controlador::ejecutarInstruccion(int pos)
{
	int r1;
	int r2;
	int r3;
	//cout << inst_lineas_control[LC].getRegDst() << " " << inst_lineas_control[LC].getJump() << " " << inst_lineas_control[LC].getBranch() << " " << inst_lineas_control[LC].getMemRead() << " " << inst_lineas_control[LC].getMemToReg() << " " << inst_lineas_control[LC].getALUOp() << " "  <<inst_lineas_control[LC].getMemWrite() << " " << inst_lineas_control[LC].getALUSrc() << " " << inst_lineas_control[LC].getRegWrite() << endl;
	//cout << "LC: " << LC << "" <<inst_mips[pos].getOperando()<< endl;
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
			lines_control_sign[controlSignal].controlSign(inst_mips[pos].getTipo(),inst_mips[pos].getOperando());
			compareControlSign(controlSignal);
			controlSignal++;
			LC++;		
			break;

		case 'I':
			if(inst_mips[pos].getOperando() == "addi"){
				r1 = buscarRegistro(inst_mips[pos].getRegistro1());
				r2 = registros[buscarRegistro(inst_mips[pos].getRegistro2())].getRegistro();
				r3 = atoi(inst_mips[pos].getRegistro3().c_str()); //pasar a int
				registros[r1].setRegistro(addi(r2,r3));
				lines_control_sign[controlSignal].controlSign(inst_mips[pos].getTipo(),inst_mips[pos].getOperando());
				compareControlSign(controlSignal);
				controlSignal++;
				LC++;
			}
			else if(inst_mips[pos].getOperando() == "subi"){
				r1 = buscarRegistro(inst_mips[pos].getRegistro1());
				r2 = registros[buscarRegistro(inst_mips[pos].getRegistro2())].getRegistro();
				r3 = atoi(inst_mips[pos].getRegistro3().c_str()); //pasar a int
				registros[r1].setRegistro(subi(r2,r3));
				lines_control_sign[controlSignal].controlSign(inst_mips[pos].getTipo(),inst_mips[pos].getOperando());
				compareControlSign(controlSignal);	
				controlSignal++;
				LC++;
			}
			else if(inst_mips[pos].getOperando() == "lw"){
				lw(inst_mips[pos].getRegistro1(),atoi(inst_mips[pos].getRegistro2().c_str()));
				//showContent_Registros();
				lines_control_sign[controlSignal].controlSign(inst_mips[pos].getTipo(),inst_mips[pos].getOperando());
				compareControlSign(controlSignal);
				controlSignal++;
				LC++;
			}
			else if(inst_mips[pos].getOperando() == "sw"){
				//showContent_Registros();
				sw(inst_mips[pos].getRegistro1(),atoi(inst_mips[pos].getRegistro2().c_str()));
				cout << lines_control_sign[controlSignal].getRegDst() << " " << lines_control_sign[controlSignal].getJump() << " " << lines_control_sign[controlSignal].getBranch() << " " << lines_control_sign[controlSignal].getMemRead() << " " << lines_control_sign[controlSignal].getMemToReg() << " " << lines_control_sign[controlSignal].getALUOp() << " "  <<lines_control_sign[controlSignal].getMemWrite() << " " << lines_control_sign[controlSignal].getALUSrc() << " " << lines_control_sign[controlSignal].getRegWrite() << endl;
				lines_control_sign[controlSignal].controlSign(inst_mips[pos].getTipo(),inst_mips[pos].getOperando());
				cout << "***" << endl;
				cout << inst_lineas_control[LC].getRegDst() << " " << inst_lineas_control[LC].getJump() << " " << inst_lineas_control[LC].getBranch() << " " << inst_lineas_control[LC].getMemRead() << " " << inst_lineas_control[LC].getMemToReg() << " " << inst_lineas_control[LC].getALUOp() << " "  <<inst_lineas_control[LC].getMemWrite() << " " << inst_lineas_control[LC].getALUSrc() << " " << inst_lineas_control[LC].getRegWrite() << endl;
				compareControlSign(controlSignal);
				cout << lines_control_sign[controlSignal].getRegDst() << " " << lines_control_sign[controlSignal].getJump() << " " << lines_control_sign[controlSignal].getBranch() << " " << lines_control_sign[controlSignal].getMemRead() << " " << lines_control_sign[controlSignal].getMemToReg() << " " << lines_control_sign[controlSignal].getALUOp() << " "  <<lines_control_sign[controlSignal].getMemWrite() << " " << lines_control_sign[controlSignal].getALUSrc() << " " << lines_control_sign[controlSignal].getRegWrite() << endl;
				controlSignal++;
				LC++;
			}
			else if(inst_mips[pos].getOperando() == "beq"){
				lines_control_sign[controlSignal].controlSign(inst_mips[pos].getTipo(),inst_mips[pos].getOperando());
				compareControlSign(controlSignal);
				controlSignal++;
				LC++;
				if(beq(registros[buscarRegistro(inst_mips[pos].getRegistro1())].getRegistro(),registros[buscarRegistro(inst_mips[pos].getRegistro2())].getRegistro()))
					j(inst_mips[pos].getRegistro3()+":");
			}	
			break;
		case 'J':
			j(inst_mips[pos].getRegistro3());
			lines_control_sign[controlSignal].controlSign(inst_mips[pos].getTipo(),inst_mips[pos].getOperando());
			compareControlSign(controlSignal);
			controlSignal++;
			break;
	}
}

void controlador::compareControlSign(int pos)
{
	if(inst_lineas_control[LC].getRegDst() == lines_control_sign[pos].getRegDst() || lines_control_sign[pos].getRegDst() == 'x')
		lines_control_sign[pos].setRegDst('-');
	else lines_control_sign[pos].setRegDst(inst_lineas_control[LC].getRegDst());
	if(inst_lineas_control[LC].getJump() == lines_control_sign[pos].getJump() || lines_control_sign[pos].getJump() == 'x')
		lines_control_sign[pos].setJump('-');
	else lines_control_sign[pos].setJump(inst_lineas_control[LC].getJump());
	if(inst_lineas_control[LC].getBranch() == lines_control_sign[pos].getBranch() || lines_control_sign[pos].getBranch() == 'x')
		lines_control_sign[pos].setBranch('-');
	else lines_control_sign[pos].setBranch(inst_lineas_control[LC].getBranch());
	if(inst_lineas_control[LC].getMemRead() == lines_control_sign[pos].getMemRead() || lines_control_sign[pos].getMemRead() == 'x')
		lines_control_sign[pos].setMemRead('-');
	else lines_control_sign[pos].setMemRead(inst_lineas_control[LC].getMemRead());
	if(inst_lineas_control[LC].getMemToReg() == lines_control_sign[pos].getMemToReg() || lines_control_sign[pos].getMemToReg() == 'x')
		lines_control_sign[pos].setMemToReg('-');
	else lines_control_sign[pos].setMemToReg(inst_lineas_control[LC].getMemToReg());
	if(inst_lineas_control[LC].getALUOp() == lines_control_sign[pos].getALUOp() || lines_control_sign[pos].getALUOp() == "x")
		lines_control_sign[pos].setALUOp("-");
	else lines_control_sign[pos].setALUOp(inst_lineas_control[LC].getALUOp());
	if(inst_lineas_control[LC].getMemWrite() == lines_control_sign[pos].getMemWrite() || lines_control_sign[pos].getMemWrite() == 'x')
		lines_control_sign[pos].setMemWrite('-');
	else lines_control_sign[pos].setMemWrite(inst_lineas_control[LC].getMemWrite());
	if(inst_lineas_control[LC].getALUSrc() == lines_control_sign[pos].getALUSrc() || lines_control_sign[pos].getALUSrc() == 'x')
		lines_control_sign[pos].setALUSrc('-');
	else lines_control_sign[pos].setALUSrc(inst_lineas_control[LC].getALUSrc());
	if(inst_lineas_control[LC].getRegWrite() == lines_control_sign[pos].getRegWrite() || lines_control_sign[pos].getRegWrite() == 'x')
		lines_control_sign[pos].setRegWrite('-');
	else lines_control_sign[pos].setRegWrite(inst_lineas_control[LC].getRegWrite());

}

bool controlador::searchError(int pos)
{
	if(lines_control_sign[pos].getRegDst() == '1' || lines_control_sign[pos].getRegDst() == '0' || 
		lines_control_sign[pos].getJump() == '1' || lines_control_sign[pos].getJump() == '0' ||
		lines_control_sign[pos].getBranch() == '1' || lines_control_sign[pos].getBranch() == '0' ||
		lines_control_sign[pos].getMemRead() == '1' || lines_control_sign[pos].getMemRead() == '0' ||
		lines_control_sign[pos].getMemToReg() == '1' || lines_control_sign[pos].getMemToReg() == '0' ||
		lines_control_sign[pos].getALUOp() == "00" || lines_control_sign[pos].getALUOp() == "10" || lines_control_sign[pos].getALUOp() == "01" ||
		lines_control_sign[pos].getMemWrite() == '1' || lines_control_sign[pos].getMemWrite() == '1' ||
		lines_control_sign[pos].getALUSrc() == '1' || lines_control_sign[pos].getALUSrc() == '0'||
		lines_control_sign[pos].getRegWrite() == '1' || lines_control_sign[pos].getRegWrite() == '0')
			return 1;
	else return 0;
}


