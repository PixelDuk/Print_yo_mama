/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgankhuy <dgankhuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:29:43 by dgankhuy          #+#    #+#             */
/*   Updated: 2026/10/29 14:19:38 by dgankhuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *conversion, ...)
{
	va_list	args;
	int		i;
	int		n;

	va_start(args, conversion);
	i = 0;
	n = 0;
	while (conversion[i] != '\0')
	{
		if (conversion[i] == '%' && conversion[i + 1] != '\0')
			n = n + con_type(&args, conversion[++i]);
		else if (conversion[i] != '%')
		{
			write(1, &conversion[i], 1);
			n++;
		}
		else
			break ;
		i++;
	}
	va_end(args);
	return (n);
}

int	con_type(va_list *args, char con)
{
	if (con == 'c' || con == 's')
		return (con_c_s(args, con));
	else if (con == 'p')
		return (con_p(args, con));
	else if ((con == 'd' || con == 'i')
		|| (con == 'u' || con == 'x') || con == 'X')
		return (con_d_i_u_x(args, con));
	else if (con == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

int	con_c_s(va_list *args, char con)
{
	char	*y;
	char	x;

	if (con == 'c')
	{
		x = (char)va_arg(*args, int);
		write(1, &x, 1);
		return (1);
	}
	else
	{
		y = va_arg(*args, char *);
		if (y == NULL)
			y = "(null)";
		write(1, y, ft_strlen(y));
		return (ft_strlen(y));
	}
}

int	con_p(va_list *args, char con)
{
	unsigned long	x;
	int				i;

	x = (unsigned long)va_arg(*args, void *);
	if (x == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	i = put_hex(x, con);
	return (2 + i);
}

int	con_d_i_u_x(va_list *args, char con)
{
	int				x;
	int				i;
	unsigned int	y;

	if (con == 'd' || con == 'i')
	{
		x = va_arg(*args, int);
		i = print_sign_num(x);
	}
	else if (con == 'x' || con == 'X')
	{
		y = va_arg(*args, unsigned int);
		i = put_hex(y, con);
	}
	else
	{
		y = va_arg(*args, unsigned int);
		i = print_num(y);
	}
	return (i);
}
