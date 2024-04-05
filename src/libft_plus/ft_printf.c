/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:50:50 by mmakagon          #+#    #+#             */
/*   Updated: 2023/10/13 13:02:43 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_print_char(va_list args)
{
	unsigned char	c;

	c = va_arg(args, int);
	write (STDOUT_FILENO, &c, 1);
	return (1);
}

size_t	format_specifier(const char fmt, va_list args, size_t printlen)
{
	if (fmt == 'c')
		printlen += pf_print_char(args);
	else if (fmt == 'i' || fmt == 'd')
		printlen += pf_print_integer(args);
	else if (fmt == 's')
		printlen += pf_print_string(args);
	else if (fmt == 'p')
		printlen += pf_print_ptr(args);
	else if (fmt == 'u')
		printlen += pf_print_unsigned(args);
	else if (fmt == '%')
		printlen += write (STDOUT_FILENO, "%%", 1);
	else if (fmt == 'x' || fmt == 'X')
		printlen += pf_print_hex(args, fmt);
	return (printlen);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	size_t		printlen;

	va_start(args, fmt);
	printlen = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			printlen = format_specifier((char)*fmt, args, printlen);
		}
		else
			printlen += write (STDOUT_FILENO, fmt, 1);
		++fmt;
	}
	va_end(args);
	return (printlen);
}
