/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/09 11:32:00 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	void_signal(int sig)
{
	(void) sig;
}

void	new_line_signal(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);//wtf
	rl_redisplay();
}

void	connect_signals(void)
{
	signal(SIGINT, new_line_signal);
	signal(SIGQUIT, void_signal);
}
