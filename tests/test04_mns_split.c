#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define DELIMETERS " 	\n\'\"\\$|<>"


enum e_delimiter
{
	WHITESPACE = ' ',
	TAB = '	',
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


/* Toggles in_quote switch and returns either it wos toggled or not */
int mns_util_in_quote(char *in_quote, char c)
{
	int toggle;

	if (!*in_quote && (c == DOUBLE_QUOTE || c == SINGLE_QUOTE))
	{
		*in_quote = c;
		toggle = 1;
	}
	else if (c == *in_quote)
	{
		*in_quote = 0;
		toggle = 1;
	}
	else
		toggle = 0;
	return (toggle);
}

int	mns_split_util_type(char *line, int next_position)
{
	char	in_quote;

	in_quote = 0;
	while (*line && mns_util_in_quote(&in_quote, *line))
		line++;
	if (!line)
		return (NULL_TOKEN);
	else if (in_quote != SINGLE_QUOTE && line[0] == DOLLAR_SIGN)
		return (ENV);
	else if (!in_quote && line[0] == PIPE_LINE)
		return (PIPE);
	else if (!in_quote && line[0] == REDIR_IN)
	{
		if (line[1] == REDIR_IN)
			return (HERE_DOC);
		return (IN_OPERATOR);
	}
	else if (!in_quote && line[0] == REDIR_OUT)
	{
		if (line[1] == REDIR_OUT)
			return (OUT_APPEND_OPRTR);
		return (OUT_OPERATOR);
	}
	else
		return (WORD);
}

int mns_tknlen(char *line, int *tkn_len)
{
	char	in_quote;
	int		pos;

	in_quote = 0;
	pos = 0;
	while (line[pos])
	{
		if (mns_util_in_quote(&in_quote, line[pos]))
			pos++;
		else
		{
			if (!in_quote && line[pos] == WHITESPACE)
				break;
			(*tkn_len)++;
			pos++;
		}
	}
	while (line[pos] == WHITESPACE)
		pos++;
	return (pos);
}

char	*mns_tkncpy(char *line, char *token, int tkn_len, int next_position)
{
	int		i;
	int		j;
	char	in_quote;

	in_quote = 0;
	i = 0;
	j = 0;
	while (line[i] && i < next_position)
	{
		if (mns_util_in_quote(&in_quote, line[i]))
			i++;
		else
		{
			if (!in_quote && line[i] == WHITESPACE)
				break ;
			else if (j < tkn_len)
				token[j++] = line[i];
			i++;
		}
	}
	token[j] = '\0';
	return (token);
}

int	mns_split_process(char **splitted, int *splitted_type, char *line, int tokens)
{
	int	i;
	int	tkn_len;
	int	next_position;

	i = 0;
	tkn_len = 0;
	while (i < tokens)
	{
		next_position = mns_tknlen(line, &tkn_len);
		splitted[i] = (char *)malloc((tkn_len + 1) * sizeof(char));
		if (!splitted[i])
			return (MNS_ERROR);
		splitted_type[i] = mns_split_util_type(line, next_position);
		splitted[i] = mns_tkncpy(line, splitted[i], tkn_len, next_position);
		line += next_position;
		i++;
	}
	splitted[i] = NULL;
	splitted_type[i] = NULL_TOKEN;
	return (ALL_FINE);
}

/* Counts a number of tokens to allocate */
int	mns_count_tokens(const char *line)
{
	int		i;
	int		count;
	char	in_quote;

	i = 0;
	count = 1;
	in_quote = 0;
	while (line[i])
	{
		mns_util_in_quote(&in_quote, line[i]);
		if (!in_quote && line[i] == WHITESPACE)
		{
			while (line[i] == WHITESPACE)
				i++;
			if (!line[i])
				break ;
			count++;
			continue ;
		}
		i++;
	}
	return (count);
}

/* Splits line to an array of strings (splitted)
	and returns a number of parsed tokens.
	Returns 0 in case of empty line.
	Returns -1 (MNS_ERROR) in case of malloc error. */
int	mns_split(char ***splitted, int **splitted_type, char *line)
{
	int	tokens;

	while (*line == WHITESPACE)
		line++;
	if (!*line)
		return (0);
	tokens = mns_count_tokens(line);
	*splitted = malloc((tokens + 1) * sizeof(char *));
	*splitted_type = malloc((tokens + 1) * sizeof(int));
	if (!*splitted || !*splitted_type)
		return (MNS_ERROR);
	if (mns_split_process(*splitted, *splitted_type, line, tokens) == MNS_ERROR)
		return (MNS_ERROR);
	return (tokens);
}

int main(int argc, char **argv) {
	char	line1[] = "r2345 \"|\" \"$VARIABLE\" \'$NOT_A_VARIABLE\'";
	char	line2[] = "echo \'a\' \"\"\"\"| wc -w <";
	char	line3[] = "r234 << d2345\"\" \"t234\" c23\"4\"56";
	int		*splitted_type;
	char	**splitted;
	int		count;

	count = mns_split(&splitted, &splitted_type, line1);
	if (count != MNS_ERROR) {
		printf("Line 1:\n");
		for (int i = 0; i < count; i++) {
			printf("%d: %d %s\n", i + 1, splitted_type[i], splitted[i]);
			free(splitted[i]);
		}
		free(splitted);
		free(splitted_type);
	}
	count = mns_split(&splitted, &splitted_type, line2);
	if (count != MNS_ERROR) {
		printf("Line 2:\n");
		for (int i = 0; i < count; i++) {
			printf("%d: %d %s\n", i + 1, splitted_type[i], splitted[i]);
			free(splitted[i]);
		}
		free(splitted);
		free(splitted_type);
	}
	count = mns_split(&splitted, &splitted_type, line3);
	if (count != MNS_ERROR) {
		printf("Line 3:\n");
		for (int i = 0; i < count; i++) {
			printf("%d: %d %s\n", i + 1, splitted_type[i], splitted[i]);
			free(splitted[i]);
		}
		free(splitted);
		free(splitted_type);
	}
}
