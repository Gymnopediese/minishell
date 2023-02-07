/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/02/07 14:04:12 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

//gere les priorité
void	priorities(t_slst *args, t_args *argv, int success)
{
	t_slink	*start;

	start = args->first;
	if (argv->end == OR && success)
	{
		while (start && start->level >= args->first->level)
		{
			if (start->type == AND && start->level == args->first->level)
			{
				start = start->next;
				break ;
			}
			start = start->next;
		}
	}
	else if (argv->end == AND && !success)
	{
		while (start && start->level >= args->first->level)
		{
			if (start->type == OR && start->level == args->first->level)
			{
				start = start->next;
				break ;
			}
			start = start->next;
		}
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

	wait(&exec);
	if (args->first == 0)
		return ;
	argv = slst_to_tab(args);
	exec = 0;
	if (args->first == 0)
		return ;
	if (builtins(argv) == -1)
	{
		exec = execute(argv);
		if (exec != -1)
		{
			temp = ft_itoa(exec);
			vars("?", temp, VARS_ADD);
			free(temp);
		}
		else if (ft_strtablen(argv->args) == 1)
			declare_variable(argv->args[0]);
	}
	//ft_putnbrn(exec);
	priorities(args, argv, !exec);
	exec_line(args);
}

void	init_vars(void)
{
	vars("Test", "Je suis la valeur d'une variable", VARS_ADD);
	vars("PATH", "/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/bin\
:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Library/Frameworks/Mono\
.framework/Versions/Current/Commands:/Users/albaud/opt/anaconda3/bin\
:/Users/albaud/opt/anaconda3/condabin:/opt/homebrew/bin\
:/opt/homebrew/sbin", VARS_ADD);
	vars("?", "0", VARS_ADD);
}

int	main(void)
{
	char	*prompt;

	init_vars();
	pipi()->fd[0] = 0;
	pipi()->fd[1] = 1;
	pipi()->to_pipe = 0;
	add_history("cat Makefile | wc");
	add_history("ls > test >> test | cat -e");
	add_history("norminette | grep -v OK");
	add_history("echo -n salut");
	add_history("(ls asd && ls) || ls");
	while (1)
	{
		connect_signals();
		prompt = readline("$> ");
		if (!prompt)
			finish("No problemo\n");
		if (prompt[0] != 0)
		{
			add_history(prompt);
			exec_line(parser(prompt));
		}
		free(prompt);
	}
}
