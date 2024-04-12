#include "minishell.h"

int mns_tknlen(char *line, int *tkn_len)
{
    int in_quote;
    int i;

    in_quote = 0;
    i = 0;
    while (line[i]) {
        if (line[i] == DOUBLE_QUOTE)
            in_quote = !in_quote;
        else if (!in_quote && line[i] == WHITESPACE) {
            i++;
            if(!line[i] || line[i] == WHITESPACE)
                continue;
            return (i);
        }
        else
            (*tkn_len)++;
        i++;
    }
    return i;
}

char *mns_tkndup(char *line, char *token, int tkn_len, int position)
{
	int in_quote;
	int i;
	int	j;

    in_quote = 0;
   	i = 0;
	j = 0;
    while (line[i] && i < position)
	{
        if (line[i] == DOUBLE_QUOTE)
            in_quote = !in_quote;
        else if (!in_quote && line[i] == WHITESPACE)
		{
            i++;
            if (!line[i] || line[i] == WHITESPACE)
                continue ;
        }
        else if (j < tkn_len)
            token[j++] = line[i];
        i++;
    }
    token[j] = '\0';
    return (token);
}

int mns_split_process(char **splitted, char *line, int tokens)
{
    int i;
	int tkn_len;
	int position;

	i = 0;
    while (i < tokens)
	{
        tkn_len = 0;
        position = mns_tknlen(line, &tkn_len);
        splitted[i] = (char *)malloc((tkn_len + 1) * sizeof(char));
        if (!splitted[i])
			return (MNS_ERROR);
        splitted[i] = mns_tkndup(line, splitted[i], tkn_len, position);
        line += position;
        i++;
    }
    splitted[i] = NULL;
    return (ALL_FINE);
}

int mns_count_tokens(const char *line)
{
    int i;
	int	count;
	int	in_quote;

	i = 0;
	count = 1;
	in_quote = 0;
    while (line[i])
    {
        if (line[i] == DOUBLE_QUOTE)
            in_quote = !in_quote;
        else if (!in_quote && line[i] == WHITESPACE)
		{
            i++;
            if (!line[i] || line[i] == WHITESPACE)
                continue;
            count++;
        }
        i++;
    }
    return (count);
}

int mns_split(char ***splitted, char *line)
{
	int tokens;
    while (*line == WHITESPACE)
		line++;
    tokens = mns_count_tokens(line);
    if (tokens == 0)
		return (0);
    *splitted = malloc((tokens + 1) * sizeof(char *));
    if (!*splitted)
		return (MNS_ERROR);
    if (mns_split_process(*splitted, line, tokens) == MNS_ERROR)
        return (MNS_ERROR);
    return (tokens);
}