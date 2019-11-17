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
#include <string.h>
#include <time.h>


#include "qsdes.h"
#include "qsdessboxes.h"
#include "qsdestest.h"
#include "qsdesgrover.h"



#define explicit 1
#define implicit 0

void usagePrint(){
      printf("================================================================================\n");
      printf("Usage:\n");
      printf("================================================================================\n");
      printf("1- To apply Grover attack on SDES:\n");
      printf("./qsdes <findkey> <plaintextBits> <ciphertextBits>\n");
      printf("Example: ./qsdes findkey 00010000 00110011\n");
      printf("Or in explicit mode: ./qsdes <findkey> <plaintextBits> <ciphertextBits> <e>\n");
      printf("Example: ./qsdes findkey 00010000 00110011 e>OutputFile\n");
      printf("--------------------------------------------------------------------------------\n");
      printf("2- SDES encryption:\n");
      printf("./qsdes <cipher> <plaintextBits> <keyBits>\n");
      printf("Example: ./qsdes cipher 00010000 1100010011\n");
      printf("Or in explicit mode: ./qsdes <cipher> <plaintextBits> <keyBits> <e>\n");
      printf("Example: ./qsdes cipher 00010000 1100010011 e>OutputFile\n");
      printf("================================================================================\n");
}

int main(int argc, char **argv)
{
  srand(time(0));

    struct timespec begin, end;
   clock_t t; 
    t = clock(); 
    	clock_gettime(CLOCK_MONOTONIC_RAW, &begin);


  if(argc<4 || argc>5)
    {
usagePrint();
      return 0;
    }

if(strcmp(argv[1],"findkey")==0){
if(strlen(argv[2]) !=8){
      printf("The entered plaintext is not 8-bit block\n");
      return 0;
}
if(strlen(argv[3]) !=8){
      printf("The entered ciphertext is not 8-bit block\n");
      return 0;
}

char *plaintext = argv[2];
char *ciphertext = argv[3];

if(argc==4){
	groverAttack(plaintext, ciphertext, implicit);
}
if(argc==5){
	groverAttack(plaintext, ciphertext, explicit);
}
}

if(strcmp(argv[1],"cipher")==0){
if(strlen(argv[2]) !=8){
      printf("The entered plaintext is not 8-bit block\n");
      return 0;
}
if(strlen(argv[3]) !=10){
      printf("The entered key is not 10-bit key\n");
      return 0;
}

char *plaintext = argv[2];
char *key = argv[3];
if(argc==5){

test(key, plaintext, explicit);

}
if(argc==4){

test(key, plaintext, implicit);
}

}

    	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("It took %f seconds to execute \n", time_taken); 
   	printf ("Total time = %f seconds\n",(end.tv_nsec - begin.tv_nsec) / 1000000000.0 +(end.tv_sec  - begin.tv_sec));

  return 0;
}

