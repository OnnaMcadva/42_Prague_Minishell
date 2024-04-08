#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TOKENS_MAX 10
#define	TKNLEN_MAX 64

enum delimeters {
	QUOTE = '"',
	WHITESPACE = ' ',
};

enum status {
	ERROR = -1,
	ALL_FINE = 1,
};

int	parse(char parsed[TOKENS_MAX][TKNLEN_MAX], char *line)
{
	int	in_quote;
	int	i;
	int	j;
	int k;

	in_quote = 0;
	i = 0;
	j = 0;
	k = 0;
	if (!line)
		return (0);
	while (line[i] == WHITESPACE)
		i++;
	while (line[i] && j < TOKENS_MAX)
	{
		if (line[i] == QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && line[i] == WHITESPACE)
		{
			i++;
			if(!line[i] || line[i] == WHITESPACE)
				continue;
			j++;
			k = 0;
			continue;
		}
		else if (k < TKNLEN_MAX)
			parsed[j][k++] = line[i];
		i++;
	}
	return (j + 1);
}

int main(int argc, char **argv)
{
	char line[] = "\"12\"abc    def hij \"\" ";
	char parsed[TOKENS_MAX][TKNLEN_MAX];
	int count;

	memset(parsed, 0, sizeof(parsed));
	count = parse (parsed, line);
	for (int i = 0; i < count; i++)
		printf("\n%d: %s\n", i + 1, parsed[i]);
}