#include "stdafx.h"
#include "ableitung.h"

// zentrale differenzenformel für die erste Ableitung
double D2f(singleParmFnPtr f,double x0) {
    int i=0;
    double h=0.1,old_h;
    double y=0, old_y=1;

    // optimale Schrittweite finden
    while( (i<2) || (y > old_y)) {
        old_y = y;
        old_h = h;
        y=(f(x0+h)-f(x0-h) ) / (2*h);
        h *= .5;
        i++;
	}
    h = 2 * old_h;

    // Ableitung an der Stelle x0
    y = ( y=f(x0+h)-f(x0-h) ) / (2*h);
    return y;
}

double h_Extrapolation(singleParmFnPtr f, doubleList h, double x0) {
    double d2f = D2f(f,x0),t;
    int i,k,j,n = h.size();
    matrix D(n);
    memset(D.begin(),0,n*n*sizeof(double));

	for (i=0; i<n; i++) {
        t = 1;
        D[i][0] = d2f * h[i];

        // 2^k berechnen
        for (j=0; j<i; j++)
               t *= 2;

        D[i][0] /= t;
	}

    for (k=1; k<n; k++) {
        t = 1;

        // 2^k berechnen
		for (j=0; j<k; j++)
               t *= 2;

        for (i=0; i<=n-1; i++)
            D[i][k] = D[i+1][k-1] + ( D[i+1][k-1] - D[i][k-1] ) / (t-1);
	}

    return D[0][n-1];
}