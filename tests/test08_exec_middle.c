#include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
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

enum e_token
{
	WORD,
	WHITESPACE = ' ',
	NEW_LINE = '\n',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_tkn_type
{
    COMMAND,
    FLAG,
    ARGUMENT,
    PIPE,
};

enum e_state
{
	MNS_ERROR = -1,
	CHILD = 0,
	ALL_FINE,
};

typedef struct s_parsed
{
    char    *command;
    char    **args;
    int     type;

}               t_parsed;

typedef struct s_data
{
	char			*line;
	char			**splitted;
	char			**paths;
    t_parsed        *parsed;
	int				tkn_count;
}				t_data;


int mns_exec_middle(char *filename, char *command)