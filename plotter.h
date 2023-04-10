
void plot(string descriptor, VD &temp, int nCell , double dh)
  {
    // Open plot file
    
    string filename = descriptor + ".plt";    std::fstream f;  f.open(filename.c_str(),std::ios::out);

    // Write to plot file

    iLOOP
      {
	jLOOP
	  {
	    int p = i + (j-1)*nCell;
	    f << i*dh << " " << j*dh << " " << temp[ p ] << endl;
	  }
	f << endl;
      }

    f.close();
  }
