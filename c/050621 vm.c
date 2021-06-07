/*
A bytecode interpeter that can perform simple mathematical operations and ternary logic
It can print the result to the console using the Print opcode
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define STACK_DEPTH 255

typedef enum {
	Const,
	Add,
	Sub,
	Mul,
	Div,
	Gt,
	Lt,
	Gte,
	Lte,
	Eq,
	Select,
	Print,
} OpKind;

typedef struct {
	OpKind kind;
	int arg;
} Opcode;

typedef struct {
	int values[STACK_DEPTH];
	int pc;
} Stack;

void stack_push(Stack *stack, int v) { stack->values[stack->pc++] = v; }

int stack_pop(Stack *stack) { return stack->values[--stack->pc]; }

int stack_peek(Stack *stack) { return stack->values[stack->pc - 1]; }

vm_run(const Opcode *program, int programLen)
{
	Stack stack = {0};

	for (int i = 0; i < programLen; i++) {
		Opcode op = program[i];
		switch (op.kind) {
		case Const: stack_push(&stack, op.arg); break;
		case Add: {
			assert(stack.pc >= 2 && "Add operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a + b;
			stack_push(&stack, c);
		} break;
		case Sub: {

			assert(stack.pc >= 2 && "Sub operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a - b;
			stack_push(&stack, c);
		} break;
		case Mul: {
			assert(stack.pc >= 2 && "Mul operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a * b;
			stack_push(&stack, c);
		} break;
		case Div: {
			assert(stack.pc >= 2 && "Div operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a / b;
			stack_push(&stack, c);
		} break;
		case Gt: {
			assert(stack.pc >= 2 && "Gt operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a > b;
			stack_push(&stack, c);
		} break;
		case Lt: {
			assert(stack.pc >= 2 && "Lt operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a < b;
			stack_push(&stack, c);
		} break;
		case Gte: {
			assert(stack.pc >= 2 && "Gte operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a >= b;
			stack_push(&stack, c);
		} break;
		case Lte: {
			assert(stack.pc >= 2 && "Lte operation requires two arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int c = a <= b;
			stack_push(&stack, c);
		} break;
		case Select: {
			assert(stack.pc >= 3 && "Select operation requires three arguments on the stack");
			int b = stack_pop(&stack);
			int a = stack_pop(&stack);
			int cond = stack_pop(&stack);
			int c = cond ? a : b;
			stack_push(&stack, c);
		} break;
		case Print: {
			assert(stack.pc >= 1 && "Print operation requires one arguments on the stack");
			int a = stack_peek(&stack);
			printf("VM:Print %d\n", a);
		} break;

		default:
			printf("Unhandled kind %d\n", op.kind);
			exit(1);
			break;
		}
	}

	printf("Stack size: %d\n", stack.pc);
	if (stack.pc > 0) {
		printf("Top: %d\n", stack_pop(&stack));
	}
}

void main()
{
	Opcode program[] = {
		{Const, 10}, {Const, 20}, {Gt}, {Const, 11}, {Const, 22}, {Select}, {Print},
	};

	int programLength = sizeof(program) / sizeof(Opcode);

	vm_run(program, programLength);
}
