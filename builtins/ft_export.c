/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:26 by bphilago          #+#    #+#             */
/*   Updated: 2023/03/21 10:58:29 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_export(char **args, int argc, int fd)
{
	(void) args;
	(void) argc;
	(void) fd;

	vars(0, 0, VARS_PRINT);
}
