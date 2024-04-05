/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:44:58 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/05 10:54:52 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 1)
	{
		signal(SIGINT, exit);
		while (mns_init(&data) == ALL_FINE)
		{
			data.line = readline(PROMPT);
			if (ft_strlen(data.line))
				if (mns_parse(&data) == ALL_FINE)
					mns_execute(&data, envp);
			mns_free_data(&data);
			// todo: if output doesn't end with \n - put it before the next prompt
		}
	}
	else
		printf
		("%s %s ... - boooo, try without arguments!\n", argv[0], argv[1]);
}
