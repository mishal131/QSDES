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


#include "qsdestest.h"
#include "qsdessboxes.h"

void printing(char *stage, int measured, quantum_reg  *reg1){

 //quantum_print_qureg(reg1);
int j;

int  printbinary[8];
for(j=reg1->width-1;j>=0;j--)
	{
	if(measured & 1)
		printbinary[j] = 1;
	else
		printbinary[j] = 0;
	measured >>= 1;
	}
printf("%s", stage);
printf("|");
for(j=0;j<reg1->width;j++) 
	printf("%i", printbinary[j]);	
printf("> with probability of %f\n\n", quantum_prob(reg1->node[0].amplitude));
}


void test(char *key, char *plaintext, int details){
quantum_reg  reg1 = quantum_new_qureg(0, 8); 
int j;
int measured;
printf("The input plaintext is: ");
for(j=0;j<8;j++) 
	printf("%c", plaintext[j]);
printf("\n");
printf("The input key is: ");
for(j=0;j<10;j++) 
	printf("%c", key[j]);
printf("\n");

//KEY
if(key[9]=='1')
	quantum_sigma_x(k10, &reg1);    
if(key[8]=='1')
	quantum_sigma_x(k9, &reg1);
if(key[7]=='1')
	quantum_sigma_x(k8, &reg1);
if(key[6]=='1')
	quantum_sigma_x(k7, &reg1);
if(key[5]=='1')
	quantum_sigma_x(k6, &reg1);
if(key[4]=='1')
	quantum_sigma_x(k5, &reg1);
if(key[3]=='1')
	quantum_sigma_x(k4, &reg1);
if(key[2]=='1')
	quantum_sigma_x(k3, &reg1);
if(key[1]=='1')
	quantum_sigma_x(k2, &reg1);
if(key[0]=='1')
	quantum_sigma_x(k1, &reg1);


//BLAINTEXT
if(plaintext[7]=='1')
	quantum_sigma_x(p8, &reg1); 
if(plaintext[6]=='1')   
	quantum_sigma_x(p7, &reg1);
if(plaintext[5]=='1')
	quantum_sigma_x(p6, &reg1);
if(plaintext[4]=='1')
	quantum_sigma_x(p5, &reg1);
if(plaintext[3]=='1')
	quantum_sigma_x(p4, &reg1);
if(plaintext[2]=='1')
	quantum_sigma_x(p3, &reg1);
if(plaintext[1]=='1')
	quantum_sigma_x(p2, &reg1);
if(plaintext[0]=='1')
	quantum_sigma_x(p1, &reg1);

quantum_cnot(p7, k1,  &reg1);
quantum_cnot(p4, k7,  &reg1);
quantum_cnot(p8, k9,  &reg1);
quantum_cnot(p5, k4,  &reg1);

quantum_cnot(p8, k8,  &reg1);
quantum_cnot(p5, k3,  &reg1);
quantum_cnot(p7, k10,  &reg1);
quantum_cnot(p4,k6,  &reg1);

if(details){
	quantum_cnot(7, p2,  &reg1); quantum_cnot(p2, 7,  &reg1); quantum_cnot(7, p2,  &reg1);
	quantum_cnot(6, p6,  &reg1); quantum_cnot(p6, 6,  &reg1); quantum_cnot(6, p6,  &reg1);
	quantum_cnot(5, p3,  &reg1); quantum_cnot(p3, 5,  &reg1); quantum_cnot(5, p3,  &reg1);
	quantum_cnot(4, p1,  &reg1); quantum_cnot(p1, 4,  &reg1); quantum_cnot(4, p1,  &reg1);
	quantum_cnot(3, p4,  &reg1); quantum_cnot(p4, 3,  &reg1); quantum_cnot(3, p4,  &reg1);
	quantum_cnot(2, p8,  &reg1); quantum_cnot(p8, 2,  &reg1); quantum_cnot(2, p8,  &reg1);
	quantum_cnot(1, p5,  &reg1); quantum_cnot(p5, 1,  &reg1); quantum_cnot(1, p5,  &reg1);
	quantum_cnot(0, p7,  &reg1); quantum_cnot(p7, 0,  &reg1); quantum_cnot(0, p7,  &reg1);

	measured = quantum_measure(reg1);
	printing("The output from (IP) is the state ", measured, &reg1);

	quantum_cnot(7, p2,  &reg1); quantum_cnot(p2, 7,  &reg1); quantum_cnot(7, p2,  &reg1);
	quantum_cnot(6, p6,  &reg1); quantum_cnot(p6, 6,  &reg1); quantum_cnot(6, p6,  &reg1);
	quantum_cnot(5, p3,  &reg1); quantum_cnot(p3, 5,  &reg1); quantum_cnot(5, p3,  &reg1);
	quantum_cnot(4, p1,  &reg1); quantum_cnot(p1, 4,  &reg1); quantum_cnot(4, p1,  &reg1);
	quantum_cnot(3, p4,  &reg1); quantum_cnot(p4, 3,  &reg1); quantum_cnot(3, p4,  &reg1);
	quantum_cnot(2, p8,  &reg1); quantum_cnot(p8, 2,  &reg1); quantum_cnot(2, p8,  &reg1);
	quantum_cnot(1, p5,  &reg1); quantum_cnot(p5, 1,  &reg1); quantum_cnot(1, p5,  &reg1);
	quantum_cnot(0, p7,  &reg1); quantum_cnot(p7, 0,  &reg1); quantum_cnot(0, p7,  &reg1);
	}


if(details){
	quantum_cnot(7, k1,  &reg1); quantum_cnot(k1, 7,  &reg1); quantum_cnot(7, k1,  &reg1);
	quantum_cnot(6, k7,  &reg1); quantum_cnot(k7, 6,  &reg1); quantum_cnot(6, k7,  &reg1);
	quantum_cnot(5, k9,  &reg1); quantum_cnot(k9, 5,  &reg1); quantum_cnot(5, k9,  &reg1);
	quantum_cnot(4, k4,  &reg1); quantum_cnot(k4, 4,  &reg1); quantum_cnot(4, k4,  &reg1);
	quantum_cnot(3, k8,  &reg1); quantum_cnot(k8, 3,  &reg1); quantum_cnot(3, k8,  &reg1);
	quantum_cnot(2, k3,  &reg1); quantum_cnot(k3, 2,  &reg1); quantum_cnot(2, k3,  &reg1);
	quantum_cnot(1, k10,  &reg1); quantum_cnot(k10, 1,  &reg1); quantum_cnot(1, k10,  &reg1);
	quantum_cnot(0, k6,  &reg1); quantum_cnot(k6, 0,  &reg1); quantum_cnot(0, k6,  &reg1);

	measured = quantum_measure(reg1);
	printing("The output from (XOR1) is the state ", measured, &reg1);

	quantum_cnot(7, k1,  &reg1); quantum_cnot(k1, 7,  &reg1); quantum_cnot(7, k1,  &reg1);
	quantum_cnot(6, k7,  &reg1); quantum_cnot(k7, 6,  &reg1); quantum_cnot(6, k7,  &reg1);
	quantum_cnot(5, k9,  &reg1); quantum_cnot(k9, 5,  &reg1); quantum_cnot(5, k9,  &reg1);
	quantum_cnot(4, k4,  &reg1); quantum_cnot(k4, 4,  &reg1); quantum_cnot(4, k4,  &reg1);
	quantum_cnot(3, k8,  &reg1); quantum_cnot(k8, 3,  &reg1); quantum_cnot(3, k8,  &reg1);
	quantum_cnot(2, k3,  &reg1); quantum_cnot(k3, 2,  &reg1); quantum_cnot(2, k3,  &reg1);
	quantum_cnot(1, k10,  &reg1); quantum_cnot(k10, 1,  &reg1); quantum_cnot(1, k10,  &reg1);
	quantum_cnot(0, k6,  &reg1); quantum_cnot(k6, 0,  &reg1); quantum_cnot(0, k6,  &reg1);
	}
////////////////////////////////////////////////////////////////////////////////
  Q_SDES_BOX_1(k4, k9, k7, k1, p2, p1, &reg1);
  Q_SDES_BOX_2(k6, k10, k3, k8, p6, p3, &reg1);
////////////////////////////////////////////////////////////////////////////////

if(details){
	quantum_cnot(7, p2,  &reg1); quantum_cnot(p2, 7,  &reg1); quantum_cnot(7, p2,  &reg1);
	quantum_cnot(6, p6,  &reg1); quantum_cnot(p6, 6,  &reg1); quantum_cnot(6, p6,  &reg1);
	quantum_cnot(5, p3,  &reg1); quantum_cnot(p3, 5,  &reg1); quantum_cnot(5, p3,  &reg1);
	quantum_cnot(4, p1,  &reg1); quantum_cnot(p1, 4,  &reg1); quantum_cnot(4, p1,  &reg1);
	quantum_cnot(3, p4,  &reg1); quantum_cnot(p4, 3,  &reg1); quantum_cnot(3, p4,  &reg1);
	quantum_cnot(2, p8,  &reg1); quantum_cnot(p8, 2,  &reg1); quantum_cnot(2, p8,  &reg1);
	quantum_cnot(1, p5,  &reg1); quantum_cnot(p5, 1,  &reg1); quantum_cnot(1, p5,  &reg1);
	quantum_cnot(0, p7,  &reg1); quantum_cnot(p7, 0,  &reg1); quantum_cnot(0, p7,  &reg1);

	measured = quantum_measure(reg1);
	printing("The output from (P4-R1) is the state ", measured, &reg1);

	quantum_cnot(7, p2,  &reg1); quantum_cnot(p2, 7,  &reg1); quantum_cnot(7, p2,  &reg1);
	quantum_cnot(6, p6,  &reg1); quantum_cnot(p6, 6,  &reg1); quantum_cnot(6, p6,  &reg1);
	quantum_cnot(5, p3,  &reg1); quantum_cnot(p3, 5,  &reg1); quantum_cnot(5, p3,  &reg1);
	quantum_cnot(4, p1,  &reg1); quantum_cnot(p1, 4,  &reg1); quantum_cnot(4, p1,  &reg1);
	quantum_cnot(3, p4,  &reg1); quantum_cnot(p4, 3,  &reg1); quantum_cnot(3, p4,  &reg1);
	quantum_cnot(2, p8,  &reg1); quantum_cnot(p8, 2,  &reg1); quantum_cnot(2, p8,  &reg1);
	quantum_cnot(1, p5,  &reg1); quantum_cnot(p5, 1,  &reg1); quantum_cnot(1, p5,  &reg1);
	quantum_cnot(0, p7,  &reg1); quantum_cnot(p7, 0,  &reg1); quantum_cnot(0, p7,  &reg1);
	}
////////////////////////////////////////////////////////////////////////////////
quantum_cnot(p7, k1,  &reg1);
quantum_cnot(p4, k7,  &reg1);
quantum_cnot(p8, k9,  &reg1);
quantum_cnot(p5, k4,  &reg1);

quantum_cnot(p8, k8,  &reg1);
quantum_cnot(p5, k3,  &reg1);
quantum_cnot(p7, k10,  &reg1);
quantum_cnot(p4,k6,  &reg1);

quantum_cnot(p1, k8,  &reg1);
quantum_cnot(p2, k3,  &reg1);
quantum_cnot(p6, k6,  &reg1);
quantum_cnot(p3, k5,  &reg1);

quantum_cnot(p6, k10,  &reg1);
quantum_cnot(p3, k2,  &reg1);
quantum_cnot(p1, k9,  &reg1);
quantum_cnot(p2, k1,  &reg1);


////////////////////////////////////////////////////////////////////////////////
  Q_SDES_BOX_1(k5, k6, k3, k8, p4, p7, &reg1);
  Q_SDES_BOX_2(k1, k9, k2, k10, p8, p5, &reg1);
////////////////////////////////////////////////////////////////////////////////


if(details){
	quantum_cnot(7, p4,  &reg1); quantum_cnot(p4, 7,  &reg1); quantum_cnot(7, p4,  &reg1);
	quantum_cnot(6, p8,  &reg1); quantum_cnot(p8, 6,  &reg1); quantum_cnot(6, p8,  &reg1);
	quantum_cnot(5, p5,  &reg1); quantum_cnot(p5, 5,  &reg1); quantum_cnot(5, p5,  &reg1);
	quantum_cnot(4, p7,  &reg1); quantum_cnot(p7, 4,  &reg1); quantum_cnot(4, p7,  &reg1);
	quantum_cnot(3, p2,  &reg1); quantum_cnot(p2, 3,  &reg1); quantum_cnot(3, p2,  &reg1);
	quantum_cnot(2, p6,  &reg1); quantum_cnot(p6, 2,  &reg1); quantum_cnot(2, p6,  &reg1);
	quantum_cnot(1, p3,  &reg1); quantum_cnot(p3, 1,  &reg1); quantum_cnot(1, p3,  &reg1);
	quantum_cnot(0, p1,  &reg1); quantum_cnot(p1, 0,  &reg1); quantum_cnot(0, p1,  &reg1);

	measured = quantum_measure(reg1);
	printing("The output from (P4-R2) is the state ", measured, &reg1);

	quantum_cnot(7, p4,  &reg1); quantum_cnot(p4, 7,  &reg1); quantum_cnot(7, p4,  &reg1);
	quantum_cnot(6, p8,  &reg1); quantum_cnot(p8, 6,  &reg1); quantum_cnot(6, p8,  &reg1);
	quantum_cnot(5, p5,  &reg1); quantum_cnot(p5, 5,  &reg1); quantum_cnot(5, p5,  &reg1);
	quantum_cnot(4, p7,  &reg1); quantum_cnot(p7, 4,  &reg1); quantum_cnot(4, p7,  &reg1);
	quantum_cnot(3, p2,  &reg1); quantum_cnot(p2, 3,  &reg1); quantum_cnot(3, p2,  &reg1);
	quantum_cnot(2, p6,  &reg1); quantum_cnot(p6, 2,  &reg1); quantum_cnot(2, p6,  &reg1);
	quantum_cnot(1, p3,  &reg1); quantum_cnot(p3, 1,  &reg1); quantum_cnot(1, p3,  &reg1);
	quantum_cnot(0, p1,  &reg1); quantum_cnot(p1, 0,  &reg1); quantum_cnot(0, p1,  &reg1);
	}


quantum_cnot(7, p7,  &reg1); quantum_cnot(p7, 7,  &reg1); quantum_cnot(7, p7,  &reg1);
quantum_cnot(6, p4,  &reg1); quantum_cnot(p4, 6,  &reg1); quantum_cnot(6, p4,  &reg1);
quantum_cnot(5, p5,  &reg1); quantum_cnot(p5, 5,  &reg1); quantum_cnot(5, p5,  &reg1);
quantum_cnot(4, p2,  &reg1); quantum_cnot(p2, 4,  &reg1); quantum_cnot(4, p2,  &reg1);
quantum_cnot(3, p3,  &reg1); quantum_cnot(p3, 3,  &reg1); quantum_cnot(3, p3,  &reg1);
quantum_cnot(2, p8,  &reg1); quantum_cnot(p8, 2,  &reg1); quantum_cnot(2, p8,  &reg1);
quantum_cnot(1, p1,  &reg1); quantum_cnot(p1, 1,  &reg1); quantum_cnot(1, p1,  &reg1);
quantum_cnot(0, p6,  &reg1); quantum_cnot(p6, 0,  &reg1); quantum_cnot(0, p6,  &reg1);

measured = quantum_measure(reg1);
printing("The output ciphertext is: ", measured, &reg1);

quantum_cnot(7, p7,  &reg1); quantum_cnot(p7, 7,  &reg1); quantum_cnot(7, p7,  &reg1);
quantum_cnot(6, p4,  &reg1); quantum_cnot(p4, 6,  &reg1); quantum_cnot(6, p4,  &reg1);
quantum_cnot(5, p5,  &reg1); quantum_cnot(p5, 5,  &reg1); quantum_cnot(5, p5,  &reg1);
quantum_cnot(4, p2,  &reg1); quantum_cnot(p2, 4,  &reg1); quantum_cnot(4, p2,  &reg1);
quantum_cnot(3, p3,  &reg1); quantum_cnot(p3, 3,  &reg1); quantum_cnot(3, p3,  &reg1);
quantum_cnot(2, p8,  &reg1); quantum_cnot(p8, 2,  &reg1); quantum_cnot(2, p8,  &reg1);
quantum_cnot(1, p1,  &reg1); quantum_cnot(p1, 1,  &reg1); quantum_cnot(1, p1,  &reg1);
quantum_cnot(0, p6,  &reg1); quantum_cnot(p6, 0,  &reg1); quantum_cnot(0, p6,  &reg1);
////////////////////////////////////////////////////////////////////////////////

quantum_delete_qureg(&reg1);
}
