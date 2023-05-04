/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:02:47 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 15:36:00 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	try_builtins(t_args *argv)
{
	char	*temp;

	if (ft_strtablen(argv->args) == 0 || builtins(argv) == -1)
		return (0);
	temp = ft_itoa(errno);
	if (temp == 0)
		finish("Malloc error\n", 1);
	add_vars("?", temp, 0);
	free(temp);
	return (1);
}

int	try_execute(t_args *argv)
{
	char	*temp;

	if (ft_strtablen(argv->args) == 0)
		return (0);
	errno = execute(argv);
	temp = ft_itoa(errno);
	if (temp == 0)
		finish("Malloc error\n", 1);
	add_vars("?", temp, 0);
	free(temp);
	return (1);
}

int	try_declare(t_args *argv)
{
	if (ft_strtablen(argv->args) == 1
		&& is_variable_declaration(argv->args[0]))
	{
		declare_variable(argv->args[0], 2);
		return (1);
	}
	return (0);
}
