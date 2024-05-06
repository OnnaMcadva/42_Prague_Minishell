/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:42 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:47:49 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_com_cd(char *arg)
{
      int   ret;

      if (!arg || ft_strcmp(arg, "~") == 0)
            ret = chdir(getenv("HOME"));
      else
            ret = chdir(arg);
	if (ret == MNS_ERROR)
      {
            ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
            perror (arg);
      }
}