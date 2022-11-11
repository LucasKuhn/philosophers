/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:20:21 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/11 19:06:12 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	simulation_loop(t_philosopher **philosophers)
{
	int	nobody_died;
	int	goal_reached;
	int	philosophers_satisfied;
	int	i;

	nobody_died = TRUE;
	goal_reached = FALSE;
	while (nobody_died && goal_reached == FALSE)
	{
		usleep(1000);
		philosophers_satisfied = 0;
		i = 0;
		while (philosophers[i])
		{
			if (is_dead(philosophers[i]))
				nobody_died = FALSE;
			if (is_satisfied(philosophers[i]))
				philosophers_satisfied++;
			i++;
		}
		if (philosophers_satisfied == i)
			goal_reached = TRUE;
	}
}

void	end_simulation(t_philosopher **philosophers)
{
	int	i;

	i = 0;
	while (philosophers[i])
	{
		pthread_mutex_lock(&philosophers[i]->state_lock);
		philosophers[i]->state = SIMULATION_OVER;
		pthread_mutex_unlock(&philosophers[i]->state_lock);
		pthread_join(philosophers[i]->thread, NULL);
		i++;
	}
	i = 0;
	free(philosophers[i]->print_lock);
	while (philosophers[i])
	{
		free(philosophers[i]->right_fork);
		free(philosophers[i]);
		i++;
	}
	free(philosophers);
}

void	add_print_lock(t_philosopher **philosophers)
{
	int				i;
	pthread_mutex_t	*print_lock;

	print_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print_lock, NULL);
	i = 0;
	while (philosophers[i])
	{
		philosophers[i]->print_lock = print_lock;
		i++;
	}
}

int	main(int argc, char const *argv[])
{
	t_philosopher	**philosophers;

	if (invalid_args(argc, argv))
	{
		printf(USAGE_MSG);
		return (1);
	}
	philosophers = create_philosophers(argv);
	add_print_lock(philosophers);
	simulate_philosophers(philosophers);
	simulation_loop(philosophers);
	end_simulation(philosophers);
}
