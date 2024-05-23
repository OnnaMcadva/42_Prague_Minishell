/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:16 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/23 01:36:23 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Counts arguments for a parsed command,
	skips redirection operators
	(those will be set to a special string in parsed struct)*/
int	mns_parse_util_count_args(char **splitted,
								int *spltd_type,
								int *count)
{
	int	i;

	i = 0;
	while (splitted[i] && spltd_type[i] != PIPE)
	{
		if (spltd_type[i] == IN_OPERATOR
			|| spltd_type[i] == HERE_DOC
			|| spltd_type[i] == OUT_OPERATOR
			|| spltd_type[i] == OUT_APPEND_OPRTR)
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

char	*mns_parse_util_heredoc(t_parsed *parsed, char *stop_word)
{
	char	*input;
	int		fd;

	(void)parsed;
	fd = open(HEREDOC_FILENAME, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == MNS_ERROR)
	{
		perror("heredoc");
		return (NULL);
	}
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, stop_word) == 0)
			break ;
		ft_putendl_fd(input, fd);
		free (input);
	}
	free (input);
	close (fd);
	return (HEREDOC_FILENAME);
}

void	mns_parse_util_assign_args(t_parsed *parsed, char **splitted, int *spltd_type)
{
	int	i;

	i = 0;
	while (splitted[i] && spltd_type[i] != PIPE)
	{
		if (spltd_type[i] == IN_OPERATOR || spltd_type[i] == HERE_DOC || spltd_type[i] == OUT_OPERATOR || spltd_type[i] == OUT_APPEND_OPRTR)
		{
			if (spltd_type[i] == IN_OPERATOR)
				parsed->redir_in = splitted[i + 1];
			else if (spltd_type[i] == HERE_DOC)
				parsed->redir_in = mns_parse_util_heredoc(parsed, splitted[i + 1]);
			else
				parsed->redir_out = splitted[i + 1];
			parsed->type |= spltd_type[i];
			splitted += 2;
			spltd_type += 2;
			continue ;
		}
		if (!parsed->command)
		{
			parsed->command = splitted[0];
			parsed->type |= mns_parse_utils_cmd_type(parsed->command);
		}
		parsed->args[i] = splitted[i];
		i++;
	}
	parsed->args[i] = NULL;
}
