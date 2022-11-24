//  matrix.h  

#ifndef matrix_h
#define matrix_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <algorithm>

using namespace std;


#define index(i,j) ((i)*n+j)	//  indexing


class matrix {

public:
  matrix(int __n=0) : n(__n) { if (n) a=new double[n*n]; }
  matrix(const char *filename);
  matrix(const matrix& m) : n(0) { *this=m; }
  ~matrix() { if (n) delete[] a; }
  
  double       *operator[] (int i)       { return a+i*n; }
  const double *operator[] (int i) const { return a+i*n; }
  double& operator() (int i, int j)       { return a[index(i,j)]; }
  double  operator() (int i, int j) const { return a[index(i,j)]; }
    
  const matrix& operator= (const matrix& m);
  
  const matrix& operator+= (const matrix& m);
  const matrix& operator-= (const matrix& m);
  const matrix& operator*= (const matrix& m);
 
 
  matrix operator+ (const matrix& m) const
    { matrix dum(*this); return dum+=m; }
  matrix operator- (const matrix& m) const
    { matrix dum(*this); return dum-=m; }  
  matrix operator* (const matrix& m) const
    { matrix dum(*this); return dum*=m; }
  
  double *begin() const { return a; }
  double *end()   const { return a+n*n; }
  
  int size() const { return n; }
  
  void write() const;	//  write matrix to cout
  
  
private:
  int n;		//  order of matrix
  double *a;		//  matrix elements
};


matrix transpose(const matrix& a);	//  transpose matrix
matrix diagonal(int n);			//  diagonal matrix


#endif
