/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:21:16 by albaud            #+#    #+#             */
/*   Updated: 2023/04/04 13:35:08 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

size_t	arg_num(t_slink *link)
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

t_args	*allok_args(t_slst *args)
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
		herd = readline("herdoc> ");
		if (strcmp(sub, herd) == 0)
			return ;
		else
			ft_putendl_fd(herd, fd);
	}
}

void	treat_element(t_args *res, t_slink *node, int *i)
{
	if (node->type == RIGHT)
	{
		slst_add_back(res->right, node->next->content, 0, 0);
		node = node->next;
	}
	else if (node->type == RRIGHT)
	{
		node = node->next;
		slst_add_back(res->rright, node->content, 0, 0);
	}
	else if (node->type == LEFT && ++res->read)
	{
		node = node->next;
		fd_injection(node->content, pipi()->fd[1]);
	}
	else if (node->type == LLEFT)
	{
		node = node->next;
		herdock(pipi()->fd[1], node->content);
	}
	else
	{
		*i += 1;
		res->args[*i] = node->content;
	}
}

t_args	*slst_to_tab(t_slst *args)
{
	t_args	*res;
	t_slink	*node;
	int		i;

	i = -1;
	node = args->first;
	res = allok_args(args);
	if (pipi()->to_pipe == 0)
		pipe(pipi()->fd);
	while (node && !is_the_end(node))
	{
		res->args[i+1] = 0;
		ft_putstra_clean(res->args);
		treat_element(res, node, &i);
		node = node->next;
	}
	if (node)
		res->end = node->type;
	close(pipi()->fd[1]);
	res->args[++i] = 0;
	return (res);
}
