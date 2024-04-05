/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:00:51 by mmakagon          #+#    #+#             */
/*   Updated: 2023/10/13 13:06:45 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_print_integer(va_list args)
{
	char	*str;
	size_t	len;
	int		i;

	i = va_arg(args, int);
	len = ft_strlen((str = ft_itoa(i)));
	write (STDOUT_FILENO, str, len);
	free (str);
	return (len);
}
