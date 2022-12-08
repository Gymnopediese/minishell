/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contain_sa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:02:08 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 15:58:19 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sources.h"

int	ft_contain_sa(char **to_count, char *target)
{
	int	i;

	i = 0;
	while (to_count[i])
	{
		if (ft_strcmp(to_count[i], target) == 0)
			return (1);
		i++;
	}
	return (0);
}
