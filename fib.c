#include <stdio.h>
#include "strutils.h"
#include <time.h>

enum calculationMethod {
	RECURSION,
	GOTOLOOP
};


typedef struct fibNum fibNum;

struct fibNum {
	double num;
	double a;
	double b;
};

typedef struct calculationResult calculationResult;

struct calculationResult {
	double value;
	double elapsed_time;
};

void print_header(int repetitions);
calculationResult loop_calculate(int repetitions, void (*fib_fun)(fibNum* fn));
void (*get_fib_fun(enum calculationMethod calc_method))(fibNum* fn);
void fib_recursion(fibNum* fn);
void fib_goto(fibNum* fn);
void print_result(calculationResult recur_result, calculationResult goto_result);

int main()
{
	int repetitions = 1000;
	calculationResult recur_result, goto_result;

	print_header(repetitions);

	printf("- Normal recursion\n");
	recur_result = loop_calculate(repetitions, get_fib_fun(RECURSION));

	printf("- Goto loop\n");
	goto_result = loop_calculate(repetitions, get_fib_fun(GOTOLOOP));

	print_result(recur_result, goto_result);
}

void print_header(int repetitions)
{
	fg_color("cyan");
	printf("Calculating the 1000th Fibonacci number %dx with two different methods:\n", repetitions);
	reset_color();
}

calculationResult loop_calculate(int repetitions, void (*fib_fun)(fibNum* fn))
{
	calculationResult r = { 0.0, 0.0  };
	fibNum fn;
	clock_t t;
	t = clock();
	for (int i = 0; i < repetitions; i++) {
		fn.num = 1000.0;
		fn.a = 0.0;
		fn.b = 1.0;
		fib_fun(&fn);
	}
	t = clock() - t;
	r.value = fn.num;
	r.elapsed_time = ((double)t) / CLOCKS_PER_SEC / repetitions;
	return r;
}

void (*get_fib_fun(enum calculationMethod calc_method))(fibNum* fn)
{
	if (calc_method == GOTOLOOP) {
		return fib_goto;
	} else {
		return fib_recursion;
	}
}

void fib_recursion(fibNum* fn)
{
	if ((*fn).num == 1.0) {
		(*fn).num = (*fn).b;
		return;
	}
	(*fn).num = (*fn).num - 1;
	double a = (*fn).b;
	(*fn).b += (*fn).a;
	(*fn).a = a;
	fib_recursion(fn);
}

void fib_goto(fibNum* fn)
{
chk:	if ((*fn).num == 1.0) {
		(*fn).num = (*fn).b;
		return;
	}
	(*fn).num = (*fn).num - 1;
	double a = (*fn).b;
	(*fn).b += (*fn).a;
	(*fn).a = a;
	goto chk;
}

void print_result(calculationResult recur_result, calculationResult goto_result)
{
	char* winner;
	char* looser;
	double speed_factor;

	printf("\n");
	printf("Normal recursion result: %.14e\n", recur_result.value);
	printf("Goto loop result:        %.14e\n", goto_result.value);
	printf("\n");
	printf("Normal recursion average time consumption: %.6f ms\n", recur_result.elapsed_time * 1000);
	printf("Goto loop average time consumption:        %.6f ms\n", goto_result.elapsed_time * 1000);
	printf("\n");
	
	if (recur_result.elapsed_time > goto_result.elapsed_time) {
		winner = "Goto loop";
		looser = "Normal recursion";
		speed_factor = recur_result.elapsed_time / goto_result.elapsed_time;
	} else {
		winner = "Normal recursion";
		looser = "Goto loop";
		speed_factor = goto_result.elapsed_time / recur_result.elapsed_time;
	}
	fg_color("yellow");
	printf("%s is about %.2f times faster than %s\n", winner, speed_factor, looser);
	reset_color();
}
