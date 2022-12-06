/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:31:03 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/06 14:26:46 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	vlst_add_front(t_vlink **lst, t_var var)
{
	t_vlink	*new_link;

	new_link = vlst_new(var);
	new_link->next = *lst;
	*lst = new_link;
}

t_vlink	*vlst_new(t_var content)
{
	t_vlink	*new_lst;

	new_lst = allok(1, sizeof(*new_lst), 1);
	new_lst->content = content;
	new_lst->next = 0;
	return (new_lst);
}
