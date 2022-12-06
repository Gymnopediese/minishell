/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:45 by albaud            #+#    #+#             */
/*   Updated: 2022/12/06 14:43:48 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "koflibc/sources.h"
# include <signal.h>
# include <termios.h>

enum
{
	EXECUTABLE,
	BUILDIN,
	VARIABLE,
};

typedef struct s_exec
{
	int		type;
	char	*exec;
	t_list	*flags;
	t_list	*str;
}	t_exec;

typedef struct s_buff
{
	char	b[10001];
	int		i;
}	t_buff;

typedef struct s_var
{
	const char	*name;
	char		*data;
}	t_var;

typedef struct s_vlink
{
	t_var			content;
	struct s_vlink	*next;
}	t_vlink;

typedef struct s_slink
{
	char			*content;
	struct s_slink	*next;
}	t_slink;

typedef struct s_slst
{
	t_slink	*first;
	t_slink	*last;
	int		size;
}	t_slst;

// parser.c
t_slst		*parser(char *prompt);
// vars.c
char		*vars(const char *name, char *data);
// vars_list.c
t_vlink		*vlst_new(t_var content);
void		vlst_add_front(t_vlink **lst, t_var var);
// string_list.c
t_slink		*slst_new(char *str);
void		slst_add_back(t_slst *lst, char *str);
void		slst_add_front(t_slst *lst, char *str);

void		handle_buffer(t_buff *buffer, char *res);
void		handle_double_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_simple_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_var(char *prompt, int *index, t_buff *buffer, char *res);

void		connect_signals(void);
void		declare_variable(char *declaration);
#endif