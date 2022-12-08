/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 13:08:18 by albaud           ###   ########.fr       */
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
		chdir("~");
	if (argc == 2)
		chdir(args[1]);
	if (argc > 2)
		ft_putendl_fd("cd: too many arguments", 2);
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
}
