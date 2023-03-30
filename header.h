/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:57:53 by bphilago          #+#    #+#             */
/*   Updated: 2023/03/28 14:42:37 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "koflibc/sources.h"
# include <signal.h>
# include <termios.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>

// Pour Vars
# define VARS_PRINT 0
# define VARS_GET 1
# define VARS_ADD 2
# define VARS_FREE 3
# define VARS_DEL 4

enum
{
	TEXT,
	PIPE,
	LEFT,
	LLEFT,
	RIGHT,
	RRIGHT,
	OR,
	AND,
	PLEFT,
	PRIGHT,
};

typedef struct s_buff
{
	char	b[10001];
	int		i;
}	t_buff;

typedef struct s_var
{
	char		*name;
	char		*data;
	char		export;
}	t_var;

typedef struct s_pipe
{
	int	fd[2];
	int	to_pipe;
}	t_pipe;

typedef struct s_vlink
{
	t_var			content;
	struct s_vlink	*next;
}	t_vlink;

typedef struct s_slink
{
	char			*content;
	struct s_slink	*next;
	int				type;//todo: enum
	int				level;
}	t_slink;

typedef struct s_slst
{
	t_slink	*first;
	t_slink	*last;
	int		size;
}	t_slst;

// char	**args;
// t_slst	*right;
// t_slst	*rright;
// int		end;
// int		read;
typedef struct s_args
{
	char	**args;
	t_slst	*right;
	t_slst	*rright;
	int		end;
	int		read;
}	t_args;

# include "builtins/builtins.h"

void		rl_replace_line(const char *text, int clear_undo);
// parser.c
int			is_symbole(char c);
t_slst		*parser(char *prompt);
// vars.c
t_vlink		**get_vars(void);
char		*get_vars_value(const char *name);
void		add_vars(const char *name, char *data, char export);
void		free_vars(void);
void		del_vars(const char *name);
//export_manager
void		print_vars(char export);
void		declare_variable(char *declaration, char export);
void		import_env(char **env);
char		**export_env(void);
// vars_list.c
t_vlink		*vlst_new(t_var content);
void		vlst_add_front(t_vlink **lst, t_var var);
// string_list.c
void		slst_add_front(t_slst *lst, char *str, int type, int level);
void		slst_add_back(t_slst *lst, char *str, int type, int level);
void		handle_buffer(t_buff *buffer, char *res);
void		handle_double_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_simple_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_var(char *prompt, int *index, t_buff *buffer, char *res);
void		handle_vague(t_buff *buffer, char *res);
void		put_slst(t_slst *lst);
t_args		*slst_to_tab(t_slst *args);
void		connect_signals(void);
//parse_error
void		parse_error(char a, char b);
void		finish(char *message);
//builtins
int			execute(t_args *args);
int			filename_injection(t_args *args, int read_fd);
int			fd_injection(char *filename, int fd);
int			fd_fd_injection(int dst, int src);
int			wildcards(char *arg, t_slst *res);
int			mode(int m);
int			level(int m);
t_pipe		*pipi(void);
int			is_the_end(t_slink *link);
void		put_pipi(void);
int			is_redirection(t_slink *link);

#endif