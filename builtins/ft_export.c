/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:26 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/27 15:01:11 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_export(char **args, int argc, int fd)
{
	(void) args;
	(void) argc;
	(void) fd;

	if (argc > 1)
	{
		if (!declare_variable(args[1], 1))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
	}
	else
		print_vars(1, fd, 1);
}
