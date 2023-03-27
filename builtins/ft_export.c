/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:26 by bphilago          #+#    #+#             */
/*   Updated: 2023/03/27 11:25:49 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_export(char **args, int argc, int fd)
{
	(void) args;
	(void) argc;
	(void) fd;

	if (argc > 1)
		declare_variable(args[1], 1);
	else
		print_vars(1);
}
