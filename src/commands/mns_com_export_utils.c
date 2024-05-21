/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:40:33 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 19:31:10 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void swap_strings(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void bubble_sort(char **array, int rows)
{
    int i;

    i = 0;
	if (array)
	{
		while (i < rows - 1)
		{
			int j = 0;
			while (j < rows - i - 1)
			{
				if (ft_strcmp(array[j], array[j + 1]) > 0)
					swap_strings(&array[j], &array[j + 1]);
				j++;
			}
			i++;
		}
	}
}

char **copy_env_copy(char **env)
{
    int i;
	int len;
    char **copy;

    len = mns_util_tablen(env);
    copy = (char **)malloc((len + 1) * sizeof(char *));
    if (!copy)
        return (perror("malloc"), NULL);
    i = 0;
    while (i < len)
	{
        copy[i] = ft_strdup(env[i]);
        if (!copy[i])
		{
            while (i > 0)
                free(copy[--i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[len] = NULL;
    return (copy);
}

int     is_look_like_key(char *args, t_data *data)
{
    int i;
    char *tmp_key;

    if (!ft_isalpha(args[0]) && args[0] != '_')
        return (0);
    i = 1;
    while (args[i] && args[i] != '=')
    {
        if (!ft_isalnum(args[i]) && args[i] != '_')
            return (0);
        i++;
    }
    tmp_key = extract_env_key(args);
    mns_env_delete(data, tmp_key);
    mns_env_add(data, args);
    free(tmp_key);
    return (1);
}
