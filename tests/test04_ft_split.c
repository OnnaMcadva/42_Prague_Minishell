#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	printf("words: %d\n", i);
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (word != NULL)
	{
		while (start < finish)
			word[i++] = str[start++];
		word[i] = '\0';
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc ((count_words(s, c) + 1) * sizeof (char *));
	if (!s || !split)
		return (free(split), NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		char **splitted = ft_split(argv[1], ' ');
		printf("%s\n", splitted[0]);
		free (splitted);
	}
}
