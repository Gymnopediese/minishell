/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 17:17:24 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

	//put_slst(args);
	wait(&exec);
	if (args->first == 0 || args->first->type != 0)
		return ;//TODO print parserror near...
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
			add_vars("?", temp, 1);
			free(temp);
		}
		else if (ft_strtablen(argv->args) == 1)
			declare_variable(argv->args[0]);
	}
	//ft_putnbrn(exec);
	priorities(args, argv, !exec);
	exec_line(args);
}

void	add_var(char *str, int export)
{
	int		n;

	n = ft_strlen_to(str, '=');
	str[n] = 0;
	add_vars(ft_strdup(str), ft_strdup(&str[n + 1]), export);
	str[n] = '=';
}

int	init_env(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		add_var(envp[i], 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_slst	*args;

	(void) argc;
	(void) argv;
	// for (int i=0; envp[i]!=NULL; i++)
    //     printf("%d: %s\n", i, envp[i]);
	init_env(envp);
	pipi()->fd[0] = 0;
	pipi()->fd[1] = 1;
	pipi()->to_pipe = 0;
	debug_history();
	while (1)
	{
		*my_errno() = 0;
		connect_signals();
		prompt = readline("$> ");
		if (!prompt)
			finish("No problemo\n");
		if (prompt[0] != 0)
		{
			add_history(prompt);
			args = parser(prompt);
			if (args)
				exec_line(args);
		}
		free(prompt);
	}
}
