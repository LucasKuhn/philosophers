/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:29 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/10 15:41:45 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_state(t_philosopher *philosopher, t_states new_state, int timestamp)
{
	pthread_mutex_lock(&philosopher->state_lock);
	philosopher->state = new_state;
	pthread_mutex_unlock(&philosopher->state_lock);
	philosopher->started_state_at = timestamp;
	if (new_state == EATING)
		philosopher->last_meal_at = timestamp;
	if (new_state == SLEEPING)
	{
		pthread_mutex_lock(&philosopher->meals_eaten_lock);
		philosopher->meals_eaten++;
		pthread_mutex_unlock(&philosopher->meals_eaten_lock);
	}
}

int	is_thinking(t_philosopher *philosopher)
{
	int	result;

	pthread_mutex_lock(&philosopher->state_lock);
	result = philosopher->state == THINKING;
	pthread_mutex_unlock(&philosopher->state_lock);
	return (result);
}

int	is_eating(t_philosopher *philosopher)
{
	int	result;

	pthread_mutex_lock(&philosopher->state_lock);
	result = philosopher->state == EATING;
	pthread_mutex_unlock(&philosopher->state_lock);
	return (result);
}

int	is_sleeping(t_philosopher *philosopher)
{
	int	result;

	pthread_mutex_lock(&philosopher->state_lock);
	result = philosopher->state == SLEEPING;
	pthread_mutex_unlock(&philosopher->state_lock);
	return (result);
}

int	is_dead(t_philosopher *philosopher)
{
	int	result;

	pthread_mutex_lock(&philosopher->state_lock);
	result = philosopher->state == DEAD;
	pthread_mutex_unlock(&philosopher->state_lock);
	return (result);
}
