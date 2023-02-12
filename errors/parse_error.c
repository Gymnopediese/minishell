/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:45:44 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 12:37:36 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	parse_error(char a, char b)
{
	if (is_symbole(a) && is_symbole(b))
		printf("minish: parse error near `%c%c'\n", a, b);
	else if (is_symbole(a))
		printf("minish: parse error near `%c'\n", a);
	else
		return (0);
	return (1);
}

int	*my_errno(void)
{
	static int	err[1];

	return (err);
}

void	finish(char *message)
{
	if (message != 0)
		ft_putstr_fd(message, 2);
	close(pipi()->fd[0]);
	close(pipi()->fd[1]);
	free_vars();
	clear_history();
	ft_garbage_colector(0, 1, 1); // EN dernier
}
