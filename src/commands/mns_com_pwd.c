/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:10 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/17 11:50:19 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_com_pwd(void)
{
	char	dir[PATH_MAX];
	char	*s;

	s = getcwd(dir, PATH_MAX);
	if (!s)
	{
		perror("Error getting pwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(dir, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
