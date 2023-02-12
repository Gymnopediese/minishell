/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 11:40:22 by albaud           ###   ########.fr       */
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
			vars(args[i], "", VARS_ADD); //TODO true_delete
	}
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
}
