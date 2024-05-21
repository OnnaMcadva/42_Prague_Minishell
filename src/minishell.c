/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:44:58 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 09:32:41 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mns_main_loop(t_data *data)
{
	while (mns_init_data(data) != MNS_ERROR)
	{
		if (data->prompt)
			data->line = readline(data->prompt);
		else 
			data->line = readline(PROMPT_FULL);
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
	if (mns_init_env(envp, &data) == MNS_ERROR)
		return (1);
	signal(SIGINT, mns_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	mns_main_loop(&data);
}
