/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:44:58 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/17 14:52:49 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signal (SIGINT, mns_sigint_handler);
	if (argc == 1)
	{
		while (mns_init(&data) == ALL_FINE)
		{
			data.line = readline(PROMPT);
			if (!data.line)
				return (mns_free_data(&data), 0);
			if (*data.line)
			{
				if (mns_parse(&data) == ALL_FINE)
					mns_execute(&data, envp);
				if (data.tkn_count)
					add_history(data.line);
			}
			mns_free_data(&data);
		}
	}
	else
		printf
		("%s %s ... - boooo, try without arguments!\n", argv[0], argv[1]);
}
