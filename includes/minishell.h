/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:45:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 13:53:14 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <stdlib.h>
// # include <string.h>
// # include <sys/types.h>
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
# include "../libft_plus/libft.h"

# define PROMPT "\x1B[36m[minishell] \x1B[35m[ =) ] \x1B[36m~> \x1B[0m"
// the lenght is 42 =)

enum e_symbol
{
	WHITESPACE = ' ',
	NEW_LINE = '\n',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
};

enum e_tkn_type
{
	NULL_TOKEN,
	WORD,
	GLOBAL_EXEC,
	LOCAL_EXEC,
	PIPE,
	HERE_DOC,
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

void			mns_sigint_handler(int sig);
int				mns_init(t_data *data);
int				mns_parse(t_data *data);
int				mns_check_line(char *line);
int				mns_split(char ***splitted, char *line);
void			mns_execute(t_data *data, char **envp);
void			mns_execute_simple(t_parsed parsed, char **paths, char **envp);
void			mns_free_data(t_data *data);
int				mns_util_in_quote(char *in_quote, char c);
void			mns_com_exit(t_data *data, int code);

#endif
