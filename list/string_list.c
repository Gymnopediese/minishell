/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:56:30 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/07 16:01:09 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_slink	*slst_new(char *str, int type, int level)
{
	t_slink	*new_lst;

	new_lst = ft_calloc(1, sizeof(t_slink));
	new_lst->content = strdup(str);
	new_lst->type = type;
	new_lst->level = level;
	new_lst->next = 0;
	return (new_lst);
}

void	slst_add_back(t_slst *lst, char *str, int type, int level)
{
	t_slink	*new_link;

	new_link = slst_new(str, type, level);
	if (lst->first)
	{
		lst->last->next = new_link;
		lst->last = new_link;
		lst->size += 1;
	}
	else
	{
		lst->first = new_link;
		lst->last = new_link;
		lst->size = 1;
	}
}

void	slst_add_front(t_slst *lst, char *str, int type, int level)
{
	t_slink	*new_link;

	new_link = slst_new(str, type, level);
	new_link->level = level;
	new_link->type = type;
	if (lst->first)
	{
		new_link->next = lst->first;
		lst->last = new_link;
		lst->size += 1;
	}
	else
	{
		lst->first = new_link;
		lst->last = new_link;
		lst->size = 1;
	}
}
