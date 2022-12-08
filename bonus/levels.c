/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:29:57 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 17:49:33 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	mode(int m) // Ajouter commentaire STP
{
	static int	mo;

	if (m > -1)
		mo = m;
	return (mo);
}

int	level(int m) // Ajouter commentaire STP
{
	static int	mo;

	if (m == 0)
		mo = 0;
	else if (mo == 1 || mo == -1)
		mo += m;
	return (mo);
}