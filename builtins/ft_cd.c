/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 13:07:47 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_cd(char **args, int argc, int fd)
{
	(void) fd;
	errno = 0;
	if (fd != 1)
		return ;
	if (argc == 1)
		chdir(get_vars_value("USER_ZDOTDIR"));
	if (argc == 2)
		chdir(args[1]);
	if (errno)
		printf("minishell: cd: %s\n", strerror(errno));
}
