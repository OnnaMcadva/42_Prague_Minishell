#include <stdio.h>

typedef struct s_parsed
{
    char    **args;
    char    *command;
    int     type;

}               t_parsed;

typedef struct s_data
{
	char		**paths;
	char		*line;
	char		**splitted;
	int			*splitted_type;
	t_parsed	*parsed;
	int			tkn_count;
}				t_data;

int main()
{
    // t_parsed    parsed;

    printf ("%lu", sizeof(t_parsed));
}