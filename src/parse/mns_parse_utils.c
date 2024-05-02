#include "../../includes/minishell.h"

/* Counts arguments for a parsed command,
	skips redirection operators (those will be set to a special string in parsed struct)*/
int	mns_parse_util_count_args(const char **splitted, const int *splitted_type)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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
			count++;
		}
	}
	return (count);
}

int	mns_parse_utils_cmd_type(char *command)
{
	int	len;

	len = ft_strlen(command);
	if (len == 2 && ft_strcmp(command, "cd") == 0)
		return (COM_CD | BUILTIN_EXEC);
	else if (len == 3 && ft_strcmp(command, "env") == 0)
		return (COM_ENV | BUILTIN_EXEC);
	else if (len == 3 && ft_strcmp(command, "pwd") == 0)
		return (COM_PWD | BUILTIN_EXEC);
	else if (len == 4 && ft_strcmp(command, "echo") == 0)
		return (COM_ECHO | BUILTIN_EXEC);
	else if (len == 4 && ft_strcmp(command, "exit") == 0)
		return (COM_EXIT | BUILTIN_EXEC);
	else if (len == 5 && ft_strcmp(command, "unset") == 0)
		return (COM_UNSET | BUILTIN_EXEC);
	else if (len == 6 && ft_strcmp(command, "export") == 0)
		return (COM_EXPORT | BUILTIN_EXEC);
	else if (strchr(command, SLASH))
		return (LOCAL_EXEC);
	else
		return (GLOBAL_EXEC);
}

void	mns_parse_util_assign_args(t_parsed *parsed, const char **splitted, const int *splitted_type)
{
	int	i;

	i = 0;
	while(splitted[i] && splitted_type[i] != PIPE)
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
		}
		if (!parsed->command)
		{
			parsed->command = (char *)splitted[0];
			parsed->type |= mns_parse_utils_cmd_type(parsed->command);
		}
		parsed->args[i] = (char *)splitted[i];
		i++;
	}
	parsed->args[i] = NULL;
}