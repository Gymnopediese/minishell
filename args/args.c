/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:21:16 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 16:02:27 by bphilago         ###   ########.fr       */
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

t_args	*allok_args(const t_slst *args)
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

void	herdock(int fd, char *sub)
{
	char	*herd;

	while (1)
	{
		herd = readline("pipe heredoc> ");
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
