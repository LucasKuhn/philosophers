/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:20:21 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/08/11 15:33:25 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philophers.h"


int	is_thinking(t_philosopher *philosopher)
{
	return (philosopher->state == THINKING);
}

int	is_eating(t_philosopher *philosopher)
{
	return (philosopher->state == EATING);
}

int	is_sleeping(t_philosopher *philosopher)
{
	return (philosopher->state == SLEEPING);
}

int	is_dead(t_philosopher *philosopher)
{
	return (philosopher->state == DEAD);
}

// https://stackoverflow.com/questions/3756323/how-to-get-the-current-time-in-milliseconds-from-c-in-linux
long long	get_timestamp(void)
{
	struct timeval	tv;
	long long		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}

int has_left_fork(t_philosopher *philosopher)
{
	return (philosopher->holding_left_fork);
}

int has_right_fork(t_philosopher *philosopher)
{
	return (philosopher->holding_right_fork);
}

char *readable_state(t_philosopher *philosopher)
{
	if (is_dead(philosopher))
		return ("died                 ☠️");
	if (is_eating(philosopher))
		return ("is eating          🍴😋🍴");
	if (has_left_fork(philosopher))
		return (" has taken a fork  🍴😬");
	if (has_right_fork(philosopher))
		return (" has taken a fork    😬🍴");
	if (is_thinking(philosopher))
		return ("is thinking          🤔");
	if (is_sleeping(philosopher))
		return ("is sleeping          😴");
	else
		return ("UNKNOWN");
}

static void	display_log(t_philosopher **philosophers)
{
	long long	timestamp;
	int			i;
	int nobody_died = TRUE;


	while (nobody_died)
	{
		i = 0;
		printf("\e[1;1H\e[2J");
		printf("               🍝 Dinner time! 🍝 \v\r");
		printf("------------------------------------------------- \v\r");
		while (philosophers[i])
		{
			timestamp = get_timestamp();
			printf("%lld %15s %s\v\r", timestamp,
					philosophers[i]->name, 
					readable_state(philosophers[i]));
			if (is_dead(philosophers[i]))
				nobody_died = FALSE;
			i++;
		}
		fflush(stdout);
		usleep(1000 * 100);
	}
}

void	init_philosopher(t_philosopher *philosopher, const char **argv)
{
	philosopher->state = THINKING;
	philosopher->time_to_die = atoi(argv[2]);
	philosopher->time_to_eat = atoi(argv[3]);
	philosopher->time_to_sleep = atoi(argv[4]);
	philosopher->started_eating_at = get_timestamp();
	philosopher->meals_eaten = 0;
	if (argv[5])
		philosopher->meals_goal = atoi(argv[5]);
	else
		philosopher->meals_goal = 999;
}

void	name_philosopher(t_philosopher *philosopher, int i)
{
	const char	*names[22];

	i = i % 22;
	names[0] = "Plato";
	names[1] = "Aristotle";
	names[2] = "Pythagoras";
	names[3] = "Heraclitus";
	names[4] = "Parmenides";
	names[5] = "Democritus";
	names[6] = "Zeno of Elea";
	names[7] = "Epicurus";
	names[8] = "Anaxagoras";
	names[9] = "Diogenes";
	names[10] = "Antisthenes";
	names[11] = "Gorgias";
	names[12] = "Hippocrates";
	names[13] = "Plutarch";
	names[14] = "Proclus";
	names[15] = "Chrysippus";
	names[16] = "Solon";
	names[17] = "Archimedes";
	names[18] = "Thucydides";
	names[19] = "Arcesilaus";
	names[20] = "Posidonius";
	names[21] = "Galen";
	philosopher->name = strdup(names[i]);
}

t_philosopher	**init_philosophers(const char **argv)
{
	t_philosopher	**philosophers;
	int				i;

	philosophers = malloc(sizeof(t_philosopher *) * atoi(argv[1]));
	i = 0;
	while (i < atoi(argv[1]))
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		init_philosopher(philosophers[i], argv);
		name_philosopher(philosophers[i], i);
		t_fork *fork;
		fork = malloc(sizeof(t_fork));
		philosophers[i]->right_fork = fork;
		pthread_mutex_init(&philosophers[i]->right_fork->lock, NULL);
		if ( i >= 1 )
			philosophers[i]->left_fork = philosophers[i - 1]->right_fork;
		i++;
	}
	philosophers[0]->left_fork = philosophers[i-1]->right_fork;
	philosophers[i] = NULL;
	return (philosophers);
}

void grab_left_fork(t_philosopher	*philosopher)
{
	pthread_mutex_lock(&philosopher->left_fork->lock);
	philosopher->left_fork->locked = TRUE;
	philosopher->holding_left_fork = TRUE;
	pthread_mutex_unlock(&philosopher->left_fork->lock);
}

void grab_right_fork(t_philosopher	*philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork->lock);
	philosopher->right_fork->locked = TRUE;
	philosopher->holding_right_fork = TRUE;
	pthread_mutex_unlock(&philosopher->right_fork->lock);
}

int has_both_forks(t_philosopher	*philosopher)
{
	return (philosopher->holding_left_fork && philosopher->holding_right_fork);
}

int is_satisfied(t_philosopher *philosopher)
{
	return (philosopher->meals_eaten >= philosopher->meals_goal);
}

void update_state(t_philosopher	*philosopher)
{
	long long timestamp;
	
	timestamp = get_timestamp();
	if (is_eating(philosopher))
	{
		if (philosopher->started_eating_at + philosopher->time_to_eat < timestamp)
		{
			philosopher->meals_eaten++;
			philosopher->state = SLEEPING;
		}
	}
	else if (philosopher->started_eating_at + philosopher->time_to_die < timestamp )
	{
		philosopher->state = DEAD;
	}
	else if (is_sleeping(philosopher))
	{
		if (philosopher->started_sleeping_at + philosopher->time_to_sleep < timestamp)
			philosopher->state = THINKING;
	}
	else if (is_thinking(philosopher))
	{
		if (philosopher->left_fork->locked == FALSE)
			grab_left_fork(philosopher);
		else if (philosopher->right_fork->locked == FALSE)
			grab_right_fork(philosopher);
		else if (has_both_forks(philosopher))
		{
			philosopher->state = EATING;
			philosopher->started_eating_at = timestamp;
		}
	}
}

void *run_simulation(void *arg)
{
	
	t_philosopher	**philosophers = (t_philosopher **)arg;
	int nobody_died = TRUE;
	int goal_reached = FALSE;
	int philosophers_satisfied = 0;
	int i;
	
	while (nobody_died && goal_reached == FALSE)
	{
		i = 0;
		while (philosophers[i])
		{
			update_state(philosophers[i]);
			if (is_dead(philosophers[i]))
				nobody_died = FALSE;
			if (is_satisfied(philosophers[i]))
				philosophers_satisfied++;
			i++;
		}
		if (philosophers_satisfied == i)
			goal_reached = TRUE;
		usleep(1000 * 100);
	}
	return (NULL);
}

int	main(int argc, char const *argv[])
{
	t_philosopher	**philosophers;

	if (argc == 1)
		return (1);
	philosophers = init_philosophers(argv);
	pthread_t simulation_thread; 
	pthread_create(&simulation_thread, NULL, run_simulation, philosophers);
	display_log(philosophers);
}
