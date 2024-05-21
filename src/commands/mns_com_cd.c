/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:42 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 12:09:59 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_com_cd_set_pwd(t_data *data, char *arg)
{
	int		ret;
	char	*temp;
	char	dir[PATH_MAX];
	char	*s;

	if (ft_strcmp(arg, "-") != 0)
	{
		temp = mns_getenv(data->env_copy, "PWD");
		ret = mns_env_change(data, "OLDPWD", temp);
		if (ret == MNS_ERROR)
		{
			temp = ft_strjoin("OLDPWD=", arg);
			mns_env_add(data, temp);
			free (temp);
		}
	}
	s = getcwd(dir, PATH_MAX);
	if (!s)
	{
		perror("Error getting pwd");
		return (EXIT_FAILURE);
	}
	return (mns_env_change(data, "PWD", dir));
}

int	mns_com_cd_home(t_data *data)
{
	char	*ptr;

	ptr = mns_getenv(data->env_copy, "HOME");
	if (!ptr)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (MNS_ERROR);
	}
	return (chdir(ptr));
}

int	mns_com_cd(t_data *data, char *arg)
{
	int	ret;

	ret = ALL_FINE;
	if (!arg || ft_strcmp(arg, "~") == 0)
	{
		ret = mns_com_cd_home(data);
		if (ret == MNS_ERROR)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		if (mns_getenv(data->env_copy, "OLDPWD"))
			ret = chdir(mns_getenv(data->env_copy, "OLDPWD"));
		else
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
	}
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
