/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:37 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 15:12:36 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_unset(char **args, int argc, int fd)
{
	int	i;

	(void) fd;
	i = 0;
	while (++i < argc)
	{
		if (!del_vars(args[i]))
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			errno = 1;
		}
	}
}
