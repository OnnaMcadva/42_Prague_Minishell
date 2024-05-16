/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:16 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/16 11:28:14 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Counts arguments for a parsed command,
	skips redirection operators
	(those will be set to a special string in parsed struct)*/
int	mns_parse_util_count_args(char **splitted,
								int *splitted_type,
								int *count)
{
	int	i;

	i = 0;
	while (splitted[i] && splitted_type[i] != PIPE)
	{
		if (splitted_type[i] == IN_OPERATOR
			|| splitted_type[i] == OUT_OPERATOR
			|| splitted_type[i] == OUT_APPEND_OPRTR)
		{
			i += 2;
		}
		else
		{
			i++;
			*count += 1;
		}
	}
	return (i);
}

int	mns_parse_utils_cmd_type(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (COM_CD | BUILTIN_EXEC);
	else if (ft_strcmp(command, "env") == 0)
		return (COM_ENV | BUILTIN_EXEC);
	else if (ft_strcmp(command, "pwd") == 0)
		return (COM_PWD | BUILTIN_EXEC);
	else if (ft_strcmp(command, "echo") == 0)
		return (COM_ECHO | BUILTIN_EXEC);
	else if (ft_strcmp(command, "exit") == 0)
		return (COM_EXIT | BUILTIN_EXEC);
	else if (ft_strcmp(command, "unset") == 0)
		return (COM_UNSET | BUILTIN_EXEC);
	else if (ft_strcmp(command, "export") == 0)
		return (COM_EXPORT | BUILTIN_EXEC);
	else if (ft_strchr(command, SLASH))
		return (LOCAL_EXEC);
	else
		return (GLOBAL_EXEC);
}

void	mns_parse_util_assign_args(t_parsed *parsed,
									t_data *data,
									char **splitted,
									int *splitted_type)
{
	int	i;

	i = 0;
	while (splitted[i] && splitted_type[i] != PIPE)
	{
		if (splitted_type[i] == IN_OPERATOR
			|| splitted_type[i] == OUT_OPERATOR
			|| splitted_type[i] == OUT_APPEND_OPRTR)
		{
			if (splitted_type[i] == IN_OPERATOR)
				parsed->redir_in = (char *)splitted[i + 1];
			else
				parsed->redir_out = (char *)splitted[i + 1];
			parsed->type |= splitted_type[i];
			splitted += 2;
			splitted_type += 2;
			if (i != 0)
				continue ;
		}
		if (!parsed->command)
		{
			parsed->command = (char *)splitted[0];
			parsed->type |= mns_parse_utils_cmd_type(parsed->command);
		}
		if (splitted_type[i] == ENV)
			parsed->args[i] = mns_getenv(data->env_copy, splitted[i]);
		else
			parsed->args[i] = splitted[i];
		i++;
	}
	parsed->args[i] = NULL;
}
