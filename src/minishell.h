/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:45:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/05 10:59:20 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "../libft_plus/libft.h"

# define PROMPT "\x1B[36m[minishell] \x1B[35m[ =) ] \x1B[36m~> \x1B[0m"
// the lenght is 42 =)

# define TOKENS_MAX 10
# define TKNLEN_MAX 64

enum e_token
{
	WORD = -1,
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
	_NULL = '0',
};

enum e_state
{
	MNS_ERROR = -1,
	CHILD = 0,
	PARENT,
	ALL_FINE,
};

typedef struct s_data
{
	char			*line;
	char			**parsed;
	char			**paths;
}				t_data;

typedef struct s_split_var {
	int	i;
	int	j;
	int	in_quote;
}				t_split_var;

int				mns_init(t_data *data);
int				mns_parse(t_data *data);
int				mns_split(char ***splitted, char *line);
void			mns_execute(t_data *data, char **envp);
void			mns_free_data(t_data *data);

#endif
