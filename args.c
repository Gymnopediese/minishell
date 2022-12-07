/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:21:16 by albaud            #+#    #+#             */
/*   Updated: 2022/12/07 14:42:18 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_the_end(t_slink *link)
{
	return (link->type == PIPE || link->type == AND
		|| link->type == OR);
}

int	is_redirection(t_slink *link)
{
	return (link->type == LLEFT || link->type == RRIGHT
		|| link->type == LEFT || link->type == RIGHT);
}

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


//pas safe

//convertie notre list en table de string (en args pout execv),
//TODO: CONVERTIRE JUSQUA TOMBER SUR UN SYMBOLE (|<> etc...)
t_args	slst_to_tab(t_slst *args)
{
	t_args	res;
	t_slink	*node;	
	int		i;

	i = -1;
	node = args->first;
	res.args = allok(sizeof(char *), arg_num(node), 1);
	if (pipe(res.fd) == -1)
		ft_garbage_colector(0, 1, 1);
	//TODO treat no args after <>><>><<<
	while (node && !is_the_end(node))
	{
		if (node->type == RIGHT)
		{
			slst_add_back(res.right, node->next->content, 0, 0);
			node = node->next;
		}
		else if (node->type == RRIGHT)
		{
			slst_add_back(res.rright, node->next->content, 0, 0);
			node = node->next;
		}
		else if (node->type == LEFT)
		{
			fd_injection(node->next->content, res.fd[1]);
			node = node->next;
		}
		else if (node->type == LLEFT)
		{
			fd_injection(node->next->content, res.fd[1]);
			node = node->next;
		}
		else
			res.args[++i] = node->content;
		node = node->next;
	}
	if (node)
		res.end = node->type;
	return (res);
}
