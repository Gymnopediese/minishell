/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/04/04 13:35:46 by bphilago         ###   ########.fr       */
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

// //gere les priorité
// void	priorities(t_slst *args, t_args *argv, int success)
// {
// 	t_slink	*start;

// 	start = args->first;
// 	if (argv->end == OR && success)
// 	{
// 		while (start && start->level >= args->first->level)
// 		{
// 			if (start->type == AND && start->level == args->first->level)
// 			{
// 				start = start->next;
// 				break ;
// 			}
// 			start = start->next;
// 		}
// 	}
// 	else if (argv->end == AND && !success)
// 	{
// 		while (start && start->level >= args->first->level)
// 		{
// 			if (start->type == OR && start->level == args->first->level)
// 			{
// 				start = start->next;
// 				break ;
// 			}
// 			start = start->next;
// 		}
// 	}
// 	else
// 	{
// 		while (start && !is_the_end(start))
// 			start = start->next;
// 		if (start != 0)
// 			start = start->next;
// 	}
// 	args->first = start;
// }

void	exec_line(t_slst *args)
{
	int		exec;
	char	*temp;
	t_args	*argv;

	wait(&exec);
	if (args->first == 0)
		return ;
	exec = 0;
	argv = slst_to_tab(args);
	ft_putstra_clean(argv->args);
	if (builtins(argv) == -1)
	{
		exec = execute(argv);
		if (exec != -1)
		{
			temp = ft_itoa(exec); //malloc non protege
			add_vars("?", temp, 1); //export ou pas ?
			free(temp);
		}
		else if (ft_strtablen(argv->args) == 1)
			declare_variable(argv->args[0], 0); //export ou pas ?
	}
	else
	{
		exec = errno;
		temp = ft_itoa(exec); //malloc non protege
		add_vars("?", temp, 1); //export ou pas ?
		free(temp);
	}
	priorities(args, argv, !exec);
	exec_line(args);
}

// A deplacer dans un autre fichier
char	*ft_safecpy(const char *src)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(src);
	str = ft_malloc(sizeof(*str) * (len + 1));
	i = -1;
	while (++i < len)
		str[i] = src[i];
	str[i] = 0;
	return (str);
}

int	main(__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv, __attribute__((unused))char **envp)
{	
	char	*prompt;
	t_slst	*list;
	t_slst	to_free;

	import_env(envp);
	pipi()->fd[0] = 0;
	pipi()->fd[1] = 1;
	pipi()->to_pipe = 0;
	//add_history("echo $PATH");
	//add_history("make && ./minishell");
	//add_history("echo salut | cat -e");
	printf("welcome to our minishell :)\n");
	while (1)
	{
		connect_signals();
		prompt = readline("$> ");
		if (!prompt)
			finish("No problemo\n", 0);
		if (prompt[0] != 0)
		{
			add_history(prompt);
			list = parser(prompt);
			to_free.first = list->first;
			exec_line(list);
			free_slist(&to_free);
			// Ici free la list
		}
		free(prompt);
	}
}
