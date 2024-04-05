/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:44:15 by mmakagon          #+#    #+#             */
/*   Updated: 2023/11/02 11:58:52 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_next(char *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	k = ft_strlen(buffer) - i + 1;
	if (!buffer[i] || !k)
		return (free(buffer), NULL);
	i++;
	line = (char *)malloc((k + 1) * (sizeof(char)));
	while (buffer[i] && j < k)
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*gnl_line(char *buffer, int with_n_or_not)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (i == 0 || with_n_or_not)
		line = (char *)ft_calloc((i + 2), sizeof(char));
	else
		line = (char *)ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n' && with_n_or_not)
		line[i] = '\n';
	return (line);
}

char	*gnl_join_n_free(char *src, char *buffer, size_t b)
{
	char	*result;
	size_t	a;

	a = ft_strlen(src);
	if (!a && !b)
		return (free(src), NULL);
	result = (char *)malloc((a + b + 1) * sizeof(char));
	if (result)
	{
		ft_strcpy(result, src);
		ft_strcat(result, buffer);
	}
	else
		return (free(src), NULL);
	free(src);
	result[a + b] = '\0';
	return (result);
}

char	*gnl_read_file(int fd, char *src)
{
	char	*buffer;
	int		bytes_read;

	if (!src)
		src = ft_calloc(1, 1);
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0 || !buffer)
		{
			free(buffer);
			return (free(src), NULL);
		}
		buffer[bytes_read] = '\0';
		src = gnl_join_n_free(src, buffer, bytes_read);
		if (!src || ft_strchr(src, '\n'))
			break ;
	}
	free(buffer);
	return (src);
}

char	*get_next_line(int fd, int with_n_or_not)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = gnl_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = gnl_line(buffer, with_n_or_not);
	buffer = gnl_next(buffer);
	return (line);
}

// int main(void)
// {
//  int  fd;
//  char *line;

//  fd = open("empty", O_RDONLY);
//  while (1)
//  {
//   line = get_next_line(fd, 0);
//   printf("%s", line);
//   if (line == NULL)
//    break ;
//   free(line);
//  }
//  return (0);
// }
