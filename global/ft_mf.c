/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:47:02 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 13:36:15 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*ft_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		finish("Malloc error", 1);
	else
		return (result);
	return (0);
}

// A deplacer dans un autre fichier
char	*ft_safecpy(const char *src)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(src);
	str = ft_malloc(sizeof(*str) * (len + 1));
	i = -1;
	while (++i < len)
		str[i] = src[i];
	str[i] = 0;
	return (str);
}
