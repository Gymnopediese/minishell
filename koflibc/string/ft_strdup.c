/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:37:13 by tate              #+#    #+#             */
/*   Updated: 2023/03/21 11:24:01 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(src);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == 0)
		return (str);
	i = -1;
	while (++i < len)
		str[i] = src[i];
	str[i] = 0;
	return (str);
}
