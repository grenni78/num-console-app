
#include "stdafx.h"
#include "matrix.h"


matrix::matrix(const char *filename)
{
  ifstream finp(filename);
  
  finp >> n; a=new double[n*n];
  
  for (int i=0; i<n; i++)
  for (int j=0; j<n; j++)
    finp >> a[index(i,j)];
}

  
const matrix& matrix::operator= (const matrix& m)
{
  if (n) delete[] a; 
 
  n=m.size(); a=new double[n*n]; 
  copy(m.begin(),m.end(),a);
  
  return *this;
}
 
  
const matrix& matrix::operator+= (const matrix& m)
{
  assert( n==m.size() );
  
  for (int i=0; i<n*n; i++) a[i]+=m.a[i]; return *this;
}


const matrix& matrix::operator-= (const matrix& m)
{
  assert( n==m.size() );
  
  for (int i=0; i<n*n; i++) a[i]-=m.a[i]; return *this;
}


const matrix& matrix::operator*= (const matrix& m)
{
  assert( n==m.size() );
  
  matrix copy(*this); 
  fill(begin(),end(),0.);
  
  for (int i=0; i<n; i++)
  for (int j=0; j<n; j++)
  for (int k=0; k<n; k++)
    a[index(i,j)]+=copy(i,k)*m(k,j);
    
  return *this;
} 
 
  
void matrix::write() const
{
  for (int i=0; i<n; i++, cout << endl)
  for (int j=0; j<n; j++)
    cout << setw(10) << a[index(i,j)] << " ";
  
  
}
  

matrix transpose(const matrix& a)
{
  matrix at(a.size());
  
  for (int i=0; i<a.size(); i++)
  for (int j=0; j<a.size(); j++)
    at(i,j)=a(j,i);
    
  return at;
}


matrix diagonal(int n)
{
  matrix e(n); 
  
  fill(e.begin(),e.end(),0.);
  for (int i=0; i<n; i++) e(i,i)=1;
  
  return e;
}
