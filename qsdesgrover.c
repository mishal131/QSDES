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
#include "qsdesgrover.h"



void grover(int iterations, char *plaintext, char *ciphertext, quantum_reg  *reg1){

int i, iii;
for(i=0;i<10;i++)
	quantum_hadamard(i, reg1);
quantum_sigma_x(GroverOracle, reg1);
quantum_hadamard(GroverOracle, reg1);
for(i=0;i<iterations;i++){
	//BLAINTEXT
	if(plaintext[7]=='1')
		quantum_sigma_x(Tp8, reg1); 
	if(plaintext[6]=='1')   
		quantum_sigma_x(Tp7, reg1);
	if(plaintext[5]=='1')
		quantum_sigma_x(Tp6, reg1);
	if(plaintext[4]=='1')
		quantum_sigma_x(Tp5, reg1);
	if(plaintext[3]=='1')
		quantum_sigma_x(Tp4, reg1);
	if(plaintext[2]=='1')
		quantum_sigma_x(Tp3, reg1);
	if(plaintext[1]=='1')
		quantum_sigma_x(Tp2, reg1);
	if(plaintext[0]=='1')
		quantum_sigma_x(Tp1, reg1);

	quantum_cnot(Tp7, Tk1,  reg1);
	quantum_cnot(Tp4, Tk7,  reg1);
	quantum_cnot(Tp8, Tk9,  reg1);
	quantum_cnot(Tp5, Tk4,  reg1);

	quantum_cnot(Tp8, Tk8,  reg1);
	quantum_cnot(Tp5, Tk3,  reg1);
	quantum_cnot(Tp7, Tk10,  reg1);
	quantum_cnot(Tp4,Tk6,  reg1);

	Q_SDES_BOX_1(Tk4, Tk9, Tk7, Tk1, Tp2, Tp1, reg1);
	Q_SDES_BOX_2(Tk6, Tk10, Tk3, Tk8, Tp6, Tp3, reg1);

	quantum_cnot(Tp7, Tk1,  reg1);
	quantum_cnot(Tp4, Tk7,  reg1);
	quantum_cnot(Tp8, Tk9,  reg1);
	quantum_cnot(Tp5, Tk4,  reg1);

	quantum_cnot(Tp8, Tk8,  reg1);
	quantum_cnot(Tp5, Tk3,  reg1);
	quantum_cnot(Tp7, Tk10,  reg1);
	quantum_cnot(Tp4,Tk6,  reg1);


	quantum_cnot(Tp1, Tk8,  reg1);
	quantum_cnot(Tp2, Tk3,  reg1);
	quantum_cnot(Tp6, Tk6,  reg1);
	quantum_cnot(Tp3, Tk5,  reg1);

	quantum_cnot(Tp6, Tk10,  reg1);
	quantum_cnot(Tp3, Tk2,  reg1);
	quantum_cnot(Tp1, Tk9,  reg1);
	quantum_cnot(Tp2, Tk1,  reg1);


	Q_SDES_BOX_1(Tk5, Tk6, Tk3, Tk8, Tp4, Tp7, reg1);
	Q_SDES_BOX_2(Tk1, Tk9, Tk2, Tk10, Tp8, Tp5, reg1);


	//0011 0110


	//Chosen Ciphertext

	if(ciphertext[0]=='0')
		quantum_sigma_x(Tp7, reg1);  //0011 0110  00110011
	if(ciphertext[1]=='0')
		quantum_sigma_x(Tp4, reg1);
	if(ciphertext[2]=='0')
		quantum_sigma_x(Tp5, reg1);
	if(ciphertext[3]=='0')
		quantum_sigma_x(Tp2, reg1);
	if(ciphertext[4]=='0')
		quantum_sigma_x(Tp3, reg1);  
	if(ciphertext[5]=='0')
		quantum_sigma_x(Tp8, reg1);
	if(ciphertext[6]=='0')
		quantum_sigma_x(Tp1, reg1);
	if(ciphertext[7]=='0')
		quantum_sigma_x(Tp6, reg1);

	quantum_toffoli(Tp7, Tp4, reg1->width+12, reg1);
	quantum_toffoli(Tp5, reg1->width+12, reg1->width+13, reg1);
	quantum_toffoli(Tp2, reg1->width+13, reg1->width+14, reg1);
	quantum_toffoli(Tp3, reg1->width+14, reg1->width+15, reg1);
	quantum_toffoli(Tp8, reg1->width+15, reg1->width+16, reg1);
	quantum_toffoli(Tp1, reg1->width+16, reg1->width+17, reg1);
	quantum_toffoli(Tp6, reg1->width+17, reg1->width+18, reg1);
	quantum_cnot(reg1->width+18, GroverOracle, reg1);
	quantum_toffoli(Tp6, reg1->width+17, reg1->width+18, reg1);
	quantum_toffoli(Tp1, reg1->width+16, reg1->width+17, reg1);
	quantum_toffoli(Tp8, reg1->width+15, reg1->width+16, reg1);
	quantum_toffoli(Tp3, reg1->width+14, reg1->width+15, reg1);
	quantum_toffoli(Tp2, reg1->width+13, reg1->width+14, reg1);
	quantum_toffoli(Tp5, reg1->width+12, reg1->width+13, reg1);
	quantum_toffoli(Tp7, Tp4, reg1->width+12, reg1);

	if(ciphertext[0]=='0')
		quantum_sigma_x(Tp7, reg1);  //0011 0110  00110011
	if(ciphertext[1]=='0')
		quantum_sigma_x(Tp4, reg1);
	if(ciphertext[2]=='0')
		quantum_sigma_x(Tp5, reg1);
	if(ciphertext[3]=='0')
		quantum_sigma_x(Tp2, reg1);
	if(ciphertext[4]=='0')
		quantum_sigma_x(Tp3, reg1);  
	if(ciphertext[5]=='0')
		quantum_sigma_x(Tp8, reg1);
	if(ciphertext[6]=='0')
		quantum_sigma_x(Tp1, reg1);
	if(ciphertext[7]=='0')
		quantum_sigma_x(Tp6, reg1);

	Q_SDES_BOX_1(Tk5, Tk6, Tk3, Tk8, Tp4, Tp7, reg1);
	Q_SDES_BOX_2(Tk1, Tk9, Tk2, Tk10, Tp8, Tp5, reg1);

	quantum_cnot(Tp1, Tk8,  reg1);
	quantum_cnot(Tp2, Tk3,  reg1);
	quantum_cnot(Tp6, Tk6,  reg1);
	quantum_cnot(Tp3, Tk5,  reg1);

	quantum_cnot(Tp6, Tk10,  reg1);
	quantum_cnot(Tp3, Tk2,  reg1);
	quantum_cnot(Tp1, Tk9,  reg1);
	quantum_cnot(Tp2, Tk1,  reg1);

	quantum_cnot(Tp7, Tk1,  reg1);
	quantum_cnot(Tp4, Tk7,  reg1);
	quantum_cnot(Tp8, Tk9,  reg1);
	quantum_cnot(Tp5, Tk4,  reg1);

	quantum_cnot(Tp8, Tk8,  reg1);
	quantum_cnot(Tp5, Tk3,  reg1);
	quantum_cnot(Tp7, Tk10,  reg1);
	quantum_cnot(Tp4, Tk6,  reg1);


	Q_SDES_BOX_1(Tk4, Tk9, Tk7, Tk1, Tp2, Tp1, reg1);
	Q_SDES_BOX_2(Tk6, Tk10, Tk3, Tk8, Tp6, Tp3, reg1);

	quantum_cnot(Tp7, Tk1,  reg1);
	quantum_cnot(Tp4, Tk7,  reg1);
	quantum_cnot(Tp8, Tk9,  reg1);
	quantum_cnot(Tp5, Tk4,  reg1);

	quantum_cnot(Tp8, Tk8,  reg1);
	quantum_cnot(Tp5, Tk3,  reg1);
	quantum_cnot(Tp7, Tk10,  reg1);
	quantum_cnot(Tp4, Tk6,  reg1);

	if(plaintext[7]=='1')
		quantum_sigma_x(Tp8, reg1); 
	if(plaintext[6]=='1')   
		quantum_sigma_x(Tp7, reg1);
	if(plaintext[5]=='1')
		quantum_sigma_x(Tp6, reg1);
	if(plaintext[4]=='1')
		quantum_sigma_x(Tp5, reg1);
	if(plaintext[3]=='1')
		quantum_sigma_x(Tp4, reg1);
	if(plaintext[2]=='1')
		quantum_sigma_x(Tp3, reg1);
	if(plaintext[1]=='1')
		quantum_sigma_x(Tp2, reg1);
	if(plaintext[0]=='1')
		quantum_sigma_x(Tp1, reg1);

	for(iii=0;iii<10;iii++)
		quantum_hadamard(iii, reg1);
	for(iii=0;iii<10;iii++)
		quantum_sigma_x(iii, reg1);

	quantum_toffoli(0, 1, reg1->width+12, reg1);
	quantum_toffoli(2, reg1->width+12, reg1->width+13, reg1);
	quantum_toffoli(3, reg1->width+13, reg1->width+14, reg1);
	quantum_toffoli(4, reg1->width+14, reg1->width+15, reg1);
	quantum_toffoli(5, reg1->width+15, reg1->width+16, reg1);
	quantum_toffoli(6, reg1->width+16, reg1->width+17, reg1);
	quantum_toffoli(7, reg1->width+17, reg1->width+18, reg1);
	quantum_toffoli(8, reg1->width+18, reg1->width+19, reg1);
        quantum_hadamard(9, reg1);
	quantum_cnot(reg1->width+19, 9, reg1);
        quantum_hadamard(9, reg1);
	quantum_toffoli(8, reg1->width+18, reg1->width+19, reg1);
	quantum_toffoli(7, reg1->width+17, reg1->width+18, reg1);
	quantum_toffoli(6, reg1->width+16, reg1->width+17, reg1);
	quantum_toffoli(5, reg1->width+15, reg1->width+16, reg1);
	quantum_toffoli(4, reg1->width+14, reg1->width+15, reg1);
	quantum_toffoli(3, reg1->width+13, reg1->width+14, reg1);
	quantum_toffoli(2, reg1->width+12, reg1->width+13, reg1);
	quantum_toffoli(0, 1, reg1->width+12, reg1);

	for(iii=0;iii<10;iii++)
		quantum_sigma_x(iii, reg1);
	for(iii=0;iii<10;iii++)
		quantum_hadamard(iii, reg1);

	}
quantum_hadamard(GroverOracle, reg1);
quantum_sigma_x(GroverOracle, reg1);
}

void groverAttack(char *plaintext, char *ciphertext, int details){

int i, j;
int iterations;
quantum_reg  reg1 = quantum_new_qureg(0, 10); 
grover(2, plaintext, ciphertext, &reg1);

int s = 0; //number of found solutions.
double prob1=0; 
for(i=0; i<reg1.size; i++){
	if ( quantum_prob(reg1.node[i].amplitude) > 0.001)
		s ++;
	}

printf("================================================================================\n");
printf("\nNumber of found solution(s) = %i\n", s); 
printf("\nAccordingly, grover iterations are calculated as:\niterations = pi/4*sqrt((2^width)/solutions), that means: iterations = %i\n\n", 
      (int) (pi/4*sqrt(1024/s)));

iterations = (int) (pi/4*sqrt(1024/s));
quantum_reg  reg2 = quantum_new_qureg(0, 10); 

grover(iterations, plaintext, ciphertext, &reg2);

int measureMe =quantum_measure(reg2);

prob1=0;
for(i=1; i<reg2.size; i++)
	{
	if (prob1 < quantum_prob(reg2.node[i].amplitude))
		prob1 = quantum_prob(reg2.node[i].amplitude);
	}

printf("Note that, randomness plays the major role in the measurment in case of multiple solutions.\n\n");

printf("The measured solution is |%i> with a probability of %f among %d solutions\n\n" , measureMe, prob1, s);

int measureMe2 = measureMe;
int printbinary[reg2.width];
for(j=reg2.width-1;j>=0;j--){
	if (measureMe & 1)
		printbinary[j] = 1;
	else
		printbinary[j] = 0;
	measureMe >>= 1;
	}

printf("If the secret key is not this solution |%i> (in binary is ", measureMe2);
printf("|");
for(j=0;j<reg2.width;j++) 
	printf("%i", printbinary[j]);
		
printf(">)\n");
printf("Please go to the explicit [<e>] mode to see all the quantum states using the following:\n");
printf("[./qsdes <findkey> <plaintextBits> <ciphertextBits> <e>]\n");
printf("Example: ./qsdes findkey 00010000 00110011 e>OutputFile\n");
printf("================================================================================\n");


if(details)
	quantum_print_qureg(reg2);

quantum_delete_qureg(&reg1);
quantum_delete_qureg(&reg2);

}

