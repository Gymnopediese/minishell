/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:27:06 by albaud            #+#    #+#             */
/*   Updated: 2022/12/07 15:24:30 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	mode(int m)
{
	static int	mo;

	if (m > -1)
		mo = m;
	return (mo);
}

int	level(int m)
{
	static int	mo;

	if (m == 0)
		mo = 0;
	else if (mo == 1 || mo == -1)
		mo += m;
	return (mo);
}

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
	else if (prompt[*index] == '(') // mode(PLEFT)
		level(1);
	else if (prompt[*index] == ')') // mode(PRIGHT)
		level(-1);
	*index += 1;
	if (is_symbole(prompt[*index]))
		parse_error(prompt[*index], prompt[*index + 1]);
	return (1);
}

int	is_symbole(char c)
{
	return (ft_str_index_of("()|<>&", c) != -1);
}

char	*get_next_word(char *prompt, int *index)
{
	t_buff		buffer;
	char		*res;
	int			level;

	buffer.i = 0;
	level = 0;
	res = ft_calloc(1, 1);
	while (prompt[*index] && prompt[*index] != ' ')
	{
		if (prompt[*index] == '"' && ++*index)
			handle_double_quote(prompt, index, &buffer, res);
		else if (is_symbole(prompt[*index])
			&& handle_pipes(prompt, index, &buffer, res))
			break ;
		else if (prompt[*index] == ')' && ++*index)
			level--;
		else if (prompt[*index] == '\\' && ++*index)
		{
			buffer.b[buffer.i++] = prompt[*index];
			*index += 1;
		}
		else if (prompt[*index] == '\'' && ++*index)
			handle_simple_quote(prompt, index, &buffer, res);
		else if (prompt[*index] == '$' && ++*index)
			handle_var(prompt, index, &buffer, res);
		else
		{
			buffer.b[buffer.i++] = prompt[*index];
			*index += 1;
		}
		handle_buffer(&buffer, res);
	}
	if (mode(-1))
		return (0);
	res = ft_strjoin(res, buffer.b);
	if (res == 0)
		ft_garbage_colector(0, 1, 1);
	return (res);
}

t_slst	*parser(char *prompt)
{
	t_slst	*res;
	int		i;
	char	*arg;

	i = 0;
	res = allok(sizeof(*res), 1, 1);
	res->first = 0;
	res->last = 0;
	res->size = 0;
	while (prompt[i])
	{
		mode(0);
		while (prompt[i] && prompt[i] == ' ') //TODOT WHITESPAVE
			i++;
		ft_putendl("new");
		ft_putendl(&prompt[i]);
		arg = get_next_word(prompt, &i);
		ft_putnbrn(mode(-1));
		if (arg && arg[0] && !wildcards(arg, res))
		{
			ft_putendl(arg);
			slst_add_back(res, arg, TEXT, level(2));
			free(arg);
		}
		if (mode(-1))
			slst_add_back(res, "pipe", mode(-1), level(2));
	}
	return (res);
}
