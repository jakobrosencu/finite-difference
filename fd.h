#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include "math.h"
#include <omp.h>  
#include <mpi.h>  
#include <stdio.h>
#include <chrono>
#include <ctime>
#include "stdio.h"
#include "math.h"
#include "string.h"
using std :: string;
using std :: vector;
using std :: stringstream;
using std :: cout;
using std :: endl;


typedef  vector<double>          VD;
typedef  vector<vector<double> > VDD;
typedef  vector<int>             VI;
typedef  vector<vector<int> >    VII;

#define rLOOP  for ( int r = 1 ; r <= nTemp     ; ++r )
#define cLOOP  for ( int c = 1 ; c <= nTemp     ; ++c )
#define iLOOP  for ( int i = 1 ; i <= nCell     ; ++i )
#define jLOOP  for ( int j = 1 ; j <= nCell     ; ++j )


#define rowLOOP  for ( int row = 1 ; row <= nTemp     ; ++row )
#define colLOOP  for ( int col = 1 ; col <= nTemp     ; ++col )





