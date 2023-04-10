#include "fd.h"

#include "solvers.h"
#include "plotter.h"

// =========================================================================
// printSystem and results
// =========================================================================

void printSystem(string message, int nTemp , VDD &A , VD &b)
{
  
  cout << endl;
  cout << "--------------------------------------" << endl;
  cout << message << endl;
  cout << "--------------------------------------" << endl;
  cout << endl;

  rLOOP
    {
      cLOOP
	{
	  printf("%5.2f ", A[r][c] );
	}
      printf("      |    %5.2f ", b[r] );
      cout << endl;
    }
}



void ApplyBCSymmetrically( VDD &A , VD &b , int nTemp , int bcRow, double value)
{

  // Zero out the row where the BC is to be applied
  
  cLOOP A[bcRow][c] = 0.;

  // Place a one on the diagonal and the BC in the right-hand side vector
  
  A[bcRow][bcRow] = 1.;
  b[bcRow]    = value;

  // Apply the BC to all other instances of T[bcRow] in the matrix

  rLOOP
    if ( r != bcRow )
      {
	b[r]        -= A[r][bcRow]*value;
	A[r][bcRow]  = 0.;
      }

}




int main(  int argc, char *argv[] ) 
{

  // Default values for user input
    
  int nCell = 20;   // nCell is for the x- and y-directions

  // Set up grid and linear system information

  double dh          = 1./nCell;        // Size of each cell in each direction (dx and dy)
  int nTemp          = nCell * nCell;   // Total number of points (and number of rows in the linear system)
  int bandwidth      = 5;               // Number of columns in the sparse-matrix format
    
  // Acquire memory for the linear system A*phi = b

  cout << "Acquire memory...\n";
  
  VDD A  ; A.resize  (nTemp+1)  ;  rLOOP A[r].resize(nTemp+1);
  VD b   ; b.resize  (nTemp+1)  ;
  VD temp ; temp.resize(nTemp+1)  ;
  
  // Initialize the linear system and form the initial guess for temp
  
  cout << "Initialize system...\n";

  rLOOP cLOOP A[r][c] = 0.;
    
  rLOOP b  [r] = 0.;

  // Populate the linear system for all interior points using that local row number

  cout << "Form system..." << endl;

  iLOOP
    jLOOP
       {
	 int p = i + (j-1)*nCell;
	  
	 // Interior points

	 if ( i > 1 && i < nCell && j > 1 && j < nCell )
	   {
	     A[p][p]       = -4.;
	     A[p][p-1]     =  1.;
	     A[p][p+1]     =  1.;
	     A[p][p-nCell] =  1.;
	     A[p][p+nCell] =  1.;
	   }
	  
       }

  // Boundary points
  
  iLOOP
    jLOOP
       {
	 int p = i + (j-1)*nCell;
	 
	 if ( i == 1     ) ApplyBCSymmetrically( A, b, nTemp, p ,  40. ) ;
	 if ( i == nCell ) ApplyBCSymmetrically( A, b, nTemp, p ,  40. ) ;
	 if ( j == 1     ) ApplyBCSymmetrically( A, b, nTemp, p , 200. ) ;
	 if ( j == nCell ) ApplyBCSymmetrically( A, b, nTemp, p ,  40. ) ;
       }

  //  printSystem("system",nTemp,A,b);

  // Solve the system using all three methods

  cout << endl;
  cout << "Solve system using Jacobi...\n";
  cout << endl;

  rLOOP temp[r] = 0.;
  Jacobi( A , temp , b , nTemp );
  plot("temp_Jac",temp,nCell,dh);

  cout << endl;
  cout << "Solve system using Gauss-Seidel..." << endl;
  cout << endl;
  
  rLOOP temp[r] = 0.;
  GaussSeidel( A , temp , b , nTemp );
  plot("temp_GS",temp,nCell,dh);
  
  cout << endl;
  cout << "Solve system using Conjugate-Gradient..." << endl;
  cout << endl;
    
  rLOOP temp[r] = 0.;
  CG( A , temp , b , nTemp );
  plot("temp_CG",temp,nCell,dh);

  return 0 ;
}

