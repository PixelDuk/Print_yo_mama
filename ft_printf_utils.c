/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgankhuy <dgankhuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:19:52 by dgankhuy          #+#    #+#             */
/*   Updated: 2026/10/29 14:18:40 by dgankhuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	put_hex(unsigned long n, char con)
{
	int		digit;
	char	c;
	int		i;

	i = 0;
	if (n >= 16)
		i = i + put_hex(n / 16, con);
	digit = n % 16;
	if (con == 'x' || con == 'p')
	{
		if (digit < 10)
			c = '0' + digit;
		else
			c = 'a' + (digit - 10);
		write(1, &c, 1);
	}
	else
	{
		if (digit < 10)
			c = '0' + digit;
		else
			c = 'A' + (digit - 10);
		write(1, &c, 1);
	}
	return (i + 1);
}

int	print_sign_num(int n)
{
	long			x;
	unsigned int	y;
	int				i;

	i = 0;
	x = (long)n;
	if (n < 0)
	{
		write(1, "-", 1);
		x = x * -1;
		i = 1;
	}
	y = (unsigned int)x;
	i = print_num(y) + i;
	return (i);
}

int	print_num(unsigned int n)
{
	unsigned int	x;
	char			c;
	int				i;

	i = 0;
	if (n >= 10)
	{
		i = i + print_num(n / 10);
	}
	x = n % 10;
	c = '0' + x;
	write(1, &c, 1);
	return (i + 1);
}
