/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:26 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 15:10:50 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

#include "../header.h"

void	ft_export(char **args, int argc, int fd)
{
	int	i;

	if (argc == 1)
	{
		print_vars(1, fd, 1);
		return ;
	}
	i = 0;
	while (++i < argc)
	{
		if (!declare_variable(args[i], 1))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			errno = 1;
		}
	}
}
