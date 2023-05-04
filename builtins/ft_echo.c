/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 14:36:59 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_echo(char **args, int argc, int fd)
{
	int		nline;
	int		i;

	nline = 1;
	i = 0;
	if (argc > 1 && ft_strcmp(args[1], "-n") == 0 && nline--)
		i++;
	while (++i < argc)
	{
		ft_putstr_fd(args[i], fd);
		if (i < argc - 1)
			ft_putstr_fd(" ", fd);
	}
	if (nline)
		ft_putendl_fd("", fd);
}
