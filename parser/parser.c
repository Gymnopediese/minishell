/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:58:59 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 16:12:08 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handler(char *prompt, int *index, t_buff *buffer, char *res)
{
	if (prompt[*index] == '"' && ++*index)
		handle_double_quote(prompt, index, buffer, res);
	else if (is_symbole(prompt[*index])
		&& handle_pipes(prompt, index))
		return (0);
	else if (prompt[*index] == '*' && ++*index)
		buffer->b[buffer->i++] = -1;
	else if (prompt[*index] == '\'' && ++*index)
		handle_simple_quote(prompt, index, buffer, res);
	else if (prompt[*index] == '~' && (ft_strcontain("/ \t", prompt[*index + 1])
			|| !prompt[*index + 1]) && buffer->i == 0 && ++*index)
		handle_vague(buffer, res);
	else if (prompt[*index] == '$' && ++*index)
		handle_var(prompt, index, buffer, res);
	else if ((prompt[*index] == '\\' && ++(*index)) || 1)
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
		{
			if (errno == 1)
			{
				free(res);
				return (0);
			}
			break ;
		}
	}
	res = ft_strjoin(res, buffer.b);
	if (res == 0)
		finish("Error in get_next_word\n", 1);
	return (res);
}

static int	free_t_slst(t_slst *start)
{
	t_slink	*tmp;
	t_slink	*next;

	tmp = start->first;
	while (tmp)
	{
		next = tmp->next;
		free_t_slink(tmp);
		tmp = next;
	}
	free(start);
	return (1);
}

t_slst	*parser(char *prompt)
{
	t_slst	*res;
	int		i;
	char	*arg;

	i = 0;
	res = ft_malloc(sizeof(*res));
	ft_bzero(res, sizeof(*res));
	level(0);
	while (prompt[i])
	{
		mode(0);
		while (prompt[i] && (prompt[i] == ' ' || prompt[i] == '\t'))
			i++;
		arg = get_next_word(prompt, &i);
		if (!arg && free_t_slst(res))
			return (0);
		if (arg[0] && !wildcards(arg, res))
			slst_add_back(res, arg, TEXT, level(2));
		else
			free(arg);
		if (mode(-1) && ++res->pipe_nbr)
			slst_add_back(res, ft_safecpy("pipe"), mode(-1), level(2));
	}
	return (res);
}
