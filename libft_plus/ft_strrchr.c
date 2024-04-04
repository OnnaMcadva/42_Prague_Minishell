/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:21:28 by mmakagon          #+#    #+#             */
/*   Updated: 2023/03/22 00:16:24 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*newchar;
	size_t			i;
	unsigned char	ch;

	ch = (char)c;
	if (c == '\0')
	{
		i = ft_strlen(s);
		while (i)
		{
			s++;
			i--;
		}
		return (newchar = (char *) s);
	}
	if (s[0] == '\0')
		return (NULL);
	newchar = NULL;
	while (*s != '\0')
	{
		if (*s == ch)
			newchar = (char *)s;
		s++;
	}
	return ((char *)newchar);
}
