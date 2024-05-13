/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:00:49 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/13 14:47:23 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_hex_len(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	pf_put_hex(unsigned int num, const char format)
{
	if (num >= 16)
	{
		pf_put_hex(num / 16, format);
		pf_put_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	pf_print_hex(va_list args, const char format)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	if (num == 0)
		return (write(1, "0", 1));
	else
		pf_put_hex(num, format);
	return (pf_hex_len(num));
}
