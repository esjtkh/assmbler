#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    FILE *fp;
    char line[100];
    char*instrctn=NULL;

    char *op1, *op2, *op3, *label;
       char ch;
       int  chch;

       int program[1000];
       int counter=0;

           struct label
           {
               int location;
               char *label;
           };
           struct label labeltable[50]; //there can be 50 labels at most in our programs
           int nooflabels = 0;

           fp = fopen("test1.txt","r");


           //========================================   FIRST PASS  ======================================================
                       while (instrctn)
                       {
                         /*  if (strcmp(instrctn,"ldi")==0)        //---------------LDI INSTRUCTION--------------------
                           {
                               op1 = strtok(NULL,"\n\t\r ");                                //get the 1st operand of ldi, which is the register that ldi loads
                               op2 = strtok(NULL,"\n\t\r ");                                //get the 2nd operand of ldi, which is the data that is to be loaded
                               program[counter]=0x1000+hex2int(op1);                        //generate the first 16-bit of the ldi instruction
                               counter++;                                                   //move to the second 16-bit of the ldi instruction
                               if ((op2[0]=='0')&&(op2[1]=='x'))                            //if the 2nd operand is twos complement hexadecimal
                                   program[counter]=hex2int(op2+2)&0xffff;              //convert it to integer and form the second 16-bit
                               else if ((  (op2[0])=='-') || ((op2[0]>='0')&&(op2[0]<='9')))       //if the 2nd operand is decimal
                                   program[counter]=atoi(op2)&0xffff;                         //convert it to integer and form the second 16-bit
                               else                                                           //if the second operand is not decimal or hexadecimal, it is a laber or a variable.
                               {                                                               //in this case, the 2nd 16-bits of the ldi instruction cannot be generated.
                                   lditable[noofldis].location = counter;                 //record the location of this 2nd 16-bit
                                   op1=(char*)malloc(sizeof(op2));                         //and the name of the label/variable that it must contain
                                   strcpy(op1,op2);                                        //in the lditable array.
                                   lditable[noofldis].name = op1;
                                   noofldis++;
                               }
                               counter++;                                                     //skip to the next memory location
                           }   */

                           /*else if (strcmp(token,"ld")==0)      //------------LD INSTRUCTION---------------------
                           {
                               op1 = strtok(NULL,"\n\t\r ");                //get the 1st operand of ld, which is the destination register
                               op2 = strtok(NULL,"\n\t\r ");                //get the 2nd operand of ld, which is the source register
                               ch = (op1[0]-48)| ((op2[0]-48) << 3);        //form bits 11-0 of machine code. 48 is ASCII value of '0'
                               program[counter]=0x2000+((ch)&0x00ff);       //form the instruction and write it to memory
                               counter++;                                   //skip to the next empty location in memory
                           }*/
                           /*else if (strcmp(token,"st")==0) //-------------ST INSTRUCTION--------------------
                           {
                               //to be added
                           }
                           else if (strcmp(token,"jz")==0) //------------- CONDITIONAL JUMP ------------------
                           {
                               //to be added
                           }
                           else if (strcmp(token,"jmp")==0)  //-------------- JUMP -----------------------------
                           {
                               op1 = strtok(NULL,"\n\t\r ");           //read the label
                               jumptable[noofjumps].location = counter;    //write the jz instruction's location into the jumptable
                               op2=(char*)malloc(sizeof(op1));         //allocate space for the label
                               strcpy(op2,op1);                //copy the label into the allocated space
                               jumptable[noofjumps].label=op2;         //point to the label from the jumptable
                               noofjumps++;                    //skip to the next empty location in jumptable
                               program[counter]=0x5000;            //write the incomplete instruction (just opcode) to memory
                               counter++;                  //skip to the next empty location in memory.
                           }    */
                           else if (strcmp(instrctn,"add")==0) //----------------- ADD -------------------------------
                           {
                               op1 = strtok(NULL,"\n\t\r ");
                               op2 = strtok(NULL,"\n\t\r ");
                               op3 = strtok(NULL,"\n\t\r ");
                               chch = (op1[0]-48)| ((op2[0]-48)<<3)|((op3[0]-48)<<6);
                               program[counter]=0x7000+((chch)&0x00ff);
                               counter++;
                           }
                           else if (strcmp(token,"sub")==0)
                           {
                               //to be added
                           }
                           else if (strcmp(token,"and")==0)
                           {
                               //to be added
                           }
                           else if (strcmp(token,"or")==0)
                           {
                               //to be added
                           }
                           else if (strcmp(token,"xor")==0)
                           {
                               //to be added
                           }
                           else if (strcmp(token,"not")==0)
                           {
                               op1 = strtok(NULL,"\n\t\r ");
                               op2 = strtok(NULL,"\n\t\r ");
                               ch = (op1[0]-48)| ((op2[0]-48)<<3);
                               program[counter]=0x7500+((ch)&0x00ff);
                               counter++;
                           }
                           else if (strcmp(token,"mov")==0)
                           {
                               //to be added
                           }
                           else if (strcmp(token,"inc")==0)
                           {
                               op1 = strtok(NULL,"\n\t\r ");
                               ch = (op1[0]-48)| ((op1[0]-48)<<3);
                               program[counter]=0x7700+((ch)&0x00ff);
                               counter++;
                           }
                           else if (strcmp(token,"dec")==0)
                           {
                                               //to be added
                           }
                           else //------WHAT IS ENCOUNTERED IS NOT AN INSTRUCTION BUT A LABEL. UPDATE THE LABEL TABLE--------
                           {
                               labeltable[nooflabels].location = counter;  //buraya bir counter koy. error check
                               op1=(char*)malloc(sizeof(token));
                               strcpy(op1,token);
                               labeltable[nooflabels].label=op1;
                               nooflabels++;
                           }
                           token = strtok(NULL,",\n\t\r ");
                       }













    return a.exec();
}
