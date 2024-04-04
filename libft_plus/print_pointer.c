/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:14:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/03 14:30:33 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_ptr_len(uintptr_t num)
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

void	pf_put_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		pf_put_ptr(num / 16);
		pf_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	pf_print_ptr(va_list args)
{
	unsigned long long	ptr;
	int					print_length;

	ptr = va_arg(args, unsigned long long);
	print_length = 0;
	if (!ptr)
		print_length += write(1, "(nil)", 5);
	else
	{
		print_length += write(1, "0x", 2);
		pf_put_ptr(ptr);
		print_length += pf_ptr_len(ptr);
	}
	return (print_length);
}
