/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:13:45 by mmakagon          #+#    #+#             */
/*   Updated: 2023/03/22 14:05:44 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	size_t	b;

	if (nmemb == 0 || size == 0)
	{
		p = malloc(0);
		return (p);
	}
	else
	{
		b = nmemb * size;
		if (b / nmemb != size)
			return (NULL);
		p = malloc(nmemb * size);
		if (!p)
			return (NULL);
		ft_bzero(p, nmemb * size);
		return (p);
	}
}
