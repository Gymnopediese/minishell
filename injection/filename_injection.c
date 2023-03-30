/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_injection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:58:58 by albaud            #+#    #+#             */
/*   Updated: 2023/03/30 15:07:19 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

#define DEBUG_PATH "tests/"

void	open_fds(t_args *args, int *fds)
{
	t_slink	*start;
	int		index;

	index = 0;
	start = args->right->first;
	while (start)
	{
		fds[index++] = open(ft_strjoin(DEBUG_PATH, start->content),
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		start = start->next;
	}
	start = args->rright->first;
	while (start)
	{
		fds[index++] = open(ft_strjoin(DEBUG_PATH, start->content),
				O_WRONLY | O_APPEND | O_CREAT, 0666);
		start = start->next;
	}
}

void	write_in_fds(char *buffer, int *fds, int fds_len, int pip)
{
	int	i;

	i = -1;
	while (++i < fds_len)
		ft_putstr_fd(buffer, fds[i]);
	if (pip == PIPE)
		ft_putstr_fd(buffer, pipi()->fd[1]);
}

void	close_fds(int *fds, int fds_len)
{
	int	i;

	i = -1;
	while (++i < fds_len)
		close(fds[i]);
}

int	filename_injection(t_args *args, int read_fd)
{
	char	buffer[1000];
	int		size;
	int		*fds;
	size_t	fds_len;

	fds_len = args->right->size + args->rright->size;
	ft_mf(MALLOC, (void **)&fds, sizeof(int) * fds_len);
	open_fds(args, fds);
	size = 1;
	if (args->end == PIPE)
		pipe(pipi()->fd);
	while (size)
	{
		size = read(read_fd, buffer, 999);
		if (size == -1)
			return (0);
		buffer[size] = 0;
		write_in_fds(buffer, fds, fds_len, args->end);
	}
	close_fds(fds, fds_len);
	return (0);
}
