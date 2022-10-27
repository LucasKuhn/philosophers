/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:47:57 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/10/27 13:15:39 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_satisfied(t_philosopher *philosopher)
{
	return (philosopher->meals_eaten >= philosopher->meals_goal);
}

int	should_die(t_philosopher *philosopher, int timestamp)
{
	return (timestamp
		- philosopher->started_state_at >= philosopher->time_to_die);
}

int	done_eating(t_philosopher *philosopher, int timestamp)
{
	return (timestamp
		- philosopher->started_state_at >= philosopher->time_to_eat);
}
