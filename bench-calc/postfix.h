#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#include "stack.h"

double evaluate_postfix_expression(char ** expr, int nterms);
bool is_operator(char *token);
bool is_operand(char *token);

#endif
