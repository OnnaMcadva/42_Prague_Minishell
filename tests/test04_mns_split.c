#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum delimeters {
    DOUBLE_QUOTE = '\"',
    SINGLE_QUOTE = '\'',
    WHITESPACE = ' ',
};

enum status {
    MNS_ERROR = -1,
    ALL_FINE = 1,
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

char	*mns_tkncpy(char *line, char *token, int tkn_len, int position)
{
	int		i;
	int		j;
	char	in_quote;

	in_quote = 0;
	i = 0;
	j = 0;
	while (line[i] && i < position)
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

int	mns_split_process(char **splitted, char *line, int tokens)
{
	int	i;
	int	tkn_len;
	int	position;

	i = 0;
	while (i < tokens)
	{
		tkn_len = 0;
		position = mns_tknlen(line, &tkn_len);
		splitted[i] = (char *)malloc((tkn_len + 1) * sizeof(char));
		if (!splitted[i])
			return (MNS_ERROR);
		splitted[i] = mns_tkncpy(line, splitted[i], tkn_len, position);
		line += position;
		i++;
	}
	splitted[i] = NULL;
	return (ALL_FINE);
}

/* Counts a number of tokens to allocate */
int	mns_count_tokens(const char *line)
{
	int	    i;
	int	    count;
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
int	mns_split(char ***splitted, char *line)
{
	int	tokens;

	while (*line == WHITESPACE)
		line++;
	if (!*line)
		return (0);
	tokens = mns_count_tokens(line);
	*splitted = malloc((tokens + 1) * sizeof(char *));
	if (!*splitted)
		return (MNS_ERROR);
	if (mns_split_process(*splitted, line, tokens) == MNS_ERROR)
		return (MNS_ERROR);
	return (tokens);
}

int main(int argc, char **argv) {
    char	line1[] = "r2345  ";
	char	line2[] = "echo \'a\'";
	char	line3[] = "r234 d2345\"\" \"t234\" c23\"4\"56";
	char	**splitted;
	int		count;

    count = mns_split(&splitted, line1);
    if (count != MNS_ERROR) {
        printf("Line 1:\n");
        for (int i = 0; i < count; i++) {
            printf("%d: %s\n", i + 1, splitted[i]);
            free(splitted[i]);
        }
        free(splitted);
    }
    count = mns_split(&splitted, line2);
    if (count != MNS_ERROR) {
        printf("Line 2:\n");
        for (int i = 0; i < count; i++) {
            printf("%d: %s\n", i + 1, splitted[i]);
            free(splitted[i]);
        }
        free(splitted);
    }
    count = mns_split(&splitted, line3);
    if (count != MNS_ERROR) {
        printf("Line 3:\n");
        for (int i = 0; i < count; i++) {
            printf("%d: %s\n", i + 1, splitted[i]);
            free(splitted[i]);
        }
        free(splitted);
    }
}
