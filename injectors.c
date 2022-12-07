/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injectors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:58:58 by albaud            #+#    #+#             */
/*   Updated: 2022/12/07 14:37:36 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	open_fds(t_args *args, int *fds)
{
	t_slink	*start;
	int		index;

	index = 0;
	start = args->right->first;
	while (start)
	{
		fds[index++] = open(start->content, O_WRONLY | O_CREAT);
		start = start->next;
	}
	start = args->rright->first;
	while (start)
	{
		fds[index++] = open(start->content, O_WRONLY | O_CREAT | O_APPEND);
		start = start->next;
	}
}

int	filename_injection(t_args *args, int read_fd)
{
	char	buffer[1000];
	int		size;
	int		i;
	int		*fds;
	int		fds_len;

	fds_len = args->right->size + args->rright->size;
	fds = allok(fds_len, sizeof(4), 1);
	open_fds(args, fds);
	size = 1;
	while (size)
	{
		size = read(read_fd, buffer, 999);
		if (size == -1)
			return (0);
		buffer[size] = 0;
		i = -1;
		while (++i < fds_len)
			ft_putstr_fd(buffer, fds[i]);
	}
	return (0);
}
