/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:05:29 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/10/27 13:55:48 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(t_philosopher *philosopher, const char **argv, int nb)
{
	philosopher->id = nb;
	philosopher->state = THINKING;
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	philosopher->started_state_at = get_timestamp();
	philosopher->meals_eaten = 0;
	if (argv[5])
		philosopher->meals_goal = ft_atoi(argv[5]);
	else
		philosopher->meals_goal = INT_MAX;
}

void	create_fork(t_philosopher *philosopher)
{
	t_fork			*fork;

	fork = malloc(sizeof(t_fork));
	philosopher->right_fork = fork;
	pthread_mutex_init(&philosopher->right_fork->lock, NULL);
}

t_philosopher	**create_philosophers(const char **argv)
{
	t_philosopher	**philosophers;
	int				i;
	int				philosophers_count;

	philosophers_count = ft_atoi(argv[1]);
	philosophers = malloc(sizeof(t_philosopher *) * philosophers_count);
	i = 0;
	while (i < philosophers_count)
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		init_philosopher(philosophers[i], argv, i);
		create_fork(philosophers[i]);
		if (i >= 1)
			philosophers[i]->left_fork = philosophers[i - 1]->right_fork;
		i++;
	}
	philosophers[0]->left_fork = philosophers[i - 1]->right_fork;
	philosophers[i] = NULL;
	return (philosophers);
}
