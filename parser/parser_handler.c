/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:27:06 by albaud            #+#    #+#             */
/*   Updated: 2023/03/27 11:36:49 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_buffer(t_buff *buffer, char *res)
{
	buffer->b[buffer->i] = 0;
	if (buffer->i == 10000)
	{
		res = ft_strjoin(res, buffer->b);
		if (res == 0)
			ft_garbage_colector(0, 1, 1);
		buffer->i = 0;
	}
}

void	handle_double_quote(char *prompt, int *index, t_buff *buffer, char *res)
{
	while (prompt[*index] && prompt[*index] != '"')
	{
		if (prompt[*index] == '$' && ++*index)
			handle_var(prompt, index, buffer, res);
		else
		{
			buffer->b[buffer->i++] = prompt[*index];
			*index += 1;
		}
		handle_buffer(buffer, res);

	}
	*index += 1;
}

void	handle_var(char *prompt, int *index, t_buff *buffer, char *res)
{
	int			i;
	char		*var_name;
	const char	*data;

	i = 0;
	while (prompt[*index + i] && prompt[*index + i] != '"'
		&& prompt[*index + i] != ' ' && prompt[*index + i] != '\'')
		++i;
	var_name = allok(sizeof(*var_name), (i + 1), 1);
	ft_strncpy(var_name, prompt + *index, i);
	*index += i;
	data = get_vars_value(var_name);
	i = -1;
	while (data[++i])
	{
		buffer->b[buffer->i++] = data[i];
		handle_buffer(buffer, res);
	}
}

void	handle_simple_quote(char *prompt, int *index, t_buff *buffer, char *res)
{
	while (prompt[*index] && prompt[*index] != '\'')
	{
		buffer->b[buffer->i++] = prompt[*index];
		*index += 1;
		handle_buffer(buffer, res);
	}
	*index += 1;
}
