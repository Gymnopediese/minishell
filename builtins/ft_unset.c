/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:37 by bphilago          #+#    #+#             */
/*   Updated: 2023/03/21 12:49:15 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_unset(char **args, int argc, int fd)
{
	int	i;

	(void) fd;
	i = 0;
	errno = 0;
	if (argc == 1)
		ft_putendl_fd("unset: not enough arguments", 2);
	else
	{
		while (++i < argc)
			del_vars(args[i]);
	}
	//if (errno) pas le droit au errno
		//ft_putendl_fd(strerror(errno), 2);
}
