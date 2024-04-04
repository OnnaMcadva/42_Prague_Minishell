/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:09:15 by mmakagon          #+#    #+#             */
/*   Updated: 2023/10/13 13:11:46 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*new_dest;

	if (!dest && !src)
		return (NULL);
	new_dest = dest;
	while (*new_dest != '\0')
		new_dest++;
	while (*src != '\0')
		*new_dest++ = *src++;
	*new_dest = '\0';
	return (dest);
}
