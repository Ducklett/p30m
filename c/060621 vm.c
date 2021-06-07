/*
Failed attempt at implementing functions
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	Call,
	Add,
	Const,
	End,
	Ret,
} OpKind;

typedef struct {
	OpKind kind;
	int arg;
} Opcode;

Opcode func0[] = {{Call, 1}, {Const, 1}, {Add}, {End}};
Opcode func1[] = {{Const, 2}, {Ret}};
Opcode *program[] = {func0, func1};

typedef struct {
	int stack[255];
	int pc;
} Stack;

void stack_push(Stack *s, int v) { s->stack[s->pc++] = v; }
int stack_pop(Stack *s) { return s->stack[--s->pc]; }

Stack stack;

void main()
{
	int fn = 0;

	int i = 0;
	while (true) {
		Opcode op = program[fn][i];
		printf("OP: %d\n", op.kind);
		// if (stack.pc > 0)
		//     printf("TOP: %d\n", stack.stack[stack.pc - 1]);
		switch (op.kind) {
		case Call: {
			stack_push(&stack, i);
			stack_push(&stack, fn);

			fn = op.arg;
			i = 0;
			continue;
		} break;

		case Const: {
			int v = op.arg;
			printf("const %d\n", v);
			stack_push(&stack, v);
		} break;

		case Add: {
			int a = stack_pop(&stack);
			int b = stack_pop(&stack);
			int c = a + b;
			stack_push(&stack, c);
		} break;

		case End: {
			printf("Machine exited\n");
			printf("Stack size %d\n", stack.pc);
			if (stack.pc >= 1) {
				printf("Top: %d\n", stack.stack[stack.pc - 1]);
			}
			return;
		} break;

		case Ret: {
			int idx = stack_pop(&stack);
			int addr = stack_pop(&stack);
			printf("RET %d %d\n", addr, idx);
			fn = addr;
			i = idx;
		} break;

		default: printf("Unhandled case %d", op.kind); break;
		}
		i++;
	}
}
