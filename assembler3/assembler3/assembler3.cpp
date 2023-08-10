#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_LENGTH 80

char* dectohex(int decimal)
{

	int  remainder, quotient;
	char hexadecimal[100];

	quotient = decimal;

	int i = 0, size = 0;
	char* finalhex;
	finalhex = (char*)malloc((size) * sizeof(char));


	if (decimal == 0)
	{
		char* z = new char;
		char a = '\0';
		strcpy(z, &a);
		return z;
	}

	//Convert decimal to hexadecimal
	while (quotient != 0) {
		remainder = quotient % 16;
		if (remainder < 10) {
			hexadecimal[i] = remainder + 48;
			size++;
		}
		else {
			hexadecimal[i] = remainder + 55;
			size++;
		}
		i++;
		quotient = quotient / 16;
	}

	char a = '\0';
	strcpy(finalhex, &a);

	for (int j = i - 1; j >= 0; j--) {

		char* x = &hexadecimal[j];

		strncat(finalhex, x, 1);
	}

	return finalhex;
}

void hex_to_machine_code(char* hex_string, char* machine_code) {
	int decimal_num;
	sscanf(hex_string, "%x", &decimal_num); // Convert hexadecimal to decimal

	// Convert decimal to binary and store in machine_code array
	int i = 0;
	while (decimal_num > 0) {
		machine_code[i++] = (decimal_num % 2) + '0'; // Convert binary digit to character
		decimal_num /= 2;
	}

	// Pad with zeros to ensure machine code is 8 bits long
	while (i < 8) {
		machine_code[i++] = '0';
	}

	// Reverse the order of the bits to get big-endian format
	char temp;
	for (int j = 0; j < 4; j++) {
		temp = machine_code[j];
		machine_code[j] = machine_code[7 - j];
		machine_code[7 - j] = temp;
	}

	// Convert binary to machine code
	
}


int main()
{
	char a = '\0';

	struct symboltable
	{
	public:
		int num;
		char *label;
	};
	//symboltable *symtbl= (struct symboltable*)malloc(1 * sizeof(struct symboltable));
	struct symboltable symtbl[10];

	/*for (int i = 0; i < 10; i++)
	{
		strcpy(symtbl.label[i], &a);
		strcpy(symtbl.num[i], &a);
	}*/

	for (int i=0;i<9;i++)
	{
		symtbl[i].label = new char;
		//symtbl[i].num = new char;
	}


	char line[80];
	//char program[100][10];//number of instructions
	int counter = 0;
	char* rs, * rd, * rt, * nextpart;
	char* instruct = new char;
	char program[5][10];
	int labelnum = 0;
	//char orders[] = { "# add sub slt or nand addi ori slti lui lw beq jalr j halt .fill" };
	char orders[17][6] = { "#","add", "sub", "slt", "or", "nand" ,"addi" ,"ori" ,"slti" ,"lui" ,"lw" ,"beq" ,"jalr" ,"j" ,"halt",".fill" };
	strcpy(program[0], &a);//program counter with only 5 instructions :)
	strcpy(program[1], &a);
	strcpy(program[2], &a);
	strcpy(program[3], &a);
	strcpy(program[4], &a);

	strcpy(instruct, &a);

	FILE* fp;
	fp = fopen("program.as", "r");

	if (!fp)
	{
		perror("program.as");
		return EXIT_FAILURE;
	}

	/////////////////////////////////////////////////////// FIRST SCAN ///////////////////////////////////////////////////////////////////

	int linenum = 0;
	while (fgets(line, MAX_LINE_LENGTH, fp))
	{
		linenum++;
		instruct = strtok_s(line, "\n\t\r, ", &nextpart);
		char* token = new char;
		strcpy(token, &a);

		//token = strtok_s(orders, "\n\t\r, ", &nextpart);
		if (strcmp(instruct, "#") == 0)
		{
			linenum--;
			continue;
		}
	
		for (int i = 0; i < 17; i++)// labels at first of each line
			{
				if (strcmp(instruct, orders[i]) == 0)
				{
					break;
				}
				else if(i==16) // it means it is  a label
				{
					strcpy(symtbl[labelnum].label, instruct);
					/*char s = linenum + '0';
					memcpy(symtbl[labelnum].num, &s, 1);
					puts(symtbl[labelnum].num);*/
					symtbl[labelnum].num = linenum;
					labelnum++;
				}
			}

		delete token;

	}

	/*
	
	fp = fopen("program.as", "r");
	 linenum = 0;
	 while (fgets(line, MAX_LINE_LENGTH, fp))
	 {
		 linenum++;
		 instruct = strtok_s(line, "\n\t\r, ", &nextpart);

		 char* token = new char;
		 strcpy(token, &a);

		 //token = strtok_s(orders, "\n\t\r, ", &nextpart);
		 if (strcmp(instruct, "#") == 0)
		 {
			 continue;
		 }

		 for (int i = 0; i < 17; i++) //labels inside instructions
		 {
			 if (strcmp(instruct, orders[i]) == 0)
			 {
				 if ((strcmp(instruct, "lw") == 0 || strcmp(instruct, "sw") == 0 || strcmp(instruct, "beq") == 0))
				 {
					 rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
					 rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
					 char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
					 symtbl[labelnum].label = imm;
					 symtbl[labelnum].num = linenum;
					 labelnum++;

				 }
				 else if (strcmp(instruct, "j") == 0)
				 {

				 }
			 }
		 }

		 for (int i = 0; i < labelnum; i++) //labels inside instructions
		 {
			 if (strcmp(instruct, symtbl[i].label) == 0)
			 {
				 ///.....
			 }
		 }
	 }
	 
	 */

	////////////////////////////////////////////////////////////// SECOND SCAN /////////////////////////////////////////////////////////
	 fclose(fp);
	fp = fopen("program.as", "r");


	while (fgets(line, MAX_LINE_LENGTH, fp))
	{

		char* instruct = strtok_s(line, "\n\t\r ", &nextpart);
		
		start:
		if (strcmp(instruct, "add") == 0)
		{
			rd = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);

			int rd1 = atoi(rd);
			int rs1 = atoi(rs);
			int rt1 = atoi(rt);

			char* rd2 = dectohex(rd1);
			char* rs2 = dectohex(rs1);
			char* rt2 = dectohex(rt1);

			char* hexarr = new char[10];
			char mergedhex[10];

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "0");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);
			strcat(hexarr, rd2);
			strcpy(&hexarr[7], "0");
			strcpy(&hexarr[8], "0");
			strcpy(&hexarr[9], "0");



			//memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr) + 1);

			counter++;
			continue;



		}
		else if (strcmp(instruct, "sub") == 0)
		{

			rd = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rd1 = atoi(rd);
			int rs1 = atoi(rs);
			int rt1 = atoi(rt);
			char* rd2 = dectohex(rd1);
			char* rs2 = dectohex(rs1);
			char* rt2 = dectohex(rt1);

			char* hexarr = new char[10];
			char mergedhex[10];

			strcpy(hexarr, &a);  

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "1");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);
			strcat(hexarr, rd2);
			strcpy(&hexarr[7], "0");
			strcpy(&hexarr[8], "0");
			strcpy(&hexarr[9], "0");

			int x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;

			continue;

		}
		else if (strcmp(instruct, "slt") == 0)
		{

			rd = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rd1 = atoi(rd);
			int rs1 = atoi(rs);
			int rt1 = atoi(rt);
			char* rd2 = dectohex(rd1);
			char* rs2 = dectohex(rs1);
			char* rt2 = dectohex(rt1);

			char* hexarr = new char[10];
			char mergedhex[10];

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "2");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);
			strcat(hexarr, rd2);
			strcpy(&hexarr[7], "0");
			strcpy(&hexarr[8], "0");
			strcpy(&hexarr[9], "0");

			int x = strlen(hexarr);
			//memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;

			continue;

		}
		else if (strcmp(instruct, "or") == 0)
		{

			rd = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rd1 = atoi(rd);
			int rs1 = atoi(rs);
			int rt1 = atoi(rt);
			char* rd2 = dectohex(rd1);
			char* rs2 = dectohex(rs1);
			char* rt2 = dectohex(rt1);

			char* hexarr = new char[10];
			char mergedhex[10];
			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "3");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);
			strcat(hexarr, rd2);
			strcpy(&hexarr[7], "0");
			strcpy(&hexarr[8], "0");
			strcpy(&hexarr[9], "0");


			int x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;
			continue;


		}
		else if (strcmp(instruct, "nand") == 0)
		{

			rd = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rd1 = atoi(rd);
			int rs1 = atoi(rs);
			int rt1 = atoi(rt);
			char* rd2 = dectohex(rd1);
			char* rs2 = dectohex(rs1);
			char* rt2 = dectohex(rt1);

			char* hexarr = new char[10];
			char mergedhex[10];

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "4");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);
			strcat(hexarr, rd2);
			strcpy(&hexarr[7], "0");
			strcpy(&hexarr[8], "0");
			strcpy(&hexarr[9], "0");

			int x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;

			continue;

		}

		else if (strcmp(instruct, "addi") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rt1 = atoi(rt);
			int  rs1 = atoi(rs);
			int  imm1 = atoi(imm);
			char* rt2 = dectohex(rt1);
			char* rs2 = dectohex(rs1);
			char* imm2 = dectohex(imm1);

			char* hexarr = new char[10];
			char mergedhex[10];

			int x = strlen(imm2);

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "5");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);

			if (x == 4)
			{
				strcat(hexarr, imm2);

			}
			else if (x == 3)
			{
				strcpy(&hexarr[6], "0");
				strcat(hexarr, imm2);

			}
			else if (x == 2)
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");

				strcat(hexarr, imm2);

			}
			else
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");
				strcat(hexarr, imm2);
			}


			x = strlen(hexarr);
			//memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;

			continue;

		}
		else if (strcmp(instruct, "slti") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rt1 = atoi(rt);
			int  rs1 = atoi(rs);
			int  imm1 = atoi(imm);
			char* rt2 = dectohex(rt1);
			char* rs2 = dectohex(rs1);
			char* imm2 = dectohex(imm1);

			char* hexarr = new char[10];
			char mergedhex[10];
			int x = strlen(imm2);
			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "6");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);

			if (x == 4)
			{
				strcat(hexarr, imm2);

			}
			else if (x == 3)
			{
				strcpy(&hexarr[6], "0");
				strcat(hexarr, imm2);

			}
			else if (x == 2)
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");

				strcat(hexarr, imm2);

			}
			else
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");
				strcat(hexarr, imm2);
			}

			x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;

			continue;

		}
		else if (strcmp(instruct, "ori") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rt1 = atoi(rt);
			int  rs1 = atoi(rs);
			int  imm1 = atoi(imm);
			char* rt2 = dectohex(rt1);
			char* rs2 = dectohex(rs1);
			char* imm2 = dectohex(imm1);

			char* hexarr = new char[10];
			char mergedhex[10];
			int x = strlen(imm2);

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "7");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);

			if (x == 4)
			{
				strcat(hexarr, imm2);

			}
			else if (x == 3)
			{
				strcpy(&hexarr[6], "0");
				strcat(hexarr, imm2);

			}
			else if (x == 2)
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");

				strcat(hexarr, imm2);

			}
			else
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");
				strcat(hexarr, imm2);
			}

			x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;
			continue;


		}
		else if (strcmp(instruct, "lui") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rt1 = atoi(rt);
			int  imm1 = atoi(imm);
			char* rt2 = dectohex(rt1);
			char* imm2 = dectohex(imm1);

			char* hexarr = new char[10];
			char mergedhex[10];
			int x = strlen(imm2);

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "8");
			strcpy(hexarr, "0");
			strcat(hexarr, rt2);

			if (x == 4)
			{
				strcat(hexarr, imm2);

			}
			else if (x == 3)
			{
				strcpy(&hexarr[6], "0");
				strcat(hexarr, imm2);

			}
			else if (x == 2)
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");

				strcat(hexarr, imm2);

			}
			else
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");
				strcat(hexarr, imm2);
			}


			x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;
			continue;


		}
		else if (strcmp(instruct, "lw") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rt1 = atoi(rt);
			int  rs1 = atoi(rs);

			int  imm1 = atoi(imm);

			char* rt2 = dectohex(rt1);
			char* rs2 = dectohex(rs1);

		   char* imm2 = dectohex(imm1);

		

			//imm = dectohex(imm);

			char* hexarr = new char[10];
			char mergedhex[10];
			//int x = strlen(imm2);

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "9");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);

			int x = strlen(imm);

			if (x == 4)
			{
				strcat(hexarr, imm2);

			}
			else if (x == 3)
			{
				strcpy(&hexarr[6], "0");
				strcat(hexarr, imm2);

			}
			else if (x == 2)
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");

				strcat(hexarr, imm2);

			}
			else
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");
				strcat(hexarr, imm2);
			}

			x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;

			continue;

		}
		else if (strcmp(instruct, "sw") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rt1 = atoi(rt);
			int  rs1 = atoi(rs);
			int  imm1 = atoi(imm);
			char* rt2 = dectohex(rt1);
			char* rs2 = dectohex(rs1);
			char* imm2 = dectohex(imm1);

			char* hexarr = new char[10];
			char mergedhex[10];
			int x = strlen(imm);

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "A");
			strcat(hexarr, rs2);
			strcat(hexarr, rt2);

			if (x == 4)
			{
				strcat(hexarr, imm2);

			}
			else if (x == 3)
			{
				strcpy(&hexarr[6], "0");
				strcat(hexarr, imm2);

			}
			else if (x == 2)
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");

				strcat(hexarr, imm2);

			}
			else
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");
				strcat(hexarr, imm2);
			}

			x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;
			continue;


		}
		else if (strcmp(instruct, "beq") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);
			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff);
			int rt1 = atoi(rt);
			int  rs1 = atoi(rs);
			int  imm1 = atoi(imm);
			char* rt2 = dectohex(rt1);
			char* rs2 = dectohex(rs1);
			char* imm2 = dectohex(imm1);

			char* address=new char;
			for (int i = 0; i <= labelnum; i++)
			{
				if (strcmp(symtbl[i].label, imm) == 0)
				{
					int a = symtbl[i].num;
					 address = dectohex(a);
					break;
				}
			}

			char *hexarr=new char[10];
			char mergedhex[10];
			int x = strlen(address);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "b");

			strcat(hexarr, rs2);
			strcat(hexarr, rt2);
			if (x == 4)
			{
				strcat(hexarr, address);

			}
			else if (x == 3)
			{

				strcpy(&hexarr[6], "0");
				strcat(hexarr, address);

			}
			else if (x == 2)
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcat(hexarr, address);

			}
			else
			{
				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");
				strcat(hexarr, address);
			}

			x = strlen(hexarr);
			//memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;
			continue;


		}
		else if (strcmp(instruct, "jalr") == 0)
		{

			rt = strtok_s(NULL, "\n\t\r, ", &nextpart);
			rs = strtok_s(NULL, "\n\t\r, ", &nextpart);

			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 
			int rt1 = atoi(rt);
			int  rs1 = atoi(rs);
			char* rt2 = dectohex(rt1);
			char* rs2 = dectohex(rs1);

			char* hexarr = new char[10];
			char mergedhex[10];

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "c");
			strcat(&hexarr[4], rs2);
			strcat(&hexarr[5], rt2);
			strcpy(&hexarr[6], "0");
			strcpy(&hexarr[7], "0");
			strcpy(&hexarr[8], "0");
			strcpy(&hexarr[9], "0");

			int x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);
			//strcpy(program[counter], '\0');
			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;
			continue;


		}
		else if (strcmp(instruct, "j") == 0)
		{


			char* imm = strtok_s(NULL, "\n\t\r, ", &nextpart);
			//int chch = (op1[0] - 48) | ((op2[0] - 48) << 3) | ((op3[0] - 48) << 6);
			//program[counter] = 0x00000000 + ((chch) & 0x00ff); 

			int  imm1 = atoi(imm);
			char* imm2 = dectohex(imm1);
			int x = strlen(imm2);
			char* hexarr = new char[10];
			char mergedhex[10];

			char* address = new char;
			for (int i = 0; i <= labelnum; i++)
			{
				if (strcmp(symtbl[i].label, imm) == 0)
				{
					int a = symtbl[i].num;
					address = dectohex(a);
					break;
				}
			}

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "d");
			strcpy(&hexarr[4], "0");
			strcpy(&hexarr[5], "0");

			if (x == 4)
			{
				strcat(hexarr, address);

			}
			else if (x == 3)
			{
				strcpy(&hexarr[6], "0");
				strcpy(hexarr, address);

			}
			else if (x == 2)
			{

				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");

				strcat(hexarr, address);

			}
			else
			{

				strcpy(&hexarr[6], "0");
				strcpy(&hexarr[7], "0");
				strcpy(&hexarr[8], "0");

				strcat(hexarr, address);
			}


			x = strlen(hexarr);
		//	memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;
			continue;


		}
		else if (strcmp(instruct, "halt") == 0)
		{

			/*	int  imm1 = atoi(rt);
				char* imm2 = dectohex(imm1);
				int x = strlen(imm2);*/

			char* hexarr = new char[10];
			char mergedhex[10];

			strcpy(hexarr, &a);

			strcpy(&hexarr[0], "0");
			strcpy(&hexarr[1], "x");
			strcpy(&hexarr[2], "0");
			strcpy(&hexarr[3], "e");
			strcpy(&hexarr[4], "0");
			strcpy(&hexarr[5], "0");
			strcpy(&hexarr[6], "0");
			strcpy(&hexarr[7], "0");
			strcpy(&hexarr[8], "0");
			strcpy(&hexarr[9], "0");


			int x = strlen(hexarr);
			//memcpy(mergedhex, hexarr, strlen(hexarr));

			//program[counter] = atoi(mergedhex);

			memcpy(program[counter], hexarr, strlen(hexarr));

			counter++;

			continue;
		}
		else if (strncmp(instruct, "#", 1) == 0)
		{
			continue;
		}

		else //it means it was a label
		{

		instruct = strtok_s(NULL, "\n\t\r, ", &nextpart);
		goto start;
        }

	}

	
	

	FILE* file;
	file = fopen("program.mc", "wb");

	//fprintf(file, program[0], "\n");
	
	//fprintf(file, "%s", program[0]);

	
	
	int j = 0;
	for (int i = 0; i < linenum; i++)
	{
		for(int j=0;j<10;j++)
		fprintf(file, "%c", program[i][j]); 
		fprintf(file, "\n");
	}
	
	fclose(file);

	return 0;

}
