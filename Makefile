COMPILER := mpicxx

# -----------------------------------------------------
# Make main
# -----------------------------------------------------


omp: fd.cpp fd.h solvers.h plotter.h Makefile
	$(COMPILER) -g fd.cpp -o fd -std=c++11




