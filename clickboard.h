#include	<iostream>
#include	<windows.h>
#define WINVER 0x0500

void copy(char *text){
	const size_t len = strlen(text) + 1;
	HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), text, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}
void paste(){
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
 
    // Press the "Ctrl" key
    ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
 
    // Press the "V" key
    ip.ki.wVk = 'V';
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
 
    // Release the "V" key
    ip.ki.wVk = 'V';
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
 
    // Release the "Ctrl" key
    ip.ki.wVk = VK_CONTROL;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));	
}

void leftClick(){
    INPUT    Input= {0};												// Crear la esturctura de INPUT

    Input.type        = INPUT_MOUSE;									// Decimos que vamos a usar el mouse
    Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;							// Establecemos el evento como  apretar el boton izquierdo
    SendInput( 1, &Input, sizeof(INPUT) );								// Enviamos los cambios de INPUT

    ZeroMemory(&Input,sizeof(INPUT));									// Borramos los datos de estructura INPUT
    Input.type        = INPUT_MOUSE;									// Decimos que vamos a usar el mouse
    Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								// Establecemos el evento como soltar el boton izquierdo
    SendInput( 1, &Input, sizeof(INPUT) );	
}

void getColor(int &red, int &green, int &blue){

    HDC hDC = GetDC(HWND_DESKTOP); //Crea el contexto
    POINT mouse; //Estructura que contiene las coordenadas
    COLORREF rgb; //Estructura de color

    // Values As byte
    BYTE rVal, gVal, bVal;

        GetCursorPos(&mouse); // Obtiene la posicion del cursor
        rgb = GetPixel(hDC, mouse.x, mouse.y); //Obtiene una estructura de color en las posicion del mouse

        //Divide el valor rgb en 3 valores tipo byte
        rVal = GetRValue(rgb);
        gVal = GetGValue(rgb);
        bVal = GetBValue(rgb);

        // Convierte los valores byte a enteros
        red = (int)rVal;
        green = (int)gVal;
        blue = (int)bVal;
	
}
 
 
