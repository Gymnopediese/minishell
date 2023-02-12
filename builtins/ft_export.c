/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 17:13:29 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_export(char **args, int argc, int fd)
{
	int	i;

	(void) fd;

	if (argc == 1)
	{
		print_vars();
		return ;
	}
	i = 0;
	while (++i < argc)
	{
		if (ft_strcontain(args[i], '='))
			add_var(args[i]);
		else
			export_var(args[i]);
	}
}
