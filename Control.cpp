#include "Control.h"

void Control::setRegDst(bool rd){
	regDst = rd;
}

void Control::setJump(bool j){
	jump = j;
}

void Control::setBranch(bool b){
	branch = b;
}

void Control::setMemRead(bool mr){
	memRead = mr;
}

void Control::setMemToReg(bool mtr){
	memToReg = mtr;
}

void Control::setALUOp(string aop){
	ALUOp = aop;
}

void Control::setMemWrite(bool mw){
	memWrite = mw;
}

void Control::setALUSrc(bool as){
	ALUSrc = as;
}

void Control::setRegWrite(bool rw){
	regWrite = rw;
}

bool Control::getRegDst(){
	return regDst;
}

bool Control::getJump(){
	return jump;
}

bool Control::getBranch(){
	return branch;
}

bool Control::getMemRead(){
	return memRead;
}

bool Control::getMemToReg(){
	return memToReg;
}

string Control::getALUOp(){
	return ALUOp;
}

bool Control::getMemWrite(){
	return memWrite;
}

bool Control::getALUSrc(){
	return ALUSrc;
}

bool Control::getRegWrite(){
	return regWrite;
}

void Control::establecerControl(bool rd, bool j, bool b, bool mr, bool mtr, string aop, bool mw, bool as, bool rw){
	setRegDst(rd);
	setJump(j);
	setBranch(b);
	setMemRead(mr);
	setMemToReg(mtr);
	setALUOp(aop);
	setMemWrite(mw);
	setALUSrc(as);
	setRegWrite(rw);
}