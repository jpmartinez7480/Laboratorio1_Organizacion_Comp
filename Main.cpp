#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

#include "controlador.cpp"

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::string;
using std::stringstream;

 
int main()
{
	string pause;
	string cad;
	int ans;
	string file_mips = "";
	string file_control = "";
	string file_salida;
	controlador c;
	do
	{
		system("cls");
		cout << endl;
		cout << "****** ORGANIZACION DE COMPUTADORES ******" << endl;
		cout << "        ****** laboratorio 1 ******" << endl;
		cout << "Menu de opciones" << endl;
		cout << "1.Leer archivo de instrucciones Mips" << endl;
		cout << "2.Leer archivo de lineas de control" << endl;
		cout << "3.Comprobar" << endl;
		cout << "4.Ver datos leidos del archivo mips" << endl;
		cout << "5.Ver datos leidos del archivo lineas de control" << endl;
		cout << "6.Salir" << endl;
		cout << "Ingrese opcion: ";
		getline(cin,cad);
		stringstream mystream(cad);
		string msje = mystream >> ans ? "entrada valida\n" : "entrada incorrecta\n";
		cout << msje;
		switch(ans)
		{
			case 1:
				system("cls");
				cout << "*** Lectura de archivo mips ***" << endl;
				cout << "Ingrese el nombre del archivo junto a su extension (ejemplo.ext): ";
				cin >>  file_mips;
				if(c.readFile_Mips(file_mips) == 1) 
					cout << "La lectura se realizo satisfactoriamente" << endl;
				else{
					cout << "La lectura de archivo no pudo ser completada. Revise el archivo" << endl;
					file_mips = "";
				}
				cout << "Presione cualquier tecla para continuar...";
				cin >> pause;
				break;
			case 2:
				system("cls");
				cout << "*** Lectura de archivo lineas de control ***" << endl;
				cout << "Ingrese el nombre del archivo junto a su extension (ejemplo.ext): ";
				cin >> file_control;
				if(c.readFile_lineasC(file_control) == 1)
					cout << "La lectura se realizo satisfactoriamente" << endl;
				else{
					cout << "La lectura de archivo no pudo ser completada. Revise el archivo" << endl;
					file_control = "";
				}
				cout << "Presione cualquier tecla para continuar...";
				cin >> pause;
				break;
			case 3:
				system("cls");
				if(file_mips != "" & file_control != ""){
					cout << "Ingrese nombre del archivo de salida junto a su extension: ";
					cin >> file_salida;	
					c.initRegisters();
					c.showContent_Registros();
					c.compilar();
					cout << "Presione una tecla para continuar...";
					cin >> pause;
					//llamar a la funcion
				}
				else if(file_mips == "" && file_control != ""){
					cout << "Falta leer el archivo de sentencias Mips" << endl;
					cout << "Presione una tecla para continuar...";
					cin >> pause;
				}
				else if(file_mips != "" && file_control == ""){
					cout << "Falta leer el archivo de lineas de control" << endl;
					cout << "Presione una tecla para continuar...";
					cin >> pause;
				}
				break;
			case 4:
				if(file_mips != "")
					c.showContent_Mips();
				else{
					cout << "Falta leer el archivo. Presione una tecla para continuar...";
					cin >> pause;
				}
				break;
			case 5:
				if(file_control != "")
					c.showContent_lineasC();
				else{
					cout << "Falta leer el archivo. Presione una tecla para continuar....";
					cin >> pause;
				}
				break;
			case 6:
				cout << "Gracias por su preferencia" << endl;
				break;
			default:
				cout << "Ingrese una operacion valida" << endl;
		}
		if(ans > 0 && ans <=5) ans = 0;	
	}while(ans!=6);

	return 0;
}