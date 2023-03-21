/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:30:44 by albaud            #+#    #+#             */
/*   Updated: 2023/03/21 11:16:02 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <dirent.h>

int	ft_count_dir(char *dirname, int mode)
{	
	DIR				*d;
	struct dirent	*dir;
	int				counter;

	d = opendir(dirname);
	counter = 0;
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (mode || dir->d_name[0] != '.')
				counter++;
			dir = readdir(d);
		}
		closedir(d);
	}
	return (counter);
}