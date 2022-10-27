/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:01:41 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/10/27 13:15:39 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_state(t_philosopher *philosopher, t_states new_state, int timestamp)
{
	philosopher->state = new_state;
	philosopher->started_state_at = timestamp;
	print_state(philosopher, timestamp);
}

int	done_sleeping(t_philosopher *philosopher, int timestamp)
{
	return (timestamp
		- philosopher->started_state_at >= philosopher->time_to_sleep);
}

int	has_both_forks(t_philosopher *philosopher)
{
	return (philosopher->holding_left_fork && philosopher->holding_right_fork);
}

void	update_state(t_philosopher *philosopher)
{
	int	timestamp;

	timestamp = get_timestamp();
	if (should_die(philosopher, timestamp))
		return (set_state(philosopher, DEAD, timestamp));
	if (is_thinking(philosopher) && has_both_forks(philosopher))
		return (set_state(philosopher, EATING, timestamp));
	if (is_eating(philosopher) && done_eating(philosopher, timestamp))
	{
		drop_left_fork(philosopher);
		drop_right_fork(philosopher);
		philosopher->meals_eaten++;
		return (set_state(philosopher, SLEEPING, timestamp));
	}
	if (is_sleeping(philosopher) && done_sleeping(philosopher, timestamp))
		return (set_state(philosopher, THINKING, timestamp));
	if (is_thinking(philosopher))
		return (pick_a_fork(philosopher));
	return ;
}
