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

#ifndef __QSDES_H

#define __QSDES_H



#define Tk10  0  //<-- key bit #0
#define Tk9  1
#define Tk8  2
#define Tk7  3
#define Tk6  4
#define Tk5  5
#define Tk4  6
#define Tk3  7
#define Tk2  8
#define Tk1  9

#define  GroverOracle reg1->width+11

#define  Tp8 reg1->width+3 // <-- plaintext bit 0
#define  Tp7 reg1->width+4
#define  Tp6 reg1->width+5
#define  Tp5 reg1->width+6
#define  Tp4 reg1->width+7
#define  Tp3 reg1->width+8
#define  Tp2 reg1->width+9
#define  Tp1 reg1->width+10

#define  p8 reg1.width+3 // <-- plaintext bit 0
#define  p7 reg1.width+4
#define  p6 reg1.width+5
#define  p5 reg1.width+6
#define  p4 reg1.width+7
#define  p3 reg1.width+8
#define  p2 reg1.width+9
#define  p1 reg1.width+10

#define k10  reg1.width+12  //<-- key bit #0
#define k9  reg1.width+13
#define k8  reg1.width+14
#define k7  reg1.width+15
#define k6  reg1.width+16
#define k5  reg1.width+17
#define k4  reg1.width+18
#define k3  reg1.width+19
#define k2  reg1.width+20
#define k1  reg1.width+21



#ifdef M_PI
#define pi M_PI
#else
#define pi 3.141592654
#endif


#endif

