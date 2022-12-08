/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 02:05:28 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_slst(t_slst *lst)
{
	t_slink	*n;

	n = lst->first;
	ft_putendl("printing list");
	while (n)
	{
		ft_putendl(n->content);
		n = n->next;
	}
	ft_putendl("printing list done");
}

void	put_pipi(void)
{
	ft_putendl("printing pipi");
	ft_putia_clean(pipi()->fd, 2);
	ft_putnbrn(pipi()->to_pipe);
	ft_putendl("printing pipi done");
}

void	priorities(t_slst *args, t_args *argv, int success)
{
	t_slink	*start;

	start = args->first;
	if (argv->end == OR && success)
	{
		while (start && start->level >= args->first->level)
			start = start->next;
	}
	else if (argv->end == AND && !success)
	{
		while (start && start->level >= args->first->level)
			start = start->next;
	}
	else
	{
		while (start && !is_the_end(start))
			start = start->next;
		if (start != 0)
			start = start->next;
	}
	args->first = start;
}

void	exec_line(t_slst *args)
{
	int		exec;
	char	*temp;
	t_args	*argv;

	argv = slst_to_tab(args);
	exec = 0;
	if (args->first == 0)
		return ;
	if (builtins(args) == 0)
	{
		exec = execute(argv);
		temp = ft_itoa(exec);
		vars("?", temp);
		free(temp);
	}
	ft_putnbrn(exec);
	priorities(args, argv, !exec);
	exec_line(args);
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
	pipi()->fd[0] = 0;
	pipi()->fd[1] = 1;
	pipi()->to_pipe = 0;
	add_history("cat Makefile | wc");
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
