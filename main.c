/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2022/12/07 14:57:18 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_line(t_slst *args)
{
	int		exec;
	char	*temp;

	if (builtins(args) == 0)
	{
		exec = execute(args);
		temp = ft_itoa(exec);
		vars("?", temp);
		free(temp);
		if (exec != 0)
		{
			ft_putendl(strerror(errno));
		}
	}
}

void	init_vars(void)
{
	vars("Test", "Je suis la valeur d'une variable");
	vars("PATH", "/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/bin\
:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Library/Frameworks/Mono\
.framework/Versions/Current/Commands:/Users/albaud/opt/anaconda3/bin\
:/Users/albaud/opt/anaconda3/condabin:/opt/homebrew/bin\
:/opt/homebrew/sbin");
	vars("?", "0");
}

int	main(void)
{
	char	*prompt;

	init_vars();
	while (1)
	{
		connect_signals();
		prompt = readline("$> ");
		if (!prompt)
			ft_garbage_colector(0, 1, 1);
		add_history(prompt);
		exec_line(parser(prompt));
	}
}
