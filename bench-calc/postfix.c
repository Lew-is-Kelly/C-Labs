#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#include "postfix.h"

bool is_operator(char *token)
{
  char ops[] = "+-X/^";
  int nops = 4;
  if (strlen(token) == 1)
  {
    for (int i = 0; i < nops-1; i++)
    {
      if (token[0] == ops[i])
      {
        return true;
      }
    }
  }
  return false;
}

bool is_operand(char *token)
{
  for (int i = 0; i < strlen(token); i++)
  {
    if (isdigit(token[i]))
    {
      return true;
    }
  }
  return false;
}

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char **args, int nargs)
{
  struct double_stack *stack = double_stack_new(nargs);
  for (int i = 0; i < nargs; i++)
  {
    if (is_operand(args[i]))
    {
      char *ptr;
      double_stack_push(stack, strtod(args[i], &ptr));
    }
    else
    {
      double op2 = double_stack_pop(stack);
      double op1 = double_stack_pop(stack);
      char op = args[i][0];
      if (args[i][0] == 'X')
      {
        double_stack_push(stack, op1 * op2);
      }
      else if (op == '+')
      {
        double_stack_push(stack, op1 + op2);
      }
      else if (op == '-')
      {
        double_stack_push(stack, op1 - op2);
      }
      else if (op == '/')
      {
        double_stack_push(stack, op1 / op2);
      }
      else if (op == '^')
      {
        double_stack_push(stack, pow(op1, op2));
      }
    }
  }
  return double_stack_pop(stack);
}
