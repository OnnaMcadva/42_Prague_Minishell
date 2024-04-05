# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <termios.h>
# include <term.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

#define MAX_TOKENS 100
#define TOKEN_SIZE 1024

enum e_parsed_type
{
	UNKNOWN,
	GLOBAL_EXEC,
	LOCAL_EXEC,
	PIPE,
	REDIR_LEFT,
	REDIR_RIGHT,
	VARIABLE,
};

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
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

typedef struct s_parse_indexes
{
	int		tkn;
	int		chr;
	int		in_quotes;
	int		last_quote;
}				t_parse_indexes;

typedef struct s_parsed
{
	enum e_parsed_type		type;
	char					*command;
	char					*argument;
	char					*flag;
}				t_parsed;

typedef struct s_data
{
	char			*line;
	t_parsed		parsed[10];
	size_t			pipes_count;
}				t_data;

///////////////////////////////////////////////////////////////////////////////////////

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*i;

	i = str;
	while (n--)
		*i++ = (unsigned char)c;
	return (str);
}

void	mns_split_line(char *line, char tokens[MAX_TOKENS][TOKEN_SIZE])
{
	t_parse_indexes	index;
	int				i;

	index.tkn = 0;
	index.chr = 0;
	index.in_quotes = 0;
	index.last_quote = -2;
	i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			index.in_quotes = !index.in_quotes;
			if (i - index.last_quote == 1)
			{
				tokens[index.tkn][0] = '\0';
				index.tkn++;
			}
			index.last_quote = i;
			i++;
			continue ;
		}
		if (line[i] == ' ' && !index.in_quotes)
		{
			if (index.chr != 0)
			{
				tokens[index.tkn][index.chr] = '\0';
				index.tkn++;
				index.chr = 0;
			}
		}
		else
			tokens[index.tkn][index.chr++] = line[i];
		i++;
	}
	if (index.chr != 0)
		tokens[index.tkn][index.chr] = '\0';
}

int	mns_parse(t_data *data)
{
	char	tokens[MAX_TOKENS][TOKEN_SIZE];

	ft_memset(tokens, 0, sizeof(tokens));
	mns_split_line(data->line, tokens);
	for (int i = 0; i < 3; i++) {
        printf("Token %d: %s\n", i + 1, tokens[i]);
    }
	return(1);
}

int	mns_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		data->parsed[i].type = UNKNOWN;
		data->parsed[i].argument = NULL;
		data->parsed[i].command = NULL;
		data->parsed[i].flag = NULL;
		i++;
	}
	data->line = NULL;
	data->pipes_count = 0;
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;

	while (mns_init(&data))
	{
		data.line = readline("MY_VERY_GOOD_PROMPT ");
		if (strlen(data.line))
			mns_parse(&data);
		free(data.line);
	}
}
