// ConsoleApplication1.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#define _USE_MATH_DEFINES
#include <iostream>
#include "ConsoleApplication1.h"
#include "clearscreen.h"
#include <math.h>
#include <sstream>
#include "matrix.h"
#include "gauss.h"
#include "datatypes.h"
#include "interpolation.h"
#include "lgs.h"
#include "ableitung.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Das einzige Anwendungsobjekt

CWinApp theApp;

using namespace std;

vector<string> readargs(char delim);

void berechneESP();
void grenzwert1();
void myflush ( std::istream& in );
void mypause();
void gauss();
void interpolation();
void gaussSeidel();
void ableitung();
void h_extrapol();

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// MFC initialisieren und drucken. Bei Fehlschlag Fehlermeldung aufrufen.
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: Den Fehlercode an Ihre Anforderungen anpassen.
			_tprintf(_T("Schwerwiegender Fehler bei der MFC-Initialisierung\n"));
			nRetCode = 1;
		}
		else
		{
			std::locale::global(std::locale("German_germany"));
			int selection = 0;
			while (selection!=99) {
				ClearScreen();
				cout << "Berechnungen für Numerische Mathematik\n";
				cout << "verfügbare Module: \n\n";
				cout << "  1.  Genauigkeit der Berechnung prüfen\n";
				cout << "  2.  Grenzwert (e^x -1)/x \n";
				cout << "  3.  Gauss Algorithmus \n";
				cout << "  4.  Interpolation \n";
				cout << "  5.  LGS mittels Gauss-Seidel-Verfahren \n";
				cout << "  6.  Ableitung berechnen \n";
				cout << "  7.  Ableitung mittles h-Extrapolation berechnen \n";
				cout << "  99. Programm beenden\n";
				cout << "\n  Bitte wählen Sie ein Modul: ";
				cin >> selection;
				cout << "Sie haben haben " << selection << " gewählt." << endl;
				ClearScreen();
				switch(selection) {
				case 1:
					berechneESP();
					break;
				case 2:
					grenzwert1();
					break;
				case 3:
					gauss();
					break;
				case 4:
					interpolation();
					break;
				case 5:
					gaussSeidel();
					break;
				case 6:
					ableitung();
					break;
				case 7:
					h_extrapol();
					break;
				case 99:
					return 0;
					break;
				}
				myflush(cin);
				mypause();
			}

		}
	}
	else
	{
		// TODO: Den Fehlercode an Ihre Anforderungen anpassen.
		_tprintf(_T("Schwerwiegender Fehler: Fehler bei GetModuleHandle.\n"));
		nRetCode = 1;
	}

	return nRetCode;

}

void myflush ( std::istream& in )
{
  in.ignore (5, '\n' );
  in.clear();
}
void mypause() 
{ 
  std::cout<<"Eingabetaste um fortzufahren . . .";
  std::cin.get();
} 
// liest eingaben ein
vector<string> readargs(char delim) {
	vector<string> ret;

	string input, item;
	getline(cin, input);

	stringstream iss(input);

	while (getline(iss, item, delim)) {
        ret.push_back(item);
    }
	return ret;
}

void berechneESP() {
	int B = 2;
	int n = 0;
	double eps = 1;

	cout << "Ermittle epsilon für doppelte Genauigkeit..." << endl;

	while(1+eps!=1) {
		n++;
		eps = .5 * 1/pow(B,n-1);
		cout << "testing epsilon: " << eps << " ..." << endl;
	}
	n--;
	eps = .5 * 1/pow(B,n-1);
	cout << "ermitteltes epsilon: " << eps << endl;
	cout << "ermitteltes n: " << n << endl;
	cout << "Werte für epsilon (float) laut c++: " <<  numeric_limits<float>::epsilon( ) << endl;
	cout << "Werte für epsilon (double) laut c++: " <<  numeric_limits<double>::epsilon( ) << endl;
}

void grenzwert1() {
	double x = 1;
	double e_rel = 0;
	double e_abs = 0;
	double lim;
	int max_n = 30;
	int n = 0;
	cout << "Berechnung des Grenzwertes für (e^x-1)/x ..." << endl;

	while(n<max_n) {
		lim = (pow(M_E,x) -1)/x;
		e_rel = abs((1 - lim)/x);
		e_abs = abs(1- lim);
		cout << "  ermittelter Wert für x= " << x << " : "<< lim <<endl;
		cout << "    absoluter Fehler :" << e_abs <<endl;
		cout << "    relativer Fehler :" << e_rel <<endl;
		x = pow(10,-n);
		n++;
	}
}

void gauss() {
	matrix m = matrix(3);

	m[0][0] =   4;
	m[0][1] =  -1;
	m[0][2] =  -5;
	m[1][0] = -12;
	m[1][1] =   4;
	m[1][2] =  17;
	m[2][0] =  32;
	m[2][1] = -10;
	m[2][2] = -41;

	cout << "vorher: " << endl;
	m.write();
	Obere_Dreieckmatrix(m);
	cout << "danach: " << endl;
	m.write();
}

void interpolation() {
	vector<string> xi_str;
	int i = 0;
	parameterList pl(0);
	double x,y;

	std::array<double, 2> in;

	myflush(cin);

	cout << "Interpolation \n\n" <<endl;
	cout << "Stützstellen angeben..."<<endl;
	cout << " Bitte geben Sie alle xi, durch leerzeichen getrennt, ein: ";
	xi_str = readargs(' ');
	cout << endl;

	for (std::vector<string>::iterator it = xi_str.begin() ; it != xi_str.end(); ++it) {
		in[0] = ::atof((*it).c_str());
		pl.push_back(in);
	}

	cout << " Bitte geben Sie alle fi, durch leerzeichen getrennt, ein: ";
	xi_str = readargs(' ');
	cout << endl;

	for (std::vector<string>::iterator it = xi_str.begin() ; it != xi_str.end(); ++it) {
		pl[i][1]= ::atof((*it).c_str());
		i++;
	}

	cout << " Geben Sie die Stelle an, an der interpoliert werden soll.\n  X= ";
	cin >> x;
	cout << endl;
	cout << " folgende Werte angegeben:" <<endl;
	cout << " xi: ";
	for (i=0 ; i<pl.size(); i++) {
		cout << pl[i][0] << "\t";
	}
	cout << endl;
	cout << " fi: ";
	for (i=0 ; i<pl.size(); i++) {
		cout << pl[i][1] << "\t";
	}
	cout << endl;
	cout << " X= " << x << endl << endl;
	myflush(cin);
	mypause();

	y= newtonInterpolationAnX(pl,x);

	cout << " P(X=" << x << ") = " << y << endl;

	y= nevilleAitkenInterpolation(pl, x);
	
	cout << " Mittels Neville-Aitken:" << endl;
	cout << " P(X=" << x << ") = " << y << endl;
}

void gaussSeidel() {
	matrix a(3);
	doubleList b(3), x(3);

	a[0][0] = 5;
	a[0][1] = -2;
	a[0][2] = -1;

	a[1][0] = 7;
	a[1][1] = -10;
	a[1][2] = 0;

	a[2][0] = -1;
	a[2][1] = 2;
	a[2][2] = -4;

	b[0] = -4;
	b[1] = -13;
	b[2] = -17;

	int t = gaussSeidelLGS(a,b,x,1e-4);

	if (t>0)
		cout << "Ergebnis = (" << x[0] <<", "<<x[1]<<", "<<x[2]<<" )T nach "<<t<<" Iterationen erreicht."<<endl;
	else
		cout << "Berechnung war fehlerhaft." << endl;
}

double ableitfn(double x) {
	return sin(x);
}
void ableitung() {
	double x0, dy;
	cout << "Ableitung berechnen...\n" << endl;
	cout << "  f(x) = sin(x)" <<endl;
	cout << "  An welcher Stelle soll die Ableitung gebildet werden? x0 =";
	cin >> x0;
	cout << endl;
	dy = D2f(ableitfn,x0);
	cout << "  y'(x0) = " << dy << endl;
}
void h_extrapol() {
	double x0, dy;
	doubleList h(4);
	cout << "Ableitung mittels h-Extrapolation berechnen...\n" << endl;
	cout << "  f(x) = sin(x)" <<endl;
	cout << "  An welcher Stelle soll die Ableitung gebildet werden? x0 =";
	cin >> x0;
	cout << endl;
	h[0] = .1;
	h[1] = .05;
	h[2] = .025;
	h[3] = .0125;
	dy = h_Extrapolation(ableitfn,h,x0);
	cout << "  y'(x0) = " << dy << endl;

}