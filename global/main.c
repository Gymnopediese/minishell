/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 13:25:48 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_argv(t_args *argv)
{
	free_slist(argv->right);
	free_slist(argv->rright);
	free(argv->args);
	free(argv->right);
	free(argv->rright);
	free(argv);
}

static int	is_variable_declaration(char *instruction)
{
	if (ft_strcontain(instruction, '='))
		return (1);
	else
		return (0);
}

static void	exec_line(t_slst *args)
{
	int		exec;
	t_args	*argv;

	wait(&exec);
	if (args->first == 0)
		return ;
	errno = 0;
	argv = slst_to_tab(args);
	if (!try_builtins(argv) && !try_declare(argv) && !try_execute(argv))
		;
	priorities(args, argv, !errno);
	free_argv(argv);
	exec_line(args);
}

int	main(__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv, __attribute__((unused))char **envp)
{	
	char	*prompt;
	t_slst	*list;

	import_env(envp);
	pipi()->fd[0] = 0;
	pipi()->fd[1] = 1;
	pipi()->to_pipe = 0;
	printf("welcome to our minishell :)\n");
	while (1)
	{
		connect_signals();
		prompt = readline("$> ");
		if (!prompt)
			finish("exit\n", 0);
		if (prompt[0] != 0)
		{
			add_history(prompt);
			list = parser(prompt);
			exec_line(list);
			free(list);
		}
		free(prompt);
	}
}
