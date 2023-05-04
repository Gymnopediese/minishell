/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_injection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:55:28 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 13:35:54 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	fd_injection(char *filename, int fd)
{
	char	buffer[1000];
	int		size;
	int		file;

	file = open(filename, O_RDONLY);
	size = 1;
	while (size)
	{
		size = read(file, buffer, 999);
		if (size == -1)
			return (0);
		buffer[size] = 0;
		ft_putstr_fd(buffer, fd);
	}
	return (0);
}
