/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:01:41 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/10 15:41:54 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_state(t_philosopher *philosopher, t_states new_state,
	int timestamp)
{
	set_state(philosopher, new_state, timestamp);
	print_state(philosopher, timestamp);
}

int	done_sleeping(t_philosopher *philosopher, int timestamp)
{
	return (timestamp
		- philosopher->started_state_at >= philosopher->time_to_sleep);
}

void	check_state_change(t_philosopher *philosopher)
{
	int	timestamp;

	timestamp = get_timestamp(philosopher->program_start_time);
	if (should_die(philosopher, timestamp))
		return (update_state(philosopher, DEAD, timestamp));
	if (is_thinking(philosopher) && has_both_forks(philosopher))
		return (update_state(philosopher, EATING, timestamp));
	if (is_eating(philosopher) && done_eating(philosopher, timestamp))
	{
		drop_forks(philosopher);
		return (update_state(philosopher, SLEEPING, timestamp));
	}
	if (is_sleeping(philosopher) && done_sleeping(philosopher, timestamp))
		return (update_state(philosopher, THINKING, timestamp));
	if (is_thinking(philosopher))
		return (pick_a_fork(philosopher));
	return ;
}
