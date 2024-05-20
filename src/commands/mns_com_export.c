/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:02 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/20 12:39:59 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*Эта функция извлекает ключ переменной окружения из строки,
* остановившись при символе "="*/
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

/* Эта функция извлекает значение переменной из строки окружения.
* Она ищет знак равенства ('=') в строке, а затем возвращает
* подстроку после этого знака равенства как значение переменной.*/
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

/* Эта функция выводит список переменных окружения в формате
* declare -x KEY="VALUE" */
void	print_export_variables(t_data *data)
{
	char	**env;

	env = data->env_copy;
	if (!data || !data->env_copy)
	{
		write(1, "Error: Data or environment variables are NULL\n", 47);
		return ;
	}
	print_env_by_abc(env);
}

/*Функция mns_com_export обрабатывает команду "export" в мини-оболочке.
* Она принимает список аргументов командной строки и обновляет
* переменные окружения в соответствии с переданными значениями.*/
int	mns_com_export(t_data *data, char **argv)
{
	if (!argv[1])
		return (print_export_variables(data), ALL_FINE);
    return (ALL_FINE);
}

/*Для реализации команды export в вашем шелле, без поддержки дополнительных опций
* или флагов, основные функции, которые вам нужно написать, будут следующими:

*    Функция для обработки команды export.
*    Функция для добавления новой переменной окружения или изменения значения существующей переменной.
*    Функция для печати всех переменных окружения в отсортированном виде.*/
