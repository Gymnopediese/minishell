/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:59 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/25 15:27:10 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handle_pipes(const char *prompt, int *index, t_buff *buffer, char *res)
{
	(void) buffer;
	(void) res;

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
	*index += 1;
	while (prompt[*index] == ' ')
		*index += 1;
	if (is_symbole(prompt[*index]))
		parse_error(prompt[*index], prompt[*index + 1]);
	return (1);
}

int	is_symbole(char c)
{
	return (ft_str_index_of("()|<>&", c) != -1);
}

int	handler(char *prompt, int *index, t_buff *buffer, char *res)
{
	if (prompt[*index] == '"' && ++*index)
		handle_double_quote(prompt, index, buffer, res);
	else if (is_symbole(prompt[*index])
		&& handle_pipes(prompt, index, buffer, res))
		return (0);
	else if (prompt[*index] == '\\' && ++*index)
	{
		buffer->b[buffer->i++] = prompt[*index];
		*index += 1;
	}
	else if (prompt[*index] == '*' && ++*index)
		buffer->b[buffer->i++] = -1;
	else if (prompt[*index] == '\'' && ++*index)
		handle_simple_quote(prompt, index, buffer, res);
	else if (prompt[*index] == '~' && (prompt[*index + 1] == ' '
			|| prompt[*index + 1] == 0) && buffer->i == 0 && ++*index)
		handle_vague(buffer, res);
	else if (prompt[*index] == '$' && ++*index)
		handle_var(prompt, index, buffer, res);
	else
	{
		buffer->b[buffer->i++] = prompt[*index];
		*index += 1;
	}
	handle_buffer(buffer, res);
	return (1);
}

static char	*get_next_word(char *prompt, int *index)
{
	t_buff		buffer;
	char		*res;

	buffer.i = 0;
	res = ft_malloc(1);
	handle_buffer(&buffer, res);
	while (prompt[*index] && prompt[*index] != ' ')
	{
		if (!handler(prompt, index, &buffer, res))
			break ;
	}
	res = ft_strjoin(res, buffer.b);
	if (res == 0)
		finish("Error in get_next_word\n", 1);
	return (res);
}

t_slst	*parser(char *prompt)
{
	t_slst	*res;
	int		i;
	char	*arg;

	i = 0;
	res = ft_malloc(sizeof(*res));
	res->first = 0;
	res->last = 0;
	res->size = 0;
	level(0);
	while (prompt[i])
	{
		mode(0);
		while (prompt[i] && prompt[i] == ' ') // TODO is white space
			i++;
		arg = get_next_word(prompt, &i);
		if (arg[0] && !wildcards(arg, res))
		{
			slst_add_back(res, arg, TEXT, level(2));
		}
		else
			free(arg);
		if (mode(-1))
			slst_add_back(res, ft_safecpy("pipe"), mode(-1), level(2));
	}
	return (res);
}
