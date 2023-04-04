/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/04/03 15:00:29 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_pwd(char **args, int argc, int fd)
{
	char	v[778];

	(void) args;
	if (argc == 1)
		ft_putendl_fd(getcwd(v, 777), fd);
	else if (++errno)
		ft_putendl_fd("pwd: too many arguments", 2);
}
