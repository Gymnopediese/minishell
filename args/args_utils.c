/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:32:45 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 13:37:17 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_the_end(const t_slink *link)
{
	return (link->type == PIPE || link->type == AND
		|| link->type == OR);
}

int	is_redirection(const t_slink *link)
{
	return (link->type == LLEFT || link->type == RRIGHT
		|| link->type == LEFT || link->type == RIGHT);
}

t_slink	*treat_element(t_args *res, t_slink *node, int *i)
{
	if (node->type == RIGHT)
	{
		slst_add_back(res->right, ft_safecpy(node->next->content), 0, 0);
		node = node->next;
	}
	else if (node->type == RRIGHT)
	{
		node = node->next;
		slst_add_back(res->rright, ft_safecpy(node->content), 0, 0);
	}
	else if (node->type == LEFT && ++res->read && ++pipi()->to_pipe)
	{
		node = node->next;
		fd_injection(node->content, pipi()->fd[1]);
	}
	else if (node->type == LLEFT && ++res->read)
	{
		node = node->next;
		pipi()->to_pipe = 1;
		herdock(pipi()->fd[1], node->content);
	}
	else if (++(*i))
		res->args[*i] = node->content;
	node = node->next;
	return (node);
}

t_args	*slst_to_tab(const t_slst *args)
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
		res->args[i + 1] = 0;
		node = treat_element(res, node, &i);
	}
	if (node)
		res->end = node->type;
	close(pipi()->fd[1]);
	res->args[++i] = 0;
	return (res);
}
