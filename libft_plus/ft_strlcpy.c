/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:56:46 by mmakagon          #+#    #+#             */
/*   Updated: 2023/03/16 00:03:26 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < maxlen)
		ft_memcpy(dst, src, srclen + 1);
	else if (maxlen != 0)
	{
		ft_memcpy(dst, src, maxlen - 1);
		dst[maxlen - 1] = '\0';
	}
	return (srclen);
}
