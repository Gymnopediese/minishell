/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 18:12:46 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//gere les priorité

void	exec_line(t_slst *args)
{
	int		exec;
	char	*temp;
	t_args	*argv;

	wait(&exec);
	if (args->first == 0 || args->first->type != 0)
		return ; //TODO print parserror near...
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

	(void)argc;
	(void)argv;
	init_env(envp);
	init_pipi();
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
