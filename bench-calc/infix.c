#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#include "infix.h"

char* convert(char x)
{
  char * pointer = malloc(2*sizeof(char));
  pointer[0] = x;
  pointer[1] = '\0';
  return pointer;
}

// gives operators precedance
int precedence(char x)
{
  if (x == '+' || x == '-')
  {
    return 1;
  }
  if (x == 'X' || x == '/')
  {
    return 2;
  }
  if (x == '^')
  {
    return 3;
  }
  return 0;
}

// converts to postfix then passes to postfix.c

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char **args, int nargs)
{
  struct double_stack *stack1 = double_stack_new(nargs);

  int postfix_counter = 0;
  char **postfix_expression = malloc(sizeof(char *) * nargs);

  for (int i = 0; i < nargs; i++)
  {
    char *token = args[i];
    if (is_operand(token))
    {
      postfix_expression[postfix_counter++] = token;
    }
    else if (token[0] == '(')
    {
      double_stack_push(stack1, token[0]);
    }
    else if (token[0] == ')')
    {
      char ex;
      while ((ex = (char)double_stack_pop(stack1)) != '(')
      {
        postfix_expression[postfix_counter++] = convert(ex);
      }
    }
    else
    {
      while (precedence((char) double_stack_peek(stack1)) >= precedence(*token))
      {
        postfix_expression[postfix_counter++] = convert((char) double_stack_pop(stack1));
      }
      double_stack_push(stack1, *token);
    }
  }

  while (!is_empty(stack1))
  {
    postfix_expression[postfix_counter++] = convert((char) double_stack_pop(stack1));
  }
  return evaluate_postfix_expression(postfix_expression, postfix_counter);
}