#include	<iostream>
#include	<windows.h>
#include	<fstream>
#include    "clickboard.h"



bool salir=true;
bool pause=true;
int r,g,b;

void Exit();
void pausa();
void esperarColor(int x,int y, int _r,int _g,int _b);
bool isColor(int x,int y, int _r,int _g,int _b);
void click(int x,int y);

using namespace std;
// Inicio del Bot
int main(){
	
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)Exit,0,0,0);
	
	ifstream entrada;
	ofstream salida;
	ofstream faltantes;	
	string codigo;
	
	entrada.open("Base.txt",ios::in);
	salida.open("Usados.txt",ios::app);
	faltantes.open("Faltantes.txt",ios::out);
	cout<<"******* INSTRUCCIONES *******"<<endl;
	cout<<"Despues de minimizar"<<endl;
	cout<<"Presione P para iniciar o pausar"<<endl;
	cout<<"Presione X para terminar"<<endl;
	cout<<"Nota: antes de cerrar el Bot debe presionar X"<<endl;
	pausa();
	while(salir){
		entrada>>codigo;			
		if(entrada.eof()){
			break;
		}		
		esperarColor(819,688,0,171,84);
		click(819,688);
		
		esperarColor(364,279,255,249,215);
		click(59,330);	
			
		Sleep(100);
		copy(&codigo[0u]);
		paste();
		
		esperarColor(316,426,70,175,51);
		click(316,426);
		
		do{		
			if(isColor(40,112,17,17,17)){
				salida<<codigo;
				salida<<"\tMalo";
				salida<<endl;
				click(998,6);
				break;
			}else if(isColor(48,128,231,59,48)){
				click(998,6);
				break;
			}else if(isColor(52,229,70,175,51)){
				salida<<codigo;
				salida<<"\tBueno";
				salida<<endl;
				click(169,196);
				
				esperarColor(544,534,0,171,84);
				click(544,534);
				break;
			}
		}while(salir);					
	}
	salida.close();
	
	while(true){
		entrada>>codigo;	
		if(entrada.eof()){
			break;
		}		
		faltantes<<codigo;
		faltantes<<endl;	
	}
	faltantes.close();
	entrada.close();
	system("DEL Base.txt");
	system("REN Faltantes.txt Base.txt");
	return 0;
}
// Fin del Bot


void Exit(){
	while(true){
		if(GetAsyncKeyState(VkKeyScan('x')) and true){
			salir=!salir;
		}
		if(GetAsyncKeyState(VkKeyScan('p')) and true){
			pause=!pause;
		}
		Sleep(500);
	}
}

void pausa(){
	while(pause){
		if(!salir){
			break;
		}
		Sleep(500);	
	}
}

void esperarColor(int x,int y, int _r,int _g,int _b){
	pausa();
	if(salir){
		SetCursorPos(x,y);
		Sleep(100);	
		getColor(r,g,b);
		while(!(r==_r and g==_g and b==_b)){
			if(!salir){
				break;
			}
			pausa();
			SetCursorPos(x,y);
			Sleep(100);				
			getColor(r,g,b);
		}		
	}	
}

bool isColor(int x,int y, int _r,int _g,int _b){
	pausa();
	if(salir){
		SetCursorPos(x,y);
		Sleep(100);	
		getColor(r,g,b);
		if(r==_r and g==_g and b==_b){
			return true;
		}			
	}	
	return false;
}

void click(int x,int y){
	pausa();
	if(salir){
		SetCursorPos(x,y);
		Sleep(100);	
		leftClick();		
	}	
}
