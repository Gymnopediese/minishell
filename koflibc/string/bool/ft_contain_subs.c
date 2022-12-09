/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contain_subs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:29:01 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 15:58:45 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sources.h"

int	ft_contain_subs(char *to_count, char *target)
{
	while (*to_count)
	{
		if (ft_strcmpl(to_count, target) == 0)
			return (1);
		to_count += 1;
	}
	return (0);
}
