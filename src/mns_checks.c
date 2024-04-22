#include "../includes/minishell.h"

/* Checks line for opened quotes and ... ?? */
int mns_check_line(char *line)
{
    int     i;
    char    in_quote;

    if (!line)
        return (MNS_ERROR);
    i = 0;
    in_quote = 0;
    while (line[i])
        mns_util_in_quote(&in_quote, line[i++]);
    if (in_quote != 0)
    {
        ft_putendl_fd
            ("From subject:\nYour shell should not interpret unclosed quotes",
            STDOUT_FILENO);
        return (MNS_ERROR);
    }
    return (ALL_FINE);
}