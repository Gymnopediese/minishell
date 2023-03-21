/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:48 by bphilago          #+#    #+#             */
/*   Updated: 2023/03/21 10:58:50 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	parse_error(char a, char b)
{
	if (is_symbole(a) && is_symbole(b))
		printf("minish: parse error near `%c%c'", a, b);
	if (is_symbole(a))
		printf("minish: parse error near `%c'", a);
	//todo: new line
}

void	finish(char *message)
{
	if (message != 0)
		ft_putstr_fd(message, 2);
	close(pipi()->fd[0]);
	close(pipi()->fd[1]);
	vars(0, 0, VARS_FREE);
	clear_history();
	ft_garbage_colector(0, 1, 1); // EN dernier
}
