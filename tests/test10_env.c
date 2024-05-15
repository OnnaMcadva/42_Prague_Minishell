#include "../includes/minishell.h"

int	mns_util_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

void	mns_free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while(tab[i])
			free(tab[i++]);
		free(tab);
	}
}

int	mns_env_util_malloc_check(char **tab, int i)
{
	if (!tab[i])
	{
		while (tab[++i])
			free(tab[i]);
		free (tab);
		return (MNS_ERROR);
	}
	return (ALL_FINE);
}

int	mns_init_env_copy(char **envp, t_data *data)
{
	int	i;

	i = 0;
	if (envp)
		while(envp[i])
			i++;
	if (!i)
		return (MNS_ERROR);
	data->env_copy = malloc((i + 1) * sizeof(char *));
	if (!data->env_copy)
		return (perror("malloc"), MNS_ERROR);
	data->env_copy[i] = NULL;
	while (--i >= 0)
	{
		data->env_copy[i] = ft_strdup(envp[i]);
		if (mns_env_util_malloc_check(data->env_copy, i) == MNS_ERROR)
			return (MNS_ERROR);
	}
	return (ALL_FINE);
}

int	mns_env_add(t_data *data, char *to_add)
{
	int		i;
	char	**temp_envp;

	i = mns_util_tablen(data->env_copy);
	temp_envp = malloc((i + 2) * sizeof(char *));
	if (!temp_envp)
		return (MNS_ERROR);
	temp_envp[i + 1] = NULL;
	temp_envp[i] = ft_strdup(data->env_copy[i - 1]);
	temp_envp[--i] = ft_strdup(to_add);
	if (mns_env_util_malloc_check(temp_envp, i) == MNS_ERROR
		|| mns_env_util_malloc_check(temp_envp, i + 1) == MNS_ERROR)
		return (MNS_ERROR);
	while (--i >= 0)
	{
		temp_envp[i] = ft_strdup(data->env_copy[i]);
		if (mns_env_util_malloc_check(temp_envp, i) == MNS_ERROR)
			return (MNS_ERROR);
	}
	mns_free_tab(data->env_copy);
	data->env_copy = temp_envp;
	return (ALL_FINE);
}

#if 0
int	mns_env_delete(t_data *data, char *to_delete)
{
	int		i;
	int		len;
	char	**temp_envp;

	i = mns_util_tablen(data->env_copy);
	len = ft_strlen(to_delete);
	temp_envp = malloc(i * sizeof(char *));
	if (!temp_envp)
		return (MNS_ERROR);
	temp_envp[i] = NULL;
	while (--i >= 0)
	{
		if (ft_strncmp(to_delete, temp_envp[i], len))
			break ;
		temp_envp[i] = ft_strdup(data->env_copy[i]);
		if (mns_env_util_malloc_check(temp_envp, i) == MNS_ERROR)
			return (MNS_ERROR);
	}
}
#endif

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argc;
	(void)argv;
	if (mns_init_env_copy(envp, &data) == MNS_ERROR)
		return (MNS_ERROR);
	mns_free_tab(data.env_copy);
	return (13);
}
