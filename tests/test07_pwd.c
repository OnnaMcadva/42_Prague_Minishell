# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/param.h>

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	while (s && *s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	ft_putchar_fd('\n', fd);
}

void    mns_com_pwd(void)
{
    char    dir[PATH_MAX];
    char    *s;

    s = getcwd(dir, PATH_MAX);
    if (!s)
        perror("Error getting pwd");
    else
        ft_putendl_fd(dir, STDOUT_FILENO);
}

int main()
{
    mns_com_pwd();
}
