# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include "../libft_plus/libft.h"

# define PROMPT "\x1B[36m[minishell] \x1B[35m[ =) ] \x1B[36m~> \x1B[0m"
// the lenght is 42 =)

# define META_CHARACTERS "|&;()<>"

enum e_delimiter
{
	WHITESPACE = ' ',
	TAB_SYMBOL = '\t',
	NEW_LINE = '\n',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	DOLLAR_SIGN = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
};

enum e_tkn_type
{
	NULL_TOKEN = 0,
	WORD,
	ENV,
	PIPE,
	IN_OPERATOR,
	HERE_DOC,
	OUT_OPERATOR,
	OUT_APPEND_OPRTR,
	GLOBAL_EXEC,
	LOCAL_EXEC,
	COM_CD,
	COM_ECHO,
	COM_ENV,
	COM_EXIT,
	COM_EXPORT,
	COM_PWD,
	COM_UNSET,
};

enum e_state
{
	MNS_ERROR = -1,
	CHILD = 0,
	ALL_FINE,
};

typedef struct s_parsed
{
	char	*command;
	char	**args;
	int		type;

}				t_parsed;

typedef struct s_data
{
	char			*line;
	char			**splitted;
	int				*splitted_type;
	char			**paths;
	t_parsed		*parsed;
	int				tkn_count;
}				t_data;

char	*mns_exec_path(char **paths, char *cmd)
{
	int		i;
	char	*possible_path;
	char	*possible_exec;

	i = 0;
	while (paths[i])
	{
		possible_path = ft_strjoin(paths[i], "/");
		possible_exec = ft_strjoin(possible_path, cmd);
		free(possible_path);
		if (access(possible_exec, F_OK | X_OK) == 0)
			return (possible_exec);
		free(possible_exec);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	t_parsed *parsed;

	if (!(parsed = malloc(2 * sizeof(parsed))))
		return (MNS_ERROR);
	if (!(parsed[0].args = malloc(argc * sizeof(char *))))
		return (MNS_ERROR);
	parsed[0].args = argv + 1;

	parsed[1] = NULL;
}
