/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:51:33 by albaud            #+#    #+#             */
/*   Updated: 2022/12/09 12:06:59 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	mode(int m)
{
	static int	mo;

	if (m > -1)
		mo = m;
	return (mo);
}

int	level(int new_level)
{
	static int	current_level;

	if (new_level == 0)
		current_level = 0;
	else if (new_level == 1 || new_level == -1)
		current_level += new_level;
	return (current_level);
}
