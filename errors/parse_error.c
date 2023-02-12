/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:45:44 by albaud            #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/02/12 11:39:23 by albaud           ###   ########.fr       */
=======
/*   Updated: 2023/02/07 13:29:03 by bphilago         ###   ########.fr       */
>>>>>>> parent of 4cf0605 (Vars upgarde !)
=======
/*   Updated: 2023/02/07 13:29:03 by bphilago         ###   ########.fr       */
>>>>>>> parent of 4cf0605 (Vars upgarde !)
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
