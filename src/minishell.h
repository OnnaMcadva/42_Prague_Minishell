/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:45:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/04 14:14:24 by mmakagon         ###   ########.fr       */
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

enum e_token
{
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
};

enum e_state
{
	ERROR = -1,
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

int				mns_init(t_data *data);
int				mns_parse(t_data *data);
void			mns_execute(t_data *data, char **envp);
void			mns_free_data(t_data *data);

#endif
