/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:45:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/17 14:59:45 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <sys/types.h>
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

enum e_token
{
	WORD,
	WHITESPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	MNS_ERROR = -1,
	CHILD = 0,
	ALL_FINE,
};

typedef struct s_data
{
	char			*line;
	char			**splitted;
	char			**paths;
	int				tkn_count;
}				t_data;

void			mns_sigint_handler(int sig);
int				mns_init(t_data *data);
int				mns_parse(t_data *data);
int				mns_split(char ***splitted, char *line);
void			mns_execute(t_data *data, char **envp);
void			mns_free_data(t_data *data);
void			*mns_util_do_nothing(void *arg);

#endif
