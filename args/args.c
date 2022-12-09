/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:21:16 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 13:36:47 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	arg_num(t_slink *link)
{
	int	res;

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

	res = allok(sizeof(*res), 1, 1);
	res->args = allok(sizeof(char *), arg_num(args->first), 1);
	res->right = allok(sizeof(*res->right), 1, 1);
	res->rright = allok(sizeof(*res->right), 1, 1);
	res->right->first = 0;
	res->right->last = 0;
	res->rright->first = 0;
	res->rright->last = 0;
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
	else if (node->type == LEFT)
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
	{
		pipi()->to_pipe = 1;
		pipe(pipi()->fd);
	}
	while (node && !is_the_end(node))
	{
		treat_element(res, node, &i);
		node = node->next;
	}
	if (node)
		res->end = node->type;
	close(pipi()->fd[1]);
	res->args[++i] = 0;
	return (res);
}
