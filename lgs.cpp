#include "stdafx.h"
#include "lgs.h"
#include "matrix.h"
#include "datatypes.h"

const int MAX_ITER = 500;

bool istDiagonaldominant(matrix &m) {
	int n = m.size();
	double sum = 0;
	int i, j;

	for (i=0; i<n; i++) {
		sum = 0;
		for (j=0; j<n; j++)
			if (j!=i) sum += abs(m[i][j]);
		// nicht diagonaldominant!
		if (sum > abs(m[i][i])) return false;
	}

	return true;
}

int gaussSeidelLGS(matrix &a, doubleList &b, doubleList &x, double minError) {
	// abbrechen, wenn die Matrix nicht diagonal dominant ist
	if (!istDiagonaldominant(a)) return -1;

	int n = a.size(), k=0, i=0, m=0;
	double sum_a, sum_b, e;

	if (b.size()<n) return -2;

	// Lösungsvektor
	std::vector< std::vector<double> > X(2,std::vector<double>(n,0));

	bool abbruch = false;

	while(!abbruch) {
		for (k=0; k<n; k++) {
			sum_a = 0;
			sum_b = 0;
			e = 0;

			for (i=0; i<=k-1; i++)
				sum_a += a[k][i] * X[1][i];
			for (i=k+1; i<n; i++)
				sum_b += a[k][i] * X[0][i];

			// X^(m+1) nach X[1] und X^m nach X[0]
			X[1][k] = (b[k]-sum_a-sum_b)/a[k][k];
		}
		for (i=0; i<n; i++) {
			double t = abs( X[0][i] - X[1][i]);
			e = max(e,t);
		}
		// prüfen auf Abbruch
		if ( (e <= minError) || (m >= MAX_ITER) ) {
			abbruch = true;
		}
		X[0] = X[1];
		m++;
	}

	x = X[1];
	return m;
}