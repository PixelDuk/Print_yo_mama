/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgankhuy <dgankhuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 13:40:29 by dgankhuy          #+#    #+#             */
/*   Updated: 2026/10/29 14:02:34 by dgankhuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *conversion, ...);
int	con_type(va_list *args, char con);
int	ft_strlen(char *str);
int	con_c_s(va_list *args, char con);
int	con_p(va_list *args, char con);
int	con_d_i_u_x(va_list *args, char con);
int	put_hex(unsigned long n, char con);
int	print_sign_num(int n);
int	print_num(unsigned int n);

#endif