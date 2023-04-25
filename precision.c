#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/**
* print_char - Prints a char
*
* @args: Arguments passed from main
*
* Return: 1, always
*/
int print_char(va_list args)
{
putchar(va_arg(args, int));
return (1);
}

/**
* print_string - Prints a string
*
* @args: Arguments passed from main
*
* Return: Length of string
*/
int print_string(va_list args)
{
int i, count = 0;
char *str = va_arg(args, char *);

if (!str)
str = "(null)";

for (i = 0; str[i]; i++)
{
putchar(str[i]);
count++;
}
return (count);
}

/**
* print_integer - Prints an integer
*
* @args: Arguments passed from main
*
* Return: Length of integer
*/
int print_integer(va_list args)
{
int count = 0, neg = 0, min_int = 0;
long int num = va_arg(args, int);

if (num < 0)
{
neg = 1;
num *= -1;
count++;
}

if (num == -2147483648)
{
num++;
min_int = 1;
}

if (num / 10)
count += print_integer_helper(num / 10);

if (min_int == 1)
{
putchar('8');
count++;
}
else
{
putchar((num % 10) + '0');
count++;
}

if (neg == 1)
{
putchar('-');
count++;
}
return (count);
}

/**
* print_percent - Prints a percent symbol
*
* @args: Arguments passed from main
*
* Return: 1, always
*/
int print_percent(va_list args)
{
putchar('%');
(void)args;
return (1);
}

/**
* _printf - Our implementation of printf
*
* @format: String of format to print
*
* Return: Length of format string printed
*/
int _printf(const char *format, ...)
{
int i, j, count = 0;
va_list args;

print_t types[] = {
{'c', print_char},
{'s', print_string},
{'i', print_integer},
{'d', print_integer},
{'%', print_percent},
{'\0', NULL},
};

va_start(args, format);

for (i = 0; format[i]; i++)
{
if (format[i] == '%')
{
i++;
while (format[i] == ' ')
i++;

for (j = 0; types[j].type != '\0'; j++)
{
if (format[i] == types[j].type)
{
count += types[j].f(args);
break;
}
}
}
else
{
putchar(format[i]);
count++;
}
}
va_end(args);
return (count);
}
