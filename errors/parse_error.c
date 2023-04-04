/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:48 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/04 12:23:13 by bphilago         ###   ########.fr       */
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

void	finish(char *message, int return_value) // Mettre argument retour
{
	if (message != 0)
		ft_putstr_fd(message, 2);
	close(pipi()->fd[0]);
	close(pipi()->fd[1]);
	free_vars();
	clear_history();
	exit(return_value);
}
