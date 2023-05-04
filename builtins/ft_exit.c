/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:15 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/27 14:36:52 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_exit(char **args, int argc, int fd)
{
	(void) fd;
	if (argc == 1)
		finish("exit\n", 0);
	if (ft_isnum(args[1]))
	{
		if (argc == 2)
			finish("exit\n", ft_atoi(args[1]));
		else if (++errno)
			ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else
	{
		printf("minishell: %s: exit: numeric argument required\n", args[1]);
		finish("exit\n", 255);
	}
}
