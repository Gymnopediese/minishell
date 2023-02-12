/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:23:03 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 18:10:55 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//TODO: gerer les " " sa mere
//TODO: GLOB GERER LES ERREUR
int	wildcards_match(char *tomatch, char *target)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (target[++i])
	{
		if (target[i] == -1)
		{
			while (target[i] && target[i] == -1)
				i++;
			while (tomatch[j] && tomatch[j] != target[i])
				j++;
		}
		if (!target[i] || !target[j] || target[i] != tomatch[j])
			break ;
		j++;
	}
	return (target[i] - tomatch[j]);
}

char	*ft_replace_char(char *str, char target, char new)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == target)
			str[i] = new;
	}
	return (str);
}

int	wildcards(char *arg, t_slst *res)
{
	char	**glob;
	char	v[778];
	int		len;
	int		i;
	int		match;

	if (ft_strcontain(arg, -1) == 0)
		return (0);
	glob = ft_glob(getcwd(v, 777), 0);
	len = ft_strtablen(glob);
	i = -1;
	match = 0;
	while (++i < len)
	{
		mode(0);
		if (wildcards_match(glob[i], arg) == 0 && ++match)
			slst_add_back(res, ft_strdup(glob[i]), TEXT, level(2));
	}
	if (!match)
	{
		slst_add_back(res, ft_replace_char(arg, -1, '*'), TEXT, level(2));
	}
	ft_free_pp((void **)glob);
	return (1);
}
