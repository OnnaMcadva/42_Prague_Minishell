/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:24:47 by mmakagon          #+#    #+#             */
/*   Updated: 2023/03/21 23:47:00 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	ft_convert_to_char(int n)
{
	char	c;

	c = '0' + (n % 10);
	return (c);
}

static char	*ft_pos_itoa(int n)
{
	char	*s;
	int		len;

	len = ft_count_len (n);
	s = (char *) malloc ((len + 1) * sizeof (char));
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (len)
	{
		s[len - 1] = ft_convert_to_char (n);
		n = n / 10;
		len--;
	}
	return (s);
}

static char	*ft_neg_itoa(int n)
{
	char	*s;
	int		len;

	n = n * -1;
	len = ft_count_len (n);
	s = (char *) malloc ((len + 2) * sizeof (char));
	if (!s)
		return (NULL);
	s[len + 1] = '\0';
	while (len)
	{
		s[len] = ft_convert_to_char (n);
		n = n / 10;
		len--;
	}
	s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;

	if (n == -2147483648)
	{
		s = (char *) malloc (12 * sizeof (char));
		if (!s)
			return (NULL);
		ft_memcpy (s, "-2147483648\0", 12);
		return (s);
	}
	else if (n == 0)
	{
		s = (char *) malloc (2 * sizeof (char));
		if (!s)
			return (NULL);
		ft_memcpy (s, "0\0", 2);
		return (s);
	}
	else if (n < 0)
		s = ft_neg_itoa (n);
	else
		s = ft_pos_itoa (n);
	if (!s)
		return (NULL);
	return (s);
}
