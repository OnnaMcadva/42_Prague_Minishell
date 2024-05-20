#include "../includes/minishell.h"

int	mns_util_tabcpy(char **dest, char **src, char *last_line)
{
	if (!src || !*src)
		return (MNS_ERROR);
	while (*src && *src != last_line)
	{
		*dest = ft_strdup(*src);
		if (!*dest)
			return (mns_free_tab(dest), MNS_ERROR);
		dest++;
		src++;
	}
	*dest = NULL;
	return (ALL_FINE);
}

int mns_env_delete(t_data *data, char *to_delete)
{
	char	**temp_envp;
	char	**pointer;
	int		i;
	int		env_count;

	pointer = mns_env_find(data->env_copy, to_delete);
	if (!pointer || !*pointer)
		return (MNS_ERROR);
	env_count = mns_util_tablen(data->env_copy);
	temp_envp = malloc(env_count * sizeof(char *));
	if (!temp_envp)
		return (MNS_ERROR);
	if (mns_util_tabcpy(temp_envp, data->env_copy, *pointer) == MNS_ERROR)
		return (MNS_ERROR);
	i = mns_util_tablen(temp_envp);
	if (mns_util_tabcpy(temp_envp + i, pointer + 1, NULL) == MNS_ERROR)
		return (MNS_ERROR);
	mns_free_tab(data->env_copy);
	data->env_copy = temp_envp;
	return (ALL_FINE);
}