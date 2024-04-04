/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:00:58 by mmakagon          #+#    #+#             */
/*   Updated: 2023/10/13 13:06:33 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pf_unsigned_len(unsigned int n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	pf_unsigned_to_char(unsigned int n)
{
	char	c;

	c = '0' + (n % 10);
	return (c);
}

static char	*pf_unsigned_itoa_process(unsigned int n)
{
	char		*s;
	size_t		len;

	len = pf_unsigned_len (n);
	s = (char *) malloc ((len + 1) * sizeof (char));
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (len)
	{
		s[len - 1] = pf_unsigned_to_char (n);
		n = n / 10;
		len--;
	}
	return (s);
}

char	*pf_unsigned_itoa(unsigned int n)
{
	char	*s;

	if (n == 0)
	{
		s = (char *) malloc (2 * sizeof (char));
		if (!s)
			return (NULL);
		ft_memcpy (s, "0\0", 2);
		return (s);
	}
	else
		s = pf_unsigned_itoa_process (n);
	if (!s)
		return (NULL);
	return (s);
}

int	pf_print_unsigned(va_list args)
{
	char			*str;
	size_t			len;
	unsigned int	i;

	i = va_arg(args, unsigned int);
	len = ft_strlen((str = pf_unsigned_itoa(i)));
	write (STDOUT_FILENO, str, len);
	free (str);
	return (len);
}
