/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:42 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/16 09:13:19 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_com_cd(char **envp, char *arg)
{
	int	ret;

	if (!arg || ft_strcmp(arg, "~") == 0)
		ret = chdir(mns_getenv(envp, "HOME"));
	else if (ft_strcmp(arg, "-") == 0)
		ret = chdir(getenv("OLDPWD"));
	else
		ret = chdir(arg);
	if (ret == MNS_ERROR)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror (arg);
		return (1);
	}
	return (0);
}
