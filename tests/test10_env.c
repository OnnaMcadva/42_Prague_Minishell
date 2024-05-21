#include "../includes/minishell.h"

void	mns_free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

int	mns_com_env(char **envp)
{
	int	i;

	if (!envp)
		return (EXIT_FAILURE);
	i = 0;
	while (envp[i])
		ft_putendl_fd(envp[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
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

int	mns_env_add(t_data *data, char *to_add)
{
	char	**temp_env;
	char	**pointer;
	int		tab_len;

	tab_len = mns_util_tablen(data->env_copy);
	if (tab_len <= 0)
		return (MNS_ERROR);
	temp_env = malloc((tab_len + 2) * sizeof(char *));
	if (!temp_env)
		return (perror("malloc"), MNS_ERROR);
	if (tab_len > 1)
	{
		pointer = data->env_copy + tab_len - 1;
		if (mns_util_tabcpy(temp_env, data->env_copy, *pointer) == MNS_ERROR)
			return (MNS_ERROR);
	}
	temp_env[tab_len - 1] = ft_strdup(to_add);
	if (!temp_env[tab_len - 1])
		return (mns_free_tab(temp_env), MNS_ERROR);
	pointer = data->env_copy + tab_len - 1;
	if (mns_util_tabcpy(temp_env + tab_len, pointer, NULL) == MNS_ERROR)
			return (MNS_ERROR);
	mns_free_tab(data->env_copy);
	data->env_copy = temp_env;
	return (ALL_FINE);
}

char	*mns_getenv(char **envp, char *key)
{
	char	**pointer;
	int		i;

	if (key && envp)
	{
		if (key[0] == DOLLAR_SIGN)
			key++;
		pointer = mns_env_find(envp, key);
		if (!pointer || !*pointer)
			return (NULL);
		i = 0;
		while ((*pointer)[i])
		{
			if ((*pointer)[i] == '=')
				return (*pointer + i + 1);
			i++;
		}
	}
	return (NULL);
}

char	**mns_env_find(char **envp, char *to_find)
{
	int		i;
	int		len;
	char	*tf_equals;

	if (!envp || !to_find || !*to_find)
		return (NULL);
	tf_equals = ft_strjoin(to_find, "=");
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
	return (envp + i);
}

int	mns_init_shell(t_data *data)
{
	int		shlvl;
	char	*temp;

	shlvl = 1;
	temp = mns_getenv(data->env_copy, "SHLVL");
	if (temp)
		shlvl += ft_atoi(temp);
	temp = ft_itoa(shlvl);
	if (!temp)
		return (perror("init_atoi"), MNS_ERROR);
	else
	{
		if (mns_env_change(data, "SHLVL", temp) == MNS_ERROR)
			return (free(temp), MNS_ERROR);
		free(temp);
	}
	temp = mns_getenv(data->env_copy, "PWD");
	if (temp)
	{
		temp = ft_strjoin(temp, "/minishell");
		if (temp)
			mns_env_change(data, "SHELL", temp);
		free (temp);
	}
	return (ALL_FINE);
}

int	mns_util_tabcpy(char **dest, char **src, char *last_line)
{
	int	i;

	if (!src || !*src)
		return (1);
	i = 0;
	while (src[i] && src[i] != last_line)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (mns_free_tab(dest), MNS_ERROR);
		i++;
	}
	dest[i] = NULL;
	return (ALL_FINE);
}

int	mns_init_env(char **envp, t_data *data)
{
	int	tab_len;

	data->exit_status = 0;
	tab_len = mns_util_tablen(envp);
	if (tab_len <= 0)
		return (MNS_ERROR);
	data->env_copy = malloc((tab_len + 1) * sizeof(char *));
	if (!data->env_copy)
		return (perror("malloc"), MNS_ERROR);
	if (mns_util_tabcpy(data->env_copy, envp, NULL) == MNS_ERROR)
		return (MNS_ERROR);
	return (mns_init_shell(data));
}

int	mns_env_delete(t_data *data, char *to_delete)
{
	char	**temp_envp;
	char	**pointer;
	int		env_len;

	pointer = mns_env_find(data->env_copy, to_delete);
	if (!pointer || !*pointer)
		return (MNS_ERROR);
	env_len = mns_util_tablen(data->env_copy);
	if (env_len <= 0)
		return (MNS_ERROR);
	temp_envp = malloc(env_len * sizeof(char *));
	if (!temp_envp)
		return (perror("malloc"), MNS_ERROR);
	if (mns_util_tabcpy(temp_envp, data->env_copy, *pointer) == MNS_ERROR)
		return (MNS_ERROR);
	env_len = mns_util_tablen(temp_envp);
	if (mns_util_tabcpy(temp_envp + env_len, pointer + 1, NULL) == MNS_ERROR)
		return (MNS_ERROR);
	mns_free_tab(data->env_copy);
	data->env_copy = temp_envp;
	return (ALL_FINE);
}

int	mns_env_change(t_data *data, char *key, char *value)
{
	char	**pointer;
	char	*temp;
	char	*new_entry;

	pointer = mns_env_find(data->env_copy, key);
	if (!pointer || !*pointer)
		return (MNS_ERROR);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (perror("malloc"), MNS_ERROR);
	new_entry = ft_strjoin(temp, value);
	free (temp);
	if (!new_entry)
		return (perror("malloc"), MNS_ERROR);
	free(*pointer);
	*pointer = new_entry;
	return (ALL_FINE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argc;
	(void)argv;
	data.env_copy = NULL;
	if (mns_init_env(envp, &data) == MNS_ERROR)
		return (MNS_ERROR);
	mns_env_add(&data, "AHOJ=nazdar");
	mns_env_add(&data, "ABC=def");
	mns_com_env(data.env_copy);
	printf("\n%s\n\n", *mns_env_find(data.env_copy, "AHOJ")); // Must be "AHOJ=nazdar"

	printf ("%s\n", mns_getenv(data.env_copy, "AHOJ"));

	mns_env_change(&data, "AHOJ", "dobry_den");
	// // mns_com_env(data.env_copy);
	printf("\n%s\n\n", *mns_env_find(data.env_copy, "AHOJ")); // Must be "AHOJ=dobry_den"

	printf ("%s\n", mns_getenv(data.env_copy, "AHOJ"));

	mns_env_delete(&data, "AHOJ");
	// // // mns_com_env(data.env_copy);
	printf("\n%s\n\n", *mns_env_find(data.env_copy, "AHOJ")); // Must be "(null)"
	mns_env_delete(&data, "_");
	mns_com_env(data.env_copy);


	mns_free_tab(data.env_copy);
	return (0);
}
