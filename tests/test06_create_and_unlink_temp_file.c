# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


int main()
{
	int		fd;
	int		bytes_read;
	char	*filename = "./temp";
	char	*str1 = "abc";
	char	*str2 = "def";
	char	*str3;

	str3 = malloc(4 * sizeof(char));
	fd = open(filename, (O_CREAT | O_RDWR | O_TRUNC), 0644);
	write (fd, str2, 3);
	close(fd);
	fd = open(filename, O_RDONLY);
	bytes_read = read(fd, str3, 3);
	str3[3] = '\0';
	close(fd);
	printf("%s\n", str3);
	unlink(filename);
	free(str3);
}
