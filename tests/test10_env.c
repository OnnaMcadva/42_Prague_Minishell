#include "../includes/minishell.h"

int	mns_com_env(char **envp)
{
	int	i;

	i = 0;
	if (envp)
		while (envp[i])
			ft_putendl_fd(envp[i++], STDOUT_FILENO);
	return (0);
}

int	mns_util_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;

	return (i);
}

void	mns_util_free_tab(char **tab)
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
	if (i <= 0)
		return (MNS_ERROR);
	temp_envp = malloc((i + 2) * sizeof(char *));
	if (!temp_envp)
		return (perror("malloc"), MNS_ERROR);
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
	mns_util_free_tab(data->env_copy);
	data->env_copy = temp_envp;
	return (ALL_FINE);
}

char	*mns_env_find(char **envp, char *key)
{
	int		i;
	int		len;
	char	*tf_equals;

	tf_equals = ft_strjoin(key, "=");
	len = ft_strlen(tf_equals);
	if (!len)
		return (free(tf_equals), NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], tf_equals, len) == 0)
			break ;
		i++;
	}
	free(tf_equals);
	return (envp[i]);
}

int	mns_env_delete(t_data *data, char *to_delete)
{
	char	**temp_envp;
	char	*pointer;
	int		i;
	int		flag;

	pointer = mns_env_find(data->env_copy, to_delete);
	i = mns_util_tablen(data->env_copy);
	temp_envp = malloc(i * sizeof(char *));
	if (!temp_envp || !pointer || i <= 0)
		return (free(temp_envp), MNS_ERROR);
	temp_envp[i - 1] = NULL;
	flag = 1;
	while (--i >= 0)
	{
		if (data->env_copy[i] == pointer)
		{
			flag = 0;
			i--;
		}
		temp_envp[i - flag] = ft_strdup(data->env_copy[i]);
		if (mns_env_util_malloc_check(temp_envp, i - flag) == MNS_ERROR)
			return (MNS_ERROR);
	}
	mns_util_free_tab(data->env_copy);
	return (data->env_copy = temp_envp, ALL_FINE);
}

char	*mns_env_util_join(char *key, char *value)
{
	char	*temp;
	char	*new_entry;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (perror("malloc"), NULL);
	new_entry = ft_strjoin(temp, value);
	free (temp);
	return (new_entry);
}

int	mns_env_change(t_data *data, char *key, char *value)
{
	char	*pointer;
	char	*new_entry;
	int		i;

	pointer = mns_env_find(data->env_copy, key);
	if (!pointer)
		return (MNS_ERROR);
	new_entry = mns_env_util_join(key, value);
	if (!new_entry)
		return (perror("malloc"), MNS_ERROR);
	i = 0;
	while (data->env_copy[i])
	{
		if (data->env_copy[i] == pointer)
		{
			free(data->env_copy[i]);
			data->env_copy[i] = new_entry;
			break ;
		}
		i++;
	}
	return (ALL_FINE);
}


int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argc;
	(void)argv;
	if (mns_init_env_copy(envp, &data) == MNS_ERROR)
		return (13);
	mns_env_add(&data, "AHOJ=nazdar");
	// mns_com_env(data.env_copy);
	printf("\n%s\n\n", mns_env_find(data.env_copy, "AHOJ")); // Must be "AHOJ=nazdar"

	mns_env_change(&data, "AHOJ", "dobry_den");
	// mns_com_env(data.env_copy);
	printf("\n%s\n\n", mns_env_find(data.env_copy, "AHOJ")); // Must be "AHOJ=dobry_den"

	mns_env_delete(&data, "AHOJ");
	// mns_com_env(data.env_copy);
	printf("\n%s\n\n", mns_env_find(data.env_copy, "AHOJ")); // Must be "(null)"

	mns_util_free_tab(data.env_copy);
	return (0);
}
