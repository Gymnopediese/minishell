/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 13:25:09 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	void_signal(int sig)
{
	(void) sig;
	ft_putstr("\b\b  \b\b");
	rl_redisplay();
}

void	new_line_signal(int sig)
{
	(void) sig;
	printf("\b\b  \b\b\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	connect_signals(void)
{
	signal(SIGINT, new_line_signal);
	signal(SIGQUIT, void_signal);
}
