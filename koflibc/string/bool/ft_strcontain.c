/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:49:56 by tate              #+#    #+#             */
/*   Updated: 2022/12/08 15:59:04 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sources.h"

int	ft_strcontain(char *to_count, char target)
{
	while (*to_count)
	{
		if (*to_count == target)
			return (1);
		to_count += 1;
	}
	return (0);
}
