// gauss.cpp

#include "stdafx.h"
#include "gauss.h"
#include "matrix.h"

bool Obere_Dreieckmatrix(matrix& a) {
	int i;
	int j;
	int k;
	int lowest = 0;
	double reg_check = 0;
	double lambda;
	int n = a.size();
	double* buffer = new double[n];
	
	int buffer_s = n*sizeof(double);
	// Zeilentausch

	for (i=0; i<n-1; i++) {
		if (a[i][i] == 0) {
			lowest = i+1;
			for (j=i+1; j<n; j++) {
				reg_check += a[j][i];
				if ((a[j][i] != 0) && (a[j][i] < a[lowest][i]))
					lowest = j;
			}
			// Zeile a[i] speichern
			memcpy(buffer,a[i],buffer_s);

			// Zeile a[j] nach a[i]
			memcpy(a[i],a[lowest],buffer_s);
			
			// puffer nach a[j]
			memcpy(a[lowest],buffer,buffer_s);
			
		}
	}
	delete[] buffer;

	// eliminieren
	for (i=0; i<n-1; i++) {
		for (j=i+1; j<n; j++) {
			lambda = a[j][i] / a[i][i];
			for (k = 0; k< n; k++) a[j][k] = a[j][k] - lambda*a[i][k];
		}
	}
	
	return true;
}
