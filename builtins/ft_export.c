/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:26 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/27 12:39:26 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_export(char **args, int argc, int fd)
{
	(void) args;
	(void) argc;
	(void) fd;

	if (argc > 1)
		declare_variable(args[1], 1); // TODO Export sans changer la valeur
	else
		print_vars(1, fd);
}
