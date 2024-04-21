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

// int mns_create_token(t_data *data)
// {

// }

int mns_parse_init(t_data *data)
{
    int i;

    data->parsed = malloc((data->tkn_count + 1) * sizeof(t_parsed));
    if (!data->parsed)
        return (MNS_ERROR);
    i = 0;
    while (i <= data->tkn_count)
    {
        data->parsed[i].args = NULL;
        data->parsed[i].command = NULL;
        data->parsed[i].type = 0;
        i++;
    }
    
    return (ALL_FINE);
}

int    mns_parse_process(t_data *data)
{
    int i;

    if (mns_parse_init(data) == MNS_ERROR)
        return (MNS_ERROR);
    i = 0;
    while (i < data->tkn_count)
        mns_create_token(data, i);
    return (ALL_FINE);
}


int main()
{
    t_data      data;
    char        *splitted[4];

    splitted[0] = strdup("echo");
    splitted[1] = strdup("-n");
    splitted[2] = strdup("abc");
    splitted[3] = NULL;

    data.splitted = splitted;
    data.tkn_count = 3;

    printf("%s %s %s %s\n", data.splitted[0], data.splitted[1], data.splitted[2], data.splitted[3]);
    if (mns_parse_process(&data) == MNS_ERROR)
        return (MNS_ERROR);
    for (int i = 0; i < 4; i++)
        free(splitted[i]);
    free(data.parsed);
}