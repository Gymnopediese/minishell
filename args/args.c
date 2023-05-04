/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:21:16 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 13:22:54 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

size_t	arg_num(const t_slink *link)
{
	size_t	res;

	res = 0;
	while (link)
	{
		if (is_the_end(link))
			break ;
		if (!is_redirection(link))
			res++;
		else
			link = link->next;
		link = link->next;
	}
	return (res);
}

static t_args	*allok_args(const t_slst *args)
{
	t_args	*res;

	res = ft_malloc(sizeof(*res));
	res->args = ft_malloc(sizeof(char *) * (arg_num(args->first) + 1));
	res->right = ft_malloc(sizeof(*res->right));
	res->rright = ft_malloc(sizeof(*res->rright));
	res->right->first = 0;
	res->right->last = 0;
	res->right->size = 0;
	res->rright->first = 0;
	res->rright->last = 0;
	res->rright->size = 0;
	res->read = 0;
	res->end = 0;
	return (res);
}

char	*ft_read_nl(int fd)
{
	int		size;
	char	*buffer;
	char	tuffer[3333 + 1];

	buffer = ft_calloc(1, 1);
	size = read(fd, tuffer, 3333);
	while (size)
	{
		tuffer[size] = 0;
		buffer = ft_strjoin(buffer, tuffer);
		if (ft_strcontain(buffer, '\n'))
			break ;
		size = read(fd, tuffer, 3333);
	}
	return (buffer);
}

void	herdock(int fd, char *sub)
{
	char	*herd;

	while (1)
	{
		ft_putstr("heredoc> ");
		herd = ft_read_nl(0);
		if (ft_strlen(herd) > 0)
			herd[ft_strlen(herd) - 1] = 0;
		if (ft_strcmp(sub, herd) == 0)
		{
			free(herd);
			return ;
		}
		else
			ft_putendl_fd(herd, fd);
		free(herd);
		herd = 0;
	}
}
