/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:48 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/27 15:49:43 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	parse_error(char a, char b)
{
	if (is_symbole(a) && is_symbole(b))
	{
		errno = 1;
		printf("minish: syntax error near unexpected token `%c%c'\n", a, b);
	}
	else if (is_symbole(a))
	{
		errno = 1;
		printf("minish: syntax error near unexpected token `%c'\n", a);
	}
}

void	finish(char *message, int return_value) // Mettre argument retour
{
	if (message != 0)
		ft_putstr_fd(message, 2);
	// TODO close les pipes
	free_vars();
	clear_history();
	exit(return_value);
}
