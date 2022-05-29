#include <stdio.h>
#include <string.h>
#include "strutils.h"

void fg_color(char* color)
{
	if (streq("yellow", color)) {
		printf("\033[1;33m");
	} else
	if (streq("cyan", color)) {
		printf("\033[1;36m");
	}
}

int streq(char* str1, char* str2)
{
	return (strcmp(str1, str2) == 0);
}

void reset_color()
{
	printf("\033[0m");
}
