/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:44:58 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/16 11:47:43 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mns_main_loop(t_data *data)
{
	while (mns_init_data(data) != MNS_ERROR)
	{
		data->line = readline(PROMPT);
		if (!data->line)
			mns_com_exit(data, NULL);
		if (*data->line)
		{
			if (mns_parse(data) == ALL_FINE)
				mns_execute(data);
			if (data->tkn_count)
				add_history(data->line);
		}
		mns_free_data(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
	{
		printf("%s %s???\nWatch your arguments!!!\n", argv[0], argv[1]);
		return (42);
	}
	if (mns_init_env_copy(envp, &data) == MNS_ERROR)
		return (1);
	signal(SIGINT, mns_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	mns_main_loop(&data);
}
