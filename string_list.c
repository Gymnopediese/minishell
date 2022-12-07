/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:56:30 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/07 15:09:52 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	slst_add_back(t_slst *lst, char *str)
{
	t_slink	*new_link;

	new_link = ft_slstnew(str);
	if (lst->first)
	{
		lst->last->next = new_link;
		lst->last = new_link;
	}
	else
	{
		lst->first = new_link;
		lst->last = new_link;
	}
}

t_slink	*slst_new(char *str)
{
	t_slink	*new_lst;

	new_lst = allok(1, sizeof(t_list), 1);
	new_lst->content = str;
	new_lst->next = 0;
	return (new_lst);
}

void	slst_add_front(t_slst *lst, char *str)
{
	t_slink	*new_link;

	new_link = ft_slstnew(str);
	if (lst->first)
	{
		new_link->next = lst->first;
		lst->last = new_link;
	}
	else
	{
		lst->first = new_link;
		lst->last = new_link;
	}
}
