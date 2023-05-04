/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:59 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 16:25:20 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	check_mode(const char *prompt, int *index)
{
	if (prompt[*index] == '|' && prompt[*index + 1] == '|' && ++*index)
		mode(OR);
	else if (prompt[*index] == '&' && prompt[*index + 1] == '&' && ++*index)
		mode (AND);
	else if (prompt[*index] == '|')
		mode (PIPE);
	else if (prompt[*index] == '<' && prompt[*index + 1] == '<' && ++*index)
		mode(LLEFT);
	else if (prompt[*index] == '<')
		mode(LEFT);
	else if (prompt[*index] == '>' && prompt[*index + 1] == '>' && ++*index)
		mode(RRIGHT);
	else if (prompt[*index] == '>')
		mode(RIGHT);
	else if (prompt[*index] == '(')
		level(1);
	else if (prompt[*index] == ')')
		level(-1);
}

int	handle_pipes(const char *prompt, int *index)
{
	char	temp;

	check_mode(prompt, index);
	temp = prompt[*index];
	*index += 1;
	while (prompt[*index] == ' ')
		*index += 1;
	if (temp == '(' || temp == ')')
		return (1);
	if (ft_str_index_of("|<>&", prompt[*index]) != -1)
		parse_error(prompt[*index], prompt[*index + 1]);
	return (1);
}

int	is_symbole(char c)
{
	return (ft_str_index_of("()|<>&", c) != -1);
}
