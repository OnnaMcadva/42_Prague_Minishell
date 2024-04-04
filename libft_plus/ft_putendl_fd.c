/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:04:19 by mmakagon          #+#    #+#             */
/*   Updated: 2023/03/13 15:26:08 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (s && *s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	ft_putchar_fd('\n', fd);
}
