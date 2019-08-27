#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int flag=0;
#define MOVE 0
#define ADD 1
#define SUB 2
#define BRA 3
#define CMP 4
#define BEQ 5
#define BNE 6
#define EXG 7
#define STOP 15
//ifstream myfile ("Instructions.txt");
unsigned short int PC = 0; /* program counter */
unsigned short int D0 = 0; /* data register */
unsigned short int A0 = 0; /* address register */
unsigned short int CCR = 0; /* condition code register */
unsigned short int MAR; /* memory address register */
unsigned short int MBR; /* memory buffer register */
unsigned short int IR; /* instruction register */
unsigned short int operand; /* the 8-bit operand from the IR */
unsigned short int source = 0; /* source operand */
unsigned short int destination = 0; /* the destination value */
unsigned short int opcode; /*the 4-bit op-code from the IR */
unsigned short int amode; /*the 2-bit addressing mode */
unsigned short int direction; /*the 1-bit data direction flag */
unsigned short int memory[256]= {20, 4, 21, 4, 15, 10, 255, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; /*the memory */
unsigned short int location=0; /* The memory location						*/
unsigned short int run = 1; /*execute program while run is 1 */
void print(int x)
{
    string s;
    stringstream ss;
    for(int i=0; i<8; i++)ss<<(x&1),x>>=1;
    s=ss.str();
    reverse(s.begin(),s.end());

    cout<<s<<endl;

}
void Read()
{
    unsigned short int dir=0,inst=0,add_ress,mode=0;
    string code,operation,source;
    getline(cin,code);
    int position = code.find(" ");
    operation=code.substr(0,position);//Get operation from code
    source=code.substr(position+1,code.length()-position);//Get source from code
    dir=*(operation.end()-1)-'0';
    operation=operation.substr(0,operation.length()-1);//remove direction character from end of opcode

    if(operation=="MOVE")inst=MOVE;
    else if(operation=="ADD")inst=ADD;
    else if(operation=="SUB")inst=SUB;
    else if(operation=="BRA")inst=BRA;
    else if(operation=="CMP")inst=CMP;
    else if(operation=="BEQ")inst=BEQ;
    else if(operation =="BNE")inst=BNE;
    else if(operation == "EXG")inst=EXG;
    else if(operation == "STOP")inst=STOP;
    if(source[0]=='#')mode=1,add_ress=atoi(source.substr(1,source.length()-1).c_str());
    else if(source[0]=='A')mode=2,add_ress=atoi(source.substr(3,source.length()-4).c_str());
    else if(source[0]=='P')mode=3,add_ress=atoi(source.substr(3,source.length()-4).c_str());
    else mode=0,add_ress=atoi(source.c_str());

    memory[location++]=(inst<<4) | (dir<<2) | mode; //Bitwise shift
    print(memory[location-1]);
    memory[location++]=add_ress;//put operand into next byte in memory
    print(memory[location-1]);
}
void ReadFile(string code)
{
    unsigned short int dir=0,inst=0,add_ress,mode=0;
    string operation,source;



    int position = code.find(" ");
    operation=code.substr(0,position);//Get operation from code
    source=code.substr(position+1,code.length()-position);//Get source from code
    dir=*(operation.end()-1)-'0';
    operation=operation.substr(0,operation.length()-1);//remove direction character from end of opcode

    if(operation=="MOVE")inst=MOVE;
    else if(operation=="ADD")inst=ADD;
    else if(operation=="SUB")inst=SUB;
    else if(operation=="BRA")inst=BRA;
    else if(operation=="CMP")inst=CMP;
    else if(operation=="BEQ")inst=BEQ;
    else if(operation =="BNE")inst=BNE;
    else if(operation == "EXG")inst=EXG;
    else if(operation == "STOP")inst=STOP;
    if(source[0]=='#')mode=1,add_ress=atoi(source.substr(1,source.length()-1).c_str());
    else if(source[0]=='A')mode=2,add_ress=atoi(source.substr(3,source.length()-4).c_str());
    else if(source[0]=='P')mode=3,add_ress=atoi(source.substr(3,source.length()-4).c_str());
    else mode=0,add_ress=atoi(source.c_str());
    cout<<code<<"\n";
    memory[location++]=(inst<<4) | (dir<<2) | mode; //Bitwise shift
    cout<<"IR= ";
    print(memory[location-1]);
    memory[location++]=add_ress;//put operand into next byte in memory
    cout<<"Operand= ";
    print(memory[location-1]);

}

void start(){
 char c;
   cout<<"WELCOME TO ICY_Simulation Press S to Start the FUN";
cin>>c;
if (c=='s'||'S'){
         ifstream file("Instructions.txt");
    string in;
    while(getline(file,in))
    {

        ReadFile(in);

    }
    file.close();
    }
    else
        cout<<"Press S STUPID!";
}


int main()
{
cout<<"WELCOME TO ICY_Simulation Press S to Start the FUN\n";

         ifstream file("Instructions.txt");
    string in;
    while(getline(file,in))
    {

        ReadFile(in);

    }
    file.close();


    /* Instruction format:
     7 6 5 4 3 2 1 0
     Bit 1 and 0 2-bit address mode
     00 address mode = absolute
     01 address mode = literal
     10 address mode = indexed
     11 address mode = relative
     Bit 2 1-bit direction (source/operand)
     Bit 3 not used
     Bit 7 to 4 4-bit instruction code
     */


    /* main loop */
    while (run )
    {
        //Read();
//        ReadFile();
        MAR = PC;            /* PC to MAR */
        PC = PC + 1;         /* increment PC*/
        MBR = memory[MAR];   /* get next instruction*/
        IR = MBR;            /*copy MBR to IR*/
        opcode = IR;         /*store the op-code bits*/

        MAR = PC;            /*PC to MAR*/
        PC = PC + 1;         /*increment PC*/
        MBR = memory[MAR] ;  /*get the operand*/
        IR = MBR;            /*copy MBR to IR*/
        operand = IR;        /*store the operand bits*/

        amode = opcode & 0x03; /*extract the address mode bits*/
        direction = (opcode & 0x04)>>2;  /*get data direction 0 = register to memory 1= memory to register */
        opcode = opcode >> 4; /* get the 4-bit instruction code*/

        /* use the address mode to get the source operand */
        switch (amode)
        {
        case 0:
        {
            source = memory[operand];    /* absolute */             break;
        }
        case 1:
        {
            source = operand;    /* literal */                      break;
        }
        case 2:
        {
            source = memory[A0 + operand];    /* indexed */         break;
        }
        case 3:
        {
            source = memory[PC + operand];    /* PC relative */     break;
        }
        }

        /* now execute the instruction */

        switch (opcode)
        {
        case MOVE:
        {
            if (direction == 0) destination = D0;
            else D0 = source;

            if (D0 == 0) CCR = 1;
            else CCR = 0; /* update CCR */
            break;
        }
        case ADD:
        {
            if (direction == 0)
            {
                destination = D0 + source;
                if (destination == 0) CCR = 1;
                else CCR = 0;
            }
            else
            {
                D0 = D0 + source;
                if (D0 == 0 ) CCR = 1;
                else CCR = 0;
            }
            break;
        }
        case SUB:
        {
            if (direction == 0)
            {
                destination = D0 - source;
                if (destination == 0) CCR = 1;
                else CCR = 0;
            }
            else
            {
                D0 = D0 - source;
                if (D0 == 0 ) CCR = 1;
                else CCR = 0;
            }
            break;
        }
        case BRA:
        {
            if (amode ==0) PC = operand;
            if (amode ==1) PC = PC + operand;
            break;
        }
        case CMP:
        {
            MBR = D0 - source;
            if (MBR == 0) CCR = 1;
            else CCR = 0;
            break;
        }
        case BEQ:
        {
            if (CCR == 1)
            {
                if (amode ==0) PC = operand;
                if (amode ==1) PC = PC + operand;
            }
            break;
        }
        case BNE:
        {
            if (CCR != 1)
            {
                if (amode ==0) PC = operand;
                if (amode == 1) PC = PC + operand;
            }
            break;
        }
        case EXG:
        {
            MBR = D0;
            D0 = A0;
            A0 = MBR;
            break;
        }
        case STOP:
        {
            run = 0;
            break;
        }
        }
        /* save result in memory if register to memory */
        if (direction == 0)
        {
            switch (amode)
            {
            case 0:
            {
                memory[operand] = destination;
                break; /* absolute */
            }
            case 1:
            {
                break; /* literal */
            }
            case 2:
            {
                memory[A0 + operand] = destination ;
                break; /* indexed*/
            }
            case 3:
            {
                memory[PC + operand] = destination ;
                break; /* PC relative */
            }
            }
        }
        cout<<" D0: ne "<<D0<<" A0"<<A0<<" PC: "<<PC<<" CCR: "<<CCR<<endl;


        /*
        printf("PC = %d\n",PC);
        printf("Source = %d\n",source);
        printf("D0 = %d\n",D0);
        printf("CCR = %d\n\n",CCR);*/
    }


    return 0;
}

