/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:21:28 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/13 14:58:14 by mmakagon         ###   ########.fr       */
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
		return ((char *) s);
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
