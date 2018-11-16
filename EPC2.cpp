#include <iostream>
/*
	Código das intruções:
	ADD 1000 -> Tipo de instrução 8
	SUB 1001 -> Tipo de instrução 9
	LOAD 1100 -> Tipo de instrução 12
	STORE 1110 -> Tipo de instrução 14
	
	
	16 bits padrão 
	(Endereço 1) | (Endereço 2) | ( Endereço Dest ) | ( OP CODE )  ADD
		0000 	 |		0001 	|		0010 		|	1000    
	(Endereço 1) | (Endereço 2) | ( Endereço Dest ) | ( OP CODE )  SUB
		0000 	 |		0001 	|		0010 		|	1001   
	(Endereço 1) |         ( End Memo Dados) 		| ( OP CODE )  LOAD
		0000     |             00000001            	|	1100     
	(Endereço 1) |         ( End Memo Dados) 		| ( OP CODE )  STORE
	    0000     |             00000001           	|	1110   
	
*/

using namespace std;

/*
	CACHE - 4 palavras, 4 linhas
	tag = 16 - ( 2 + 2 ) = 12 bits
*/

struct cache
{
	unsigned int tag;
	bool bitValid;
	unsigned int dados[4]; 
	bitValid = 0;
};

unsigned int Pc;
unsigned int Reg1;
unsigned int Reg2;
unsigned int RegDest;
unsigned int tipoInstruc;
unsigned int Instruc;
unsigned int RegMemo;
unsigned int Reg[10];

cache memoriaCache[4];

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

void validaCache(void)
{
	int aux;
	
	aux = Pc & 0b0000000000001111;
	
	switch(aux)
	{
		case 0:
			if(memoriaCache[0].bitValid)
			{
				if(memoriaCache[0].tag == )
				
			}
			else
			{
				carregaCache();
			}
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
	}
}

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
		Instruc = validaCache[Pc]; // memoriaProgram[Pc] -> buscaCache[Pc]
		Pc++;
		decode();   
		execute();
	}

	return 0;
}

/*
	cache recebe Pc, na função buscaCache a cache irá validar a tag e o bit de validação, com isso irá saber em qual
	linha e qual palavra buscar 
	0b 0000 0000 0000 tag |00 2 bits de linha |00 2 bits de word , se o bit de validação for 0, carregar na memoria 
	principal , segundo teste -> tag lida = tag buscada, se sim -> 
*/