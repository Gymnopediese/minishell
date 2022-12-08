/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:20:44 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 15:55:29 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources.h"

int	ft_remove_at(t_list **list, int ind, void (*freef)())
{
	t_list	*temp;

	if (ind >= ft_size(*list))
		return (-1);
	if (ind == 0)
	{
		temp = *list;
		*list = (*list)->next;
		(*freef)(temp->data);
		free(temp);
		return (1);
	}
	temp = ft_get(*list, ind)->next;
	(*freef)(ft_get(*list, ind)->data);
	free(ft_get(*list, ind));
	ft_get(*list, ind - 1)->next = temp;
	return (1);
}
