/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:02 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 19:35:18 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_env_key(char *str)
{
	size_t	i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, str, i + 1);
	return (key);
}

char	*extract_value_from_env_string(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	if (i >= len)
		return (NULL);
	i++;
	return (ft_strdup(&str[i]));
}

void	print_sorted_env(char **env_copy)
{
	char	*tmp_key;
	char	*tmp_value;
	int		i;

	i = 0;
	bubble_sort(env_copy, mns_util_tablen(env_copy));
	while (env_copy[i])
	{
		tmp_key = extract_env_key(env_copy[i]);
		tmp_value = extract_value_from_env_string(env_copy[i]);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp_key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(tmp_value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		free(tmp_key);
		free(tmp_value);
		i++;
	}
}

void	print_and_free_sorted_env(char **env)
{
	char	**env_copy_copy;
	int		i;

	env_copy_copy = copy_env_copy(env);
	if (!env_copy_copy)
	{
		ft_putendl_fd("Error: Unable to copy env. variables", STDERR_FILENO);
		return ;
	}
	print_sorted_env(env_copy_copy);
	i = 0;
	while (env_copy_copy[i])
	{
		free(env_copy_copy[i]);
		i++;
	}
	free(env_copy_copy);
}

int	mns_com_export(t_data *data, char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		return (print_and_free_sorted_env(data->env_copy), ALL_FINE);
	else
	{
		while (argv[i])
		{
			if (is_look_like_key(argv[i], data))
				data->exit_status = 0;
			else
			{
				ft_putstr_fd("export: ", STDERR_FILENO);
				ft_putstr_fd(argv[i], STDERR_FILENO);
				ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
			}
			i++;
		}
	}
	return (ALL_FINE);
}
