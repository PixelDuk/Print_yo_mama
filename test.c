/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgankhuy <dgankhuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 14:28:53 by dgankhuy          #+#    #+#             */
/*   Updated: 2026/10/20 15:52:30 by dgankhuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void print_num(const char *conversion, ... );
void put_hex2(unsigned long n);
void put_hex24(unsigned long n);

void print_num(const char *conversion, ... )
{
	int num_args = strlen(conversion);

	va_list args;
	va_start(args, conversion);

	int i = 0;
	while (i < num_args)
	{
		if(conversion[i] == 'c')
		{
			char x = (char)va_arg(args, int);
			write (1, &x, 1);
			write (1, "\n", 1);
		}
		else if(conversion[i] == 's')
		{
			char *x = va_arg(args, char *);
			write(1, x, strlen(x));
			write(1, "\n", 1);
		}
		else if(conversion[i] == 'p')
		{
			unsigned long x = (unsigned long)va_arg(args, void *);
			write(1, "0x", 2);
			put_hex2(x);
			write(1, "\n", 1);
		}
		// else if (conversion[i] == 'd' || conversion[i] == 'i')   ITOA is needed here also declair the buffer tmp
		// {
		// 	int x = va_arg(args, int);
		// 	itoa(x, tmp, 10);
		// 	write(1, tmp, strlen(tmp));
		// }
		// else if(conversion[i] == 'u')
		// {
		// 	unsigned int x = va_arg(args, unsigned int);
		// 	printf("%u", x);
		// }
		else if(conversion[i] == 'x')
		{
			unsigned int x = va_arg(args, unsigned int);
			put_hex2(x);
		}
		else if(conversion[i] == 'X')
		{
			unsigned int x = va_arg(args, unsigned int);
			put_hex24(x);
		}
		i++;
	}
	va_end(args);
}

int	main(void)
{
	// print_num("csu", 'a', "helloworld!", 2);
	// int j = 255 % 16;
	// int k = 255 / 16;

	// printf("%d\n", j);
	// printf("%d\n", k);

	// put_hex2(26);
	// write(1, "\n", 1);
	// put_hex2(255);
	// write(1, "\n", 1);
	// put_hex2(0);
	// write(1, "\n", 1);

	// int	x = 26;

	// print_num("p", &x);
	// write (1, "\n", 1);
	// printf("%p", (void *)&x);

	// int	x = -10;
	// int	y = 26;
	
	// print_num("X", x);
	// write (1, "\n", 1);
	// print_num("X", y);
	// write (1, "\n", 1);
	// printf("%X and %X", x, y);
	// write (1, "\n", 1);

	// int	x = 10;
	// put_hex24(x);
	// write (1, "\n", 1);
	// printf("%X", x);

	printf("%%\n");
	return	(0);
}

void put_hex2(unsigned long n)
{
	int	digit;
	char c;

	if (n >= 16)
		put_hex2(n/16);
	digit = n % 16;
	if (digit < 10)
		c = '0' + digit;
	else
		c = 'a' + (digit - 10);
	write(1, &c, 1);
}

void put_hex24(unsigned long n)
{
	int	digit;
	char c;

	if (n >= 16)
		put_hex24(n/16);
	digit = n % 16;
	if (digit < 10)
		c = '0' + digit;
	else
		c = 'A' + (digit - 10);
	write(1, &c, 1);
}