#include "../includes/minishell.h"

void	mns_copy_line_process(const char *input, char *output, int len)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (i < len)
	{
		if (input[i] == '|')
		{
			output[j++] = ' ';
			output[j++] = input[i++];
			output[j++] = ' ';
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			output[j++] = ' ';
			output[j++] = input[i];
			if (input[i + 1] == input[i])
				output[j++] = input[++i];
			output[j++] = ' ';
			i++;
		}
		else
			output[j++] = input[i++];
	}
}

int	mns_split_util_copy_line(char **input)
{
	char	*output;
	size_t	len;
	size_t	new_len;

	len = ft_strlen(*input);
	new_len = len * 2;
	output = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (output == NULL)
		return (perror("malloc"), MNS_ERROR);
	mns_copy_line_process(*input, output, len);
	free(*input);
	*input = output;
	return (ALL_FINE);
}

int	main(void)
{
	char	*input_str;

	input_str = ft_strdup("command1 | command2 << input.txt >> output.txt");
	if (input_str == NULL)
	{
		perror("ft_strdup");
		return (MNS_ERROR);
	}
	printf("Original: %s\n", input_str);
	if (mns_split_util_copy_line(&input_str) != ALL_FINE)
	{
		free(input_str);
		return (MNS_ERROR);
	}
	printf("Modified: %s\n", input_str);
	free(input_str);
	return (0);
}
