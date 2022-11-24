// helper.h

#include "stdafx.h"
#include <vector>
#include <array>

// für die Übergabe von Funktionsparametern
typedef double (*singleParmFnPtr)(double);
typedef double (*doubleParmFnPtr)(double,double);
typedef double (*tripleParmFnPtr)(double,double,double);

// variables array mit den Werten xi, fi
typedef std::vector< std::array<double, 2> > parameterList;
typedef std::vector< double > doubleList;