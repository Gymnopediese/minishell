/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:27:06 by albaud            #+#    #+#             */
/*   Updated: 2022/12/06 14:42:06 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*get_next_word(char *prompt, int *index)
{
	t_buff		buffer;
	char		*res;

	res = allok(1, 1, 1);
	while (prompt[*index] && prompt[*index] != ' ')
	{
		if (prompt[*index] == '"' && ++*index)
			handle_double_quote(prompt, index, &buffer, res);
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
	res = ft_strjoin(res, buffer.b);
	if (res == 0)
		ft_garbage_colector(0, 1, 1);
	while (prompt[*index] == ' ')
		*index += 1;
	return (res);
}

enum
{
	PIPE,
	LEFT,
	LLEFT,
	RIGHT,
	RRIGHT,
};

void	handle_pipes(char *arg, t_list *str_list, t_slst *res)
{
	int	mode;

	(void) str_list;
	mode = -1;
	if (ft_strcmp(arg, "|") == 0)
		mode = PIPE;
	else if (ft_strcmp(arg, "<") == 0)
		mode = LEFT;
	else if (ft_strcmp(arg, "<<") == 0)
		mode = LLEFT;
	else if (ft_strcmp(arg, ">>") == 0)
		mode = RRIGHT;
	else if (ft_strcmp(arg, ">") == 0)
		mode = RIGHT;
	slst_add_back(res, arg);
}

t_slst	*parser(char *prompt)
{
	t_slst	*res;
	int		i;
	char	*arg;

	i = 0;
	while (prompt[i] && prompt[i] == ' ') //TODOT WHITESPAVE
		i++;
	res = allok(sizeof(*res), 1, 1); // A free dans le retour
	while (prompt[i])
	{
		arg = get_next_word(prompt, &i);
		//ft_putendl(arg);
		slst_add_back(res, arg);
	}
	return (res);
}
