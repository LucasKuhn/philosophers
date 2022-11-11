/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_philosophers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:43:10 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/10 23:34:14 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	should_simulate(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->state_lock);
	if (philosopher->state == DEAD || philosopher->state == SIMULATION_OVER)
	{
		pthread_mutex_unlock(&philosopher->state_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&philosopher->state_lock);
	if (is_satisfied(philosopher))
		return (FALSE);
	return (TRUE);
}

void	*philosopher_loop(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	print_state(philosopher, get_timestamp(philosopher->program_start_time));
	usleep(philosopher->id * 250);
	while (should_simulate(philosopher))
	{
		check_state_change(philosopher);
		usleep(150);
	}
	return (NULL);
}

void	set_start_time(t_philosopher **philosophers)
{
	int				i;
	int				program_start_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	program_start_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	i = 0;
	while (philosophers[i])
	{
		philosophers[i]->program_start_time = program_start_time;
		i++;
	}
}

void	simulate_philosophers(t_philosopher **philosophers)
{
	int	i;

	set_start_time(philosophers);
	i = 0;
	while (philosophers[i])
	{
		pthread_create(&philosophers[i]->thread, NULL, philosopher_loop,
			philosophers[i]);
		i++;
	}
	i = 0;
}
