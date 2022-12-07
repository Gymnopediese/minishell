/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:45:44 by albaud            #+#    #+#             */
/*   Updated: 2022/12/07 09:45:55 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	parse_error(char a, char b)
{
	if (is_symbole(a) && is_symbole(b))
		printf("minish: parse error near `%c%c'", a, b);
	if (is_symbole(a))
		printf("minish: parse error near `%c'", a);
	//todo: new line
}
