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

// This function should return the start of the current token and update tkn_len
char *mns_tknlen(char *line, int *tkn_len) {
    char *start = line;
    int in_quote = 0;

    while (*line) {
        if (*line == DOUBLE_QUOTE)
            in_quote = !in_quote;
        else if (!in_quote && *line == WHITESPACE) {
            break;
        }
        line++;
        (*tkn_len)++;
    }
    return start;
}

int mns_split_process(char ***parsed, char *line, const int tokens) {
    int i = 0, tkn_len = 0;
    char *token_start = NULL;

    while (line && *line && i < tokens)
    {
        tkn_len = 0;
        token_start = mns_tknlen(line, &tkn_len);
        if (tkn_len > 0)
        {
            (*parsed)[i] = (char *)malloc(tkn_len + 1);
            if (!(*parsed)[i])
                return MNS_ERROR;
            mns_tkncpy((*parsed)[i], token_start, tkn_len);
            (*parsed)[i][tkn_len] = '\0';
            line = token_start + tkn_len;
            while (*line == WHITESPACE) line++;
            i++;
        } 
        else
            line++;
    }
    return ALL_FINE;
}

int mns_split(char ***parsed, char *line) {
    int tokens;
    char *line_copy = line;

    while (*line_copy == WHITESPACE)
        line_copy++;
    tokens = mns_count_tokens(line_copy);
    if (tokens) {
        *parsed = (char **)malloc((tokens + 1) * sizeof(char *));
        if (!(*parsed))
            return MNS_ERROR;
        (*parsed)[tokens] = NULL;
        if (mns_split_process(parsed, line_copy, tokens) == MNS_ERROR)
            return MNS_ERROR;
    }
    return tokens;
}

int main(int argc, char **argv) {
    char line[] = "r2\"3\"4 d2345\"\" \"\"t234 \"c23456\"";
    char **parsed;
    int count;

    count = mns_split(&parsed, line);
    if (count != MNS_ERROR) {
        for (int i = 0; i < count; i++) {
            printf("%d: %s\n", i + 1, parsed[i]);
            free(parsed[i]);
        }
        free(parsed);
    }
}
