// interpolation.cpp

#include "stdafx.h"
#include <vector>
#include "datatypes.h"

doubleList dividierteDifferenzen(parameterList &params) {
	int i,j,k;
	// Anzahl der Parameter ermitteln
	int n = params.size();
	// Liste n x (n-1)
	std::vector< std::vector<double> > f(n,std::vector<double>(n,0));

	std::vector< double > x(n);

	doubleList p(n);

	for (j=0; j<n; j++) {
		x[j] = params[j][0];
		f[0][j] = params[j][1];
	}

	for (k = 1; k < n; k++)
		for (i = 0; i < n-k; i++) {
			f[k][i] = ( f[k-1][i+1] - f[k-1][i] ) / (x[i+k] - x[i]);
		}

    for (j=0 ; j < n; j++)
		p[j] = f[j][0];

	return p;
}
//  wert an der stelle x durch newton-interpolation bestimmen
double newtonInterpolationAnX(parameterList &params, double x) {
	doubleList a = dividierteDifferenzen(params);
	int n = a.size(), k;

	double *r = new double[n];
	double sum = 0;

	r[n-1] = a[n-1];

	for (k=n-2; k>=0; k--) {
		r[k] = r[k+1] * ( x - params[k][0] ) + a[k];
	}
	sum = r[0];
	delete[] r;
	return sum;
}
// wert an der Stelle x durch Neville-Aitken-Schema
double nevilleAitkenInterpolation(parameterList &params, double x) {
	int n = params.size(), i, k;
	std::vector< std::vector<double> > p(n,std::vector<double>(n,0));

	for (i=0; i<n; i++)
		p[i][0] = params[i][1];

	for (k=1; k<n; k++)
		for (i=0; i<n-k; i++)
			p[i][k] = p[i+1][k-1]+(params[i+k][0]-x)/(params[i+k][0]-params[i][0])*(p[i][k-1]-p[i+1][k-1]);

	return p[0][n-1];
}