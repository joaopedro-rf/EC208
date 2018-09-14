#include <iostream>
/*
	Código das intruções:
	ADD 1000 -> tipo 1
	LOAD 1100 -> tipo 2
	STORE 1110 -> tipo 3
	
	16 bits padrão 
	(Endereço 1) | (Endereço 2) | ( Endereço Dest ) | ( OP CODE )  ADD
		0000 	 |		0001 	|		0010 		|	1000    
	(Endereço 1) |         ( End Memo Dados) 		| ( OP CODE )  LOAD
		0000     |             00000001            	|	1100     
	(Endereço 1) |         ( End Memo Dados) 		| ( OP CODE )  STORE
	    0000     |             00000001           	|	1110   
	(Endereço 1) | (Endereço 2) | ( Endereço Dest ) | ( OP CODE )  SUB
		0000 	 |		0001 	|		0010 		|	1001   
*/

using namespace std;

unsigned int Pc;
unsigned int Reg1;
unsigned int Reg2;
unsigned int RegDest;
unsigned int tipoInstruc;
unsigned int Instruc;
unsigned int RegMemo;
unsigned int Reg[10];

unsigned int memoriaProgram[]
{
	0b0000000000001100, //load reg0-> reg0
	0b0001000000011100, //load reg1->reg1
	0b0000000100101000, //add reg0+reg1 = reg2
	0b0011000000101100, //load reg2->reg3
	0b0010001101001001, //sub reg2-reg3 = reg4
	0b0100000000011110, //store reg4 -> reg1
};

unsigned int memoriaDados[]
{
	5,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void decode(void)
{
	tipoInstruc = Instruc & 0b0000000000001111;
	if(tipoInstruc == 8 || tipoInstruc == 9)
	{ // add
		Reg1 = Instruc >> 12;
		Reg1 = Reg1 & 0b0000000000001111;
		Reg2 = Instruc >> 8;
		Reg2 = Reg2 & 0b0000000000001111;
		RegDest = Instruc >> 4;
		RegDest = RegDest & 0b0000000000001111;

	}
	else if(tipoInstruc == 12) 
	{ // load
		RegDest = Instruc >> 12;
		RegDest = RegDest & 0b0000000000001111;
		RegMemo = Instruc >> 4;
		RegMemo = RegMemo & 0b0000000011111111;
	}
	else if(tipoInstruc == 14)
	{ // store
		Reg1 = Instruc >> 12;
		Reg1 = Reg1 & 0b0000000000001111;
		RegMemo = Instruc >> 4;
		RegMemo = RegMemo & 0b0000000011111111;
	}
	    
}

void execute(void)
{ 
	tipoInstruc = Instruc & 0b0000000000001111;
	if(tipoInstruc == 8)
	{ // add
	    Reg[RegDest] = Reg[Reg1] + Reg[Reg2];
	}
	else if(tipoInstruc == 9)
	{
		Reg[RegDest] = Reg[Reg1] - Reg[Reg2];
	}
	else if(tipoInstruc == 12) 
	{ // load
		Reg[RegDest] = memoriaDados[RegMemo]; 
	}
	else if(tipoInstruc == 14)
	{ // store
		memoriaDados[RegMemo] = Reg[Reg1];
	}
	}
int main()
{
	Pc = 0;
	for(int i = 0; i < 10; i++)
	{
		Reg[i] = 0;
	}
	
	while(Pc < 6)
	{
		Instruc = memoriaProgram[Pc]; 
		Pc++;
		decode();   
		execute();
	}

	return 0;
}
