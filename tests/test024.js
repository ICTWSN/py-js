/* Mandelbrot! */

X1 =  -2.0;  
Y1 =  -2.0; 
X2 =   2.0; 
Y2 =   2.0; 
PX = 32;
PY = 32;


lines = [];
for (y=0;y<PY;y++) {
  line="";
  for (x=0;x<PX;x++) {
    Xr=0;
    Xi=0; 
    Cr=X1+((X2-X1)*x/PX);
    Ci=Y1+((Y2-Y1)*y/PY);
    iterations=0;
    while ((iterations<32) && ((Xr*Xr+Xi*Xi)<4)) {
      t=Xr*Xr - Xi*Xi + Cr;
      Xi=2*Xr*Xi+Ci;          
      Xr=t;        
      iterations++;
    }
    if (iterations&1)
	line += "*";
    else
        line += " ";    
   }
   lines[y] = line;
  }

result =   
lines[0] == "********************************" &&
lines[1] == "***********           **********" &&
lines[2] == "*********               ********" &&
lines[3] == "*******                   ******" &&
lines[4] == "******                     *****" &&
lines[5] == "*****                       ****" &&
lines[6] == "****     *******             ***" &&
lines[7] == "***   ******* ** **           **" &&
lines[8] == "***  ******  * *   *          **" &&
lines[9] == "** *******   ** **  **         *" &&
lines[10]== "** ******  * *   ** **         *" &&
lines[11]== "* *****  ***      ** **         " &&
lines[12]== "****** ***         *****        " &&
lines[13]== "***  * * *         ** **        " &&
lines[14]== "*   * *   *         * **        " &&
lines[15]== "*   ***            ** **        " &&
lines[16]== "*                  ** **        " &&
lines[17]== "*   ***            ** **        " &&
lines[18]== "*   * *   *         * **        " &&
lines[19]== "***  * * *         ** **        " &&
lines[20]== "****** ***         *****        " &&
lines[21]== "* *****  ***      ** **         " &&
lines[22]== "** ******  * *   ** **         *" &&
lines[23]== "** *******   ** **  **         *" &&
lines[24]== "***  ******  * *   *          **" &&
lines[25]== "***   ******* ** **           **" &&
lines[26]== "****     *******             ***" &&
lines[27]== "*****                       ****" &&
lines[28]== "******                     *****" &&
lines[29]== "*******                   ******" &&
lines[30]== "*********               ********" &&
lines[31]== "***********           **********";
