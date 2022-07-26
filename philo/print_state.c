/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:54:45 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/10 23:35:07 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*readable_state(t_philosopher *philosopher)
{
	if (is_dead(philosopher))
		return ("died");
	if (is_eating(philosopher))
		return ("is eating");
	if (is_holding_a_fork(philosopher))
		return ("has taken a fork");
	if (is_thinking(philosopher))
		return ("is thinking");
	if (is_sleeping(philosopher))
		return ("is sleeping");
	else
		return ("UNKNOWN");
}

void	print_state(t_philosopher *philosopher, int timestamp)
{
	char	*state;

	state = readable_state(philosopher);
	pthread_mutex_lock(philosopher->print_lock);
	printf("%d %d %s\n", timestamp, philosopher->id, state);
	pthread_mutex_unlock(philosopher->print_lock);
}
