/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:13 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 15:55:57 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources.h"

int	ft_remove(t_list **list, void *data, int (*cmp)(), void (*freef)())
{
	t_list	*temp;
	int		ind;

	ind = ft_indexof_list(*list, data, cmp);
	if (ind == -1)
		return (0);
	if (ind == 0)
	{
		*list = (*list)->next;
		return (1);
	}
	temp = ft_get(*list, ind)->next;
	(*freef)(ft_get(*list, ind)->data);
	free(ft_get(*list, ind));
	ft_get(*list, ind - 1)->next = temp;
	return (1);
}
