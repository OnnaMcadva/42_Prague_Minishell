/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:44:58 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 13:04:33 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mns_main_loop(t_data *data, char **envp)
{
	while (mns_init_data(data) != MNS_ERROR)
	{
		data->line = readline(PROMPT);
		if (!data->line)
			mns_com_exit(data, "0");
		if (*data->line)
		{
			if (mns_parse(data) == ALL_FINE)
				mns_execute(data, envp);
			if (data->tkn_count)
				add_history(data->line);
		}
		mns_free_data(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signal (SIGINT, mns_sigint_handler);
	if (argc == 1)
		mns_main_loop(&data, envp);
	else
		printf
		("%s %s ... - boooo, try without arguments!\n", argv[0], argv[1]);
}
