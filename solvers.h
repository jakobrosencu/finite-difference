
void Jacobi(VDD &A , VD &temp , VD b , int nTemp )
  {
    int converged;
    int iter = 0;
    int max_iter = nTemp*50;
    double newval;
    double cur_delta = 0.;
    double max_delta = 0.;
    double tol = 1.e-04;

    VD tempNew; tempNew.resize(temp.size());

    rLOOP tempNew[r] = 0.;
    
    // ====================================================
    // Begin Iterations
    // ====================================================
    
    converged = 0;
    
    while ( converged == 0 )
      {
	// ----------------------------------------------
	// Convergence
	// ----------------------------------------------
	
	if ( ++iter > max_iter )
	  {
	    cout << "Jacobi: max_iter of " << max_iter << " reached.\n";
	    return;
	  }

	max_delta    = 0.;
	converged = 1;

	// ----------------------------------------------
	// One Jacobi Iteration
	// ----------------------------------------------
	
	rLOOP
	  {
	    
	    // Compute new guess for row r

	    newval = b[r];
	    cLOOP  if ( r != c ) newval -=  A[r][c] * temp[c];
	    newval /= A[r][r];

	    // Convergence check

	    cur_delta  = fabs(temp[r] - newval);

	    if ( cur_delta > tol ) converged = 0;

	    // Record new value in solution

	    tempNew[r] = newval;

	  }

	rLOOP temp[r] = tempNew[r];

	// ----------------------------------------------
	// (5) Gather convergence information from PEs
	// ----------------------------------------------

	if ( converged == 1 )
	  {
	    cout << "Jacobi/GS converged in " << iter << " iterations" << endl;
	    return;
	  }
	
      }

  }




void GaussSeidel(VDD &A , VD &temp , VD b , int nTemp )
  {

    // TO-DO:
    // Paste Jacobi method here and make one simple change that
    // turns the method into the Gauss-Seidle method.

  }




//  ==
//  ||
//  ||
//  || C O N J U G A T E   G R A D I E N T   R O U T I N E S
//  ||
//  ||
//  ==

//  ==
//  ||
//  || Utility routine: Dot
//  ||
//  ==

double Dot(VD &vec1, VD &vec2 , int nTemp)
{
  double  sum  = 0.;
  rowLOOP sum += TO-DO
  return sum;
}


//  ==
//  ||
//  || Utility routine: MatVecProd
//  ||
//  || Computes the matrix-vector product, prod = A*p.
//  ||
//  ==

void MatVecProd(VDD &A , VD &p , VD &prod , int nTemp )
{
  rowLOOP
    {
      prod[row] = 0.;
      colLOOP  prod[row] += TO-DO
    }
}


//  ==
//  ||
//  || Utility routine: Residual
//  ||
//  || Computes the residual, residual = b - A*temp
//  ||
//  ==

void Residual(VD &residual , VD &temp , VDD &A , VD &b, int nTemp )
{

  MatVecProd( A , temp , residual, nTemp);
  
  rowLOOP residual[row] = b[row] - residual[row];
  
}



// ==
// ||
// || CG (Conjugate Gradient)
// ||
// || Solves the system using Conjugate-Gradient iteration.
// ||
// || See https://en.wikipedia.org/wiki/Conjugate_gradient_method
// ||
// ==

void CG(VDD &A , VD &temp , VD &b , int nTemp)
{

  VD rnew; rnew.resize(nTemp + 1);
  VD r;       r.resize(nTemp + 1);
  VD p;       p.resize(nTemp + 1);
  VD Ap;     Ap.resize(nTemp + 1);
  
  double p_dot_Ap;         // Stores matrix-vector product
  double r_dot_r;          // Stores r dot r
  double rnew_dot_rnew;    // Stores rnew dot rnew
  double alpha;            // Alpha in the above-referenced algorithm
  double beta;             // Beta   "  "   "       "          "
  double cur_delta;
  double tol           = 1.e-04;
  int iter             = 0;
  int max_iter         = nTemp * 4;
  int converged;

  // (1) Initial residual, r, and r dot r for CG algorithm

  Residual(r,temp,A,b,nTemp);

  // (2) Initial search direction = the initial residual

  rowLOOP p[row] = r[row];

  r_dot_r  = Dot(r,r,nTemp);         
      
  // (3) CG Iterations

  converged = 0;
  
  while ( converged == 0  && ++iter <= max_iter)
    {
      MatVecProd(A,p,Ap,nTemp);    
      p_dot_Ap = Dot(p,Ap,nTemp);  
      alpha    = TO-DO


      // Update solution
      
      rowLOOP temp [row] = temp[row] + TO-DO *  p[row];

      // Update residual
      
      rowLOOP rnew [row] = r   [row] - TO-DO * Ap[row];

      // Compute beta

      rnew_dot_rnew = Dot(rnew,rnew,nTemp);
      beta          = TO-DO

      // Update search direction
      
      rowLOOP p[row] = rnew[row] + TO-DO*p[row];

      // New residual now becomes the old residual
      
      rowLOOP r[row] = rnew[row];
      r_dot_r    = rnew_dot_rnew;

      // Covnergence test #1

      rowLOOP
	{
	  cur_delta  = fabs(alpha * p[row]);
	  if ( cur_delta > tol ) converged = 0;
	}

      // Convergence test #2

      if ( fabs(r_dot_r) < 1.e-10)
	converged = 1;
      else
	converged = 0;
    }


    if ( converged == 1 ) cout << "CG converged in " << iter << " iterations.\n" ;
    if ( converged == 0 ) cout << "CG failed to converge after " << iter << " iterations.\n" ;

}



