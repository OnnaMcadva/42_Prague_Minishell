/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_env_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:40:33 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/20 21:44:38 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Прототип функции обмена строк */
void swap_strings(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

/* Функция пузырьковой сортировки */
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

/* Функция печатает переменные окружения по алфавиту */
void    print_env_by_abc(char **env)
{
	char	*tmp_key;
	char	*tmp_value;
	int	i;

	i = -1;
    bubble_sort(env, mns_util_tablen(env));
	while (env[++i])
	{
		tmp_key = extract_env_key(env[i]);
		tmp_value = extract_value_from_env_string(env[i]);
		write(1, "declare -x ", 12);
		write(1, tmp_key, ft_strlen(tmp_key));
		write(1, "=\"", 3);
		write(1, tmp_value, ft_strlen(tmp_value));
		ft_putendl_fd("\"", STDOUT_FILENO);
		free(tmp_key);
		free(tmp_value);
	}
}
