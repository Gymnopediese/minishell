/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_fd_injection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:54:45 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 13:55:11 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	fd_fd_injection(int dst, int src)
{
	char	buffer[1000];
	int		size;

	size = 1;
	while (size)
	{
		size = read(src, buffer, 999);
		if (size == -1)
			return (0);
		buffer[size] = 0;
		ft_putstr_fd(buffer, dst);
	}
	return (0);
}