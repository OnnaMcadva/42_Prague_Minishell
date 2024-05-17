/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:42 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/17 13:05:25 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_com_cd_set_pwd(t_data *data, char *arg)
{
	int		ret;
	char	*temp;
	char	dir[PATH_MAX];
	char	*s;

	ret = mns_env_change(data, "OLDPWD", mns_getenv(data->env_copy, "PWD"));
	if (ret == MNS_ERROR)
	{
		temp = ft_strjoin("OLDPWD=", arg);
		mns_env_add(data, temp);
		free (temp);
	}
	s = getcwd(dir, PATH_MAX);
	if (!s)
	{
		perror("Error getting pwd");
		return (EXIT_FAILURE);
	}
	return (mns_env_change(data, "PWD", dir));
}

int	mns_com_cd(t_data *data, char *arg)
{
	int	ret;

	if (!arg || ft_strcmp(arg, "~") == 0)
		ret = chdir(mns_getenv(data->env_copy, "HOME"));
	else if (ft_strcmp(arg, "-") == 0)
		ret = chdir(mns_getenv(data->env_copy, "OLDPWD"));
	else
		ret = chdir(arg);
	if (ret == MNS_ERROR || mns_com_cd_set_pwd(data, arg) != ALL_FINE)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror (arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
