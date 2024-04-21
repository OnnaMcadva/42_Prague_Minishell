#include "../includes/minishell.h"

void mns_com_exit(t_data *data, int code)
{
    ft_putendl_fd("exit", STDIN_FILENO);
    mns_free_data(data);
    exit (code);
}