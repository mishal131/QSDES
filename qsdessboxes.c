/*********************************************************************************#
#MIT License                                                                      #
#                                                                                 #           
#Copyright (c) 2019 mishal.usm@gmail.com                                          #
#                                                                                 #
#Permission is hereby granted, free of charge, to any person obtaining a copy     #
#of this software and associated documentation files (the "Software"), to deal    #
#in the Software without restriction, including without limitation the rights     #
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        #
#copies of the Software, and to permit persons to whom the Software is            #
#furnished to do so, subject to the following conditions:                         #
#                                                                                 #
#The above copyright notice and this permission notice shall be included in all   #
#copies or substantial portions of the Software.                                  #
#                                                                                 #
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       #
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         #
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      #
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           #
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    #
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    #
#SOFTWARE.                                                                        #
#*********************************************************************************/

#include <quantum.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "qsdessboxes.h"

/***********************************************************************************************
The first approach of the S-Boxes quantum circuits is derived from the work by Denisenko et al.*
“Application of Grover’s Quantum Algorithm for SDES Key Searching”                             *       
***********************************************************************************************/
void Q_SDES_BOX_1(int in3, int in2, int in1, int in0, int out1, int out0, quantum_reg *reg1){
quantum_cnot(in3, out0, reg1);
quantum_toffoli(in0, in1, reg1->width+0, reg1);
quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
quantum_toffoli(in3, reg1->width+1, out0, reg1);
quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
quantum_toffoli(in0, in1, reg1->width+0, reg1);
quantum_toffoli(in0, in2, out0, reg1);
quantum_sigma_x(in0, reg1);
quantum_toffoli(in0, in1, out0, reg1);
quantum_sigma_x(in2, reg1);
quantum_toffoli(in0, in2, out1, reg1);
quantum_sigma_x(in0, reg1);
quantum_toffoli(in0, in1, reg1->width+0, reg1);
quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
quantum_toffoli(in3, reg1->width+1, out1, reg1);
quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
quantum_toffoli(in0, in1, reg1->width+0, reg1);
quantum_sigma_x(in1, reg1);
quantum_toffoli(in0, in1, out1, reg1);
quantum_sigma_x(in3, reg1);
quantum_toffoli(in0, in3, out1, reg1);
quantum_sigma_x(in3, reg1);
quantum_sigma_x(in2, reg1);
quantum_sigma_x(in1, reg1);
}


void Q_SDES_BOX_2(int in7, int in6, int in5, int in4, int out3, int out2, quantum_reg *reg1){
quantum_cnot(in5, out2, reg1);
quantum_toffoli(in4, in6, reg1->width+0, reg1);
quantum_toffoli(in7, reg1->width+0, out3, reg1);
quantum_toffoli(in4, in6, reg1->width+0, reg1);
quantum_sigma_x(in7, reg1);
quantum_toffoli(in4, in7, out2, reg1);
quantum_toffoli(in4, in7, out3, reg1);
quantum_sigma_x(in5, reg1);
quantum_toffoli(in4, in5, reg1->width+0, reg1);
quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
quantum_toffoli(in7, reg1->width+1, out2, reg1);
quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
quantum_toffoli(in4, in5, reg1->width+0, reg1);
quantum_toffoli(in6, in7, out3, reg1);
quantum_sigma_x(in6, reg1);
quantum_sigma_x(in7, reg1);
quantum_toffoli(in6, in7, out2, reg1);
quantum_sigma_x(in4, reg1);
quantum_sigma_x(in5, reg1);
quantum_toffoli(in4, in5, reg1->width+0, reg1);
quantum_toffoli(in7, reg1->width+0, out3, reg1);
quantum_toffoli(in4, in5, reg1->width+0, reg1);
quantum_sigma_x(in4, reg1);
quantum_sigma_x(in6, reg1);
}

/**********************************************************************************************
The end of the first approach.                                                                *
**********************************************************************************************/


/***********************************************************************************************
The second approach of S-Boxes quantum circuits is derived from the work of Almazrooie et al.  *
“Quantum Exhaustive Key Search with Simplified-DES as a Case Study”                            *
***********************************************************************************************/

/*
void Q_SDES_BOX_1(int in0, int in1, int in2, int in3, int out0, int out1, quantum_reg *reg1)
{

// 0001 , 0111 , 1000  => 00
// 0010 , 0111 , 1000  => 00
     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


      //quantum_cnot(reg1->width+2, out0, reg1);

      //quantum_cnot(reg1->width+2, out1, reg1);


     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

/////////////////////////////////////////////////////////////////////////////////////////
// 0000 , 0110 , 1010 , 1101 => 01
// 0000 , 0101 , 1011 , 1100 => 01
     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


      quantum_cnot(reg1->width+2, out0, reg1);

      //quantum_cnot(reg1->width+2, out1, reg1);


     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


/////////////////////////////////////////////////////////////////////////////////////////
// 0011 , 0101 , 1001 , 1111 => 10
// 0011 , 0110 , 1010 , 1111 => 10
     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


      //quantum_cnot(reg1->width+2, out0, reg1);

      quantum_cnot(reg1->width+2, out1, reg1);


     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

////////////////////////////////////////////////////////////////////////////////////
// 0010 , 0100 , 1011 , 1100 , 1110 => 11
// 0001 , 0100 , 1001 , 1101 , 1110 => 11
     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);



      quantum_cnot(reg1->width+2, out0, reg1);

      quantum_cnot(reg1->width+2, out1, reg1);


     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     //quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);



     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     //quantum_sigma_x(in3, reg1);


     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     //quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);


     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

    quantum_toffoli(in0, in1, reg1->width+0, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in3, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in2, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in0, in1, reg1->width+0, reg1);

     //quantum_sigma_x(in0, reg1);
     quantum_sigma_x(in1, reg1);
     quantum_sigma_x(in2, reg1);
     quantum_sigma_x(in3, reg1);

}


void Q_SDES_BOX_2(int in4, int in5, int in6, int in7, int out2, int out3, quantum_reg *reg1)
{

//////////////////////////////////////////////////////////////////////////////////////
// 0010 , 0100 , 1100  => 10
// 0001 , 0100 , 1001  => 10
     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);



      //quantum_cnot(reg1->width+2, out2, reg1);

      quantum_cnot(reg1->width+2, out3, reg1);



     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

/////////////////////////////////////////////////////////////////////////////////////////
// 0011 , 0111 , 1000 , 1111 => 11
// 0110 , 0111 , 1000 , 1111 => 11
     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


      quantum_cnot(reg1->width+2,  out2, reg1);

      quantum_cnot(reg1->width+2,  out3, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

/////////////////////////////////////////////////////////////////////////////////////////

// 0001 , 0110 , 1010 , 1101 => 01
// 0010 , 0101 , 1011 , 1100 => 01
     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


      quantum_cnot(reg1->width+2, out2, reg1);

      //quantum_cnot(reg1->width+2, out3, reg1);


     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

////////////////////////////////////////////////////////////////////////////////////
// 0000 , 0101 , 1001 , 1011 , 1110 => 00
// 0000 , 0011 , 1010 , 1101 , 1110 => 00
     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


      //quantum_cnot(reg1->width+2, out2, reg1);

      //quantum_cnot(reg1->width+2, out3, reg1);


     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     //quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     //quantum_sigma_x(in7, reg1);


     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     //quantum_sigma_x(in4, reg1);
     //quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);


     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

    quantum_toffoli(in4, in5, reg1->width+0, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in7, reg1->width+1, reg1->width+2, reg1);
    quantum_toffoli(in6, reg1->width+0, reg1->width+1, reg1);
    quantum_toffoli(in4, in5, reg1->width+0, reg1);

     quantum_sigma_x(in4, reg1);
     quantum_sigma_x(in5, reg1);
     quantum_sigma_x(in6, reg1);
     quantum_sigma_x(in7, reg1);

}

*/
/**********************************************************************************************
The end of the second approach.                                                               *
**********************************************************************************************/



