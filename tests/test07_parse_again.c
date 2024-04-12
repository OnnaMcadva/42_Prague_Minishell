#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum delimeters {
	DOUBLE_QUOTE = '"',
	WHITESPACE = ' ',
};

enum status {
	MNS_ERROR = -1,
	ALL_FINE = 1,
};

int	mns_tknlen(char *line, int *tkn_len)
{
	int		in_quote;
	int		i;

	if (!line || !line[0])
		return (0);
	in_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == DOUBLE_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && line[i] == WHITESPACE)
		{
			i++;
			if(!line[i] || line[i] == WHITESPACE)
				continue;
			return (i);
		}
		else
			*tkn_len += 1;
		i++;;
	}
	return (i);
}

char	*mns_tkndup(char *line, int tkn_len, int position)
{
	int		in_quote;
	int		i;
	int		j;
	char	*token;

	if (!line || !line[0] || tkn_len == 0)
		return (NULL);
	token = (char *)malloc((tkn_len + 1) * sizeof(char));
	if (!token)
		return (NULL);
	token[tkn_len] = '\0';
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
			if(!line[i] || line[i] == WHITESPACE)
				continue;
		}
		else if (j < tkn_len)
			token[j++] = line[i];
		i++;
	}
	return (token);
}

int mns_split_process(char **splitted, char *line, const int tokens)
{
	int	i;
	int	tkn_len;
	int	position;

	i = 0;
	while (line && i < tokens)
	{
		tkn_len = 0;
		position = mns_tknlen(line, &tkn_len);
		splitted[i] = mns_tkndup(line, tkn_len, position);
		printf("%s\n", splitted[i]);
		line += position;
		i++;
	}
	return (ALL_FINE);
}

int mns_count_tokens(const char *line)
{
	int	i;
	int	count;
	int	in_quote;

	if (!line || !line[0])
		return (0);
	i = 0;
	count = 1;
	in_quote = 0;
	while (line[i])
	{
		if (line[i] == DOUBLE_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && line[i] == WHITESPACE)
		{
			if (!line[++i] || line[i] == WHITESPACE)
				continue ;
			count++;
			continue ;
		}
		i++;
	}
	return (count);
}


int mns_split(char **splitted, char *line)
{
	int		tokens;
	char	*line_copy;

	line_copy = line;
	while (*line_copy == WHITESPACE)
		line_copy++;
	tokens = mns_count_tokens(line_copy);
	if (tokens)
	{	
		splitted = (char **)malloc((tokens + 1) * sizeof(char **));
		if (!splitted)
			return (MNS_ERROR);
		splitted[tokens] = NULL;
		if (mns_split_process(splitted, line_copy, tokens) == MNS_ERROR)
			return (MNS_ERROR);
	}
	
	return (tokens);
	
}

int main(int argc, char **argv)
{
	char	line1[] = "r2345";
	char	line2[] = "a b";
	char	line3[] = "r234 d2345\"\" t234 c23\"4\"56";
	char	**splitted;
	int		count;

	// count = mns_split(splitted, line1);
	// printf("%s\n%d\n", splitted[0], count);

	// count = mns_split(splitted, line2);
	// printf("%s\n%d\n", splitted[0], count);

	count = mns_split(splitted, line3);
	// printf("%s\n%d\n", splitted[0], count);

	// free (splitted);
	// for (int i = 0; i < count; i++)
	// 	printf("\n%d: %s\n", i + 1, splitted[i]);
}