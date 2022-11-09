/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:20:21 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/09 15:10:38 by lalex-ku         ###   ########.fr       */
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
		usleep(1000);
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
	simulate_philosophers(philosophers);
	simulation_loop(philosophers);
}
