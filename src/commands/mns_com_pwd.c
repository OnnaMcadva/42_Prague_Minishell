/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:10 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/13 14:27:50 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_com_pwd(void)
{
	char	dir[PATH_MAX];
	char	*s;

	s = getcwd(dir, PATH_MAX);
	if (!s)
		perror("Error getting pwd");
	else
		ft_putendl_fd(dir, STDOUT_FILENO);
}
