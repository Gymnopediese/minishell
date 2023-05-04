/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:23:03 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 13:42:00 by bphilago         ###   ########.fr       */
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
		if (!target[i] || !target[i] || target[i] != tomatch[j])
			break ;
		j++;
	}
	return (target[i] - tomatch[j]);
}

int	wildcards_error(int match, char *arg)
{
	int		i;

	if (!match)
	{
		i = -1;
		while (arg[++i])
			if (arg[i] == -1)
				arg[i] = '*';
		ft_putstr_fd("minish: no matches found: ", 2);
		ft_putstr_fd(arg, 2);
	}
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
			slst_add_back(res, ft_safecpy(glob[i]), TEXT, level(2));
	}
	wildcards_error(match, arg);
	ft_free_pp((void **)glob);
	return (1);
}
