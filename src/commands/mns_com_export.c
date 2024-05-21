/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:02 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 15:12:32 by mmakagon         ###   ########.fr       */
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

void print_sorted_env(char **env_copy)
{
    char *tmp_key;
    char *tmp_value;
    int i = 0;

    bubble_sort(env_copy, mns_util_tablen(env_copy));
    while (env_copy[i])
    {
        tmp_key = extract_env_key(env_copy[i]);
        tmp_value = extract_value_from_env_string(env_copy[i]);
        write(1, "declare -x ", 12);
        write(1, tmp_key, ft_strlen(tmp_key));
        write(1, "=\"", 3);
        write(1, tmp_value, ft_strlen(tmp_value));
        ft_putendl_fd("\"", STDOUT_FILENO);
        free(tmp_key);
        free(tmp_value);
        i++;
    }
}

void print_and_free_sorted_env(char **env)
{
    char **env_copy_copy;
    int i;

    env_copy_copy = copy_env_copy(env);
    if (!env_copy_copy)
    {
        write(1, "Error: Unable to copy environment variables\n", 44);
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
	int i;

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
				write (1, "export: ", 9);
				ft_putstr_fd(argv[i], STDERR_FILENO);
				write (1, ": not a valid identifier\n", 26);
			}
			i++;
		}
	}
    return (ALL_FINE);
}
