/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_philosophers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:43:10 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/10/27 13:55:25 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_loop(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	print_state(philosopher, get_timestamp());
	if (philosopher->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		update_state(philosopher);
		usleep(1000);
	}
	return (NULL);
}

void	simulate_philosophers(t_philosopher **philosophers)
{
	int	i;

	i = 0;
	while (philosophers[i])
	{
		pthread_create(&philosophers[i]->thread, NULL, philosopher_loop,
			philosophers[i]);
		pthread_detach(philosophers[i]->thread);
		i++;
	}
}
