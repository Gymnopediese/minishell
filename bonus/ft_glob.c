/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:31:01 by albaud            #+#    #+#             */
/*   Updated: 2023/04/24 12:03:21 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../koflibc/sources.h"
#include "../header.h"
#include <dirent.h>

char	**ft_glob(char *dirname, int mode)
{	
	char			**res;
	DIR				*d;
	struct dirent	*dir;
	int				i;

	d = opendir(dirname);
	i = -1;
	if (d)
	{
		res = ft_malloc((ft_count_dir(dirname, mode) + 1) * sizeof(char *)); // Attention malloc non protege
		dir = readdir(d);
		while (dir != NULL)
		{
			if (mode || dir->d_name[0] != '.')
				res[++i] = ft_safecpy(dir->d_name); // Gerer le malloc et le free car pas dans le garbage collector
			dir = readdir(d);
		}
		closedir(d);
		res[++i] = 0;
		ft_bubble_sort_sa(res);
		return (res);
	}
	return (0);
}
