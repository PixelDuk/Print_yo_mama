/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgankhuy <dgankhuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 14:28:53 by dgankhuy          #+#    #+#             */
/*   Updated: 2026/10/19 17:32:16 by dgankhuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

```
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void print_num(const char *conversion, ... );
```
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
		// else if (conversion[i] == 'd' || conversion[i] == 'i')   ITOA is needed here also declair the buffer tmp
		// {
		// 	int x = va_arg(args, int);
		// 	itoa(x, tmp, 10);
		// 	write(1, tmp, strlen(tmp));
		// }
		else if(conversion[i] == 'u')
		{
			unsigned int x = va_arg(args, unsigned int);
			printf("%u", x);
		}

		i++;
	}
	va_end(args);
}
```
int	main(void)
{
	print_num("csu", 'a', "helloworld!", 2);

	return	(0);
}
```