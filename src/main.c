
#include <stdio.h>

typedef enum {
	PUSH,
	POP,
	SET,
	ADD,
  DIV,
  AND,
	HLT
} InstructionSet;

typedef enum {
	A, B, C, D, E, F,
	NUM_REGISTERS // enum will set this automatically to the number of registers
} Registers;

const int program[] = {
  PUSH, 0, // push 5 and 6 onto stack
  PUSH, 0,
  ADD, // POP 5 and 6 and add them together, push the result back on the stack
  POP, // POP the result from the stack
  HLT // Halt the program
};
int ip = 0; // instruction pointer
int sp = -1; // stack pointer is always index of last element
int stack[256];
int registers[NUM_REGISTERS];


void eval(int instr);
int fetch();


int main(){
  int instr = program[ip];
  while (instr != HLT){
    instr = fetch(); // get the current instruction
    eval(instr); // evaluate the instruction
    ip++; // increment the instruction pointer to the next instruction
  }

  return 0;
}

void eval(int instr){
  switch (instr) {
    case PUSH:;
      sp++;
      stack[sp] = program[++ip];
      break; // switch statements will run all the way down if not broken

    case POP:;
      printf("%d\n", stack[sp]);
      int val = stack[sp];
      sp--;
      break;

    case ADD:;
      int firstNum = stack[sp]; // pop first number
      sp--; // move stack pointer down one
      int secondNum = stack[sp]; // pop second number
      sp--; // move stack pointer down
      int sum = firstNum + secondNum; // calculate sum
      sp++;
      stack[sp] = sum; // move stack pointer up and then push the sum
      break;

    case DIV:;
      int dividend = stack[sp];
      sp--;
      int divisor = stack[sp];
      sp--;
      int quotient = dividend / divisor;
      sp++;
      stack[sp] = quotient;
      break;
   case SET:;
       registers[program[ip + 1]] = program[ip + 2];
       /*
        program[ip] is at SET, program[ip + 1] is the register,
        and program[ip + 2] is the value
				EXAMPLE:
				{
				SET, A, 15,
				HLT
			  }
       */
       break;
   case AND:; // pops two values from stack and evaluates the condition
        int cond1 = stack[sp];
        sp--;
        int cond2 = stack[sp];
        sp--;
        int isAnd = cond1 && cond2;
        sp++;
        stack[sp] = isAnd; // store answer in stack
        break;



  }
}

int fetch() {
  return program[ip]; // returns current instruction
}
