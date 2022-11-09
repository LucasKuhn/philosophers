/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:05:29 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/09 15:08:20 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(t_philosopher *philosopher, const char **argv, int nb)
{
	philosopher->id = nb;
	philosopher->state = THINKING;
	if (philosopher->id % 2 != 0)
			philosopher->state = SLEEPING;
	philosopher->holding_left_fork = 0;
	philosopher->holding_right_fork = 0;
	philosopher->started_state_at = 0;
	philosopher->last_meal_at = 0;
	philosopher->meals_eaten = 0;
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philosopher->meals_goal = ft_atoi(argv[5]);
	else
		philosopher->meals_goal = INT_MAX;
}

void	create_fork(t_philosopher *philosopher)
{
	t_fork			*fork;

	fork = malloc(sizeof(t_fork));
	fork->locked = FALSE;
	philosopher->right_fork = fork;
	pthread_mutex_init(&philosopher->right_fork->lock, NULL);
}

t_philosopher	**create_philosophers(const char **argv)
{
	t_philosopher	**philosophers;
	int				i;
	int				philosophers_count;

	philosophers_count = ft_atoi(argv[1]);
	philosophers = malloc(sizeof(t_philosopher *) * (philosophers_count + 1));
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
