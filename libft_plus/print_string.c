/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:00:55 by mmakagon          #+#    #+#             */
/*   Updated: 2023/10/13 13:06:37 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_print_string(va_list args)
{
	size_t	len;
	char	*str;

	str = ft_strdup(va_arg(args, char *));
	if (str == NULL)
	{
		write (STDOUT_FILENO, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	write (STDOUT_FILENO, str, len);
	free (str);
	return (len);
}
