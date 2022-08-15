/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:20:21 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/08/12 18:36:09 by lalex-ku         ###   ########.fr       */
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
	struct timeval		tv;
	long long			timestamp;
	static long long	start_time;

	gettimeofday(&tv, NULL);
	if (!start_time)
		start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp - start_time);
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
		return ("has taken a fork   🍴😬");
	if (has_right_fork(philosopher))
		return ("has taken a fork     😬🍴");
	if (is_thinking(philosopher))
		return ("is thinking          🤔");
	if (is_sleeping(philosopher))
		return ("is sleeping          😴");
	else
		return ("UNKNOWN");
}

// char *readable_state(t_philosopher *philosopher)
// {
// 	if (is_dead(philosopher))
// 		return ("died");
// 	if (is_eating(philosopher))
// 		return ("is eating");
// 	if (has_left_fork(philosopher))
// 		return ("has taken a fork");
// 	if (has_right_fork(philosopher))
// 		return ("has taken a fork");
// 	if (is_thinking(philosopher))
// 		return ("is thinking");
// 	if (is_sleeping(philosopher))
// 		return ("is sleeping");
// 	else
// 		return ("UNKNOWN");
// }


void	*display_log(void *arg)
{
	t_philosopher	**philosophers = (t_philosopher **)arg;
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
				printf("%lld %d %s\v\r", timestamp,
					philosophers[i]->id, 
					readable_state(philosophers[i]));
				// if (philosophers[i]->holding_left_fork)
				// 	printf("Holding left  fork: %p\v\r", philosophers[i]->left_fork);
				// if (philosophers[i]->holding_right_fork)
				// 	printf("Holding right fork: %p\v\r", philosophers[i]->right_fork);
			if (is_dead(philosophers[i]))
				nobody_died = FALSE;
			i++;
		}
		fflush(stdout);
		usleep(1000 * 10);
	}
	return (NULL);
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

	philosopher->id = i;
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

void drop_left_fork(t_philosopher	*philosopher)
{
	pthread_mutex_lock(&philosopher->left_fork->lock);
	philosopher->holding_left_fork = FALSE;
	philosopher->left_fork->locked = FALSE;
	pthread_mutex_unlock(&philosopher->left_fork->lock);
}

void drop_right_fork(t_philosopher	*philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork->lock);
	philosopher->holding_right_fork = FALSE;
	philosopher->right_fork->locked = FALSE;
	pthread_mutex_unlock(&philosopher->right_fork->lock);
}

void try_left_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork->lock);
	if (philosopher->left_fork->locked == FALSE)
		philosopher->holding_left_fork = TRUE;
		philosopher->left_fork->locked = TRUE;
	pthread_mutex_unlock(&philosopher->right_fork->lock);
}

void try_right_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->left_fork->lock);
	if (philosopher->right_fork->locked == FALSE)
		philosopher->holding_right_fork = TRUE;
		philosopher->right_fork->locked = TRUE;
	pthread_mutex_unlock(&philosopher->left_fork->lock);
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
	if (philosopher->started_eating_at + philosopher->time_to_die < timestamp )
	{
		philosopher->state = DEAD;
		return ;
	}
	if (is_eating(philosopher))
	{
		if (philosopher->started_eating_at + philosopher->time_to_eat < timestamp)
		{
			drop_left_fork(philosopher);
			drop_right_fork(philosopher);
			philosopher->meals_eaten++;
			philosopher->started_sleeping_at = get_timestamp();
			philosopher->state = SLEEPING;
		}
	}
	else if (has_both_forks(philosopher))
	{
		philosopher->state = EATING;
		philosopher->started_eating_at = timestamp;
	}	
	else if (is_thinking(philosopher))
	{
		if (philosopher->id % 2 == 0)
		{
			if (has_left_fork(philosopher))
				try_right_fork(philosopher);
			else
				try_left_fork(philosopher);	
		}
		else
		{
			if (has_right_fork(philosopher))
				try_left_fork(philosopher);	
			else
				try_right_fork(philosopher);
		}
	}
	else if (is_sleeping(philosopher))
	{
		if (philosopher->started_sleeping_at + philosopher->time_to_sleep < timestamp)
			philosopher->state = THINKING;
	}
}

void check_simulation(t_philosopher	**philosophers)
{
	int nobody_died = TRUE;
	int goal_reached = FALSE;
	int philosophers_satisfied = 0;
	int i;

	while (nobody_died && goal_reached == FALSE)
	{
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

void *simulate_philosopher(void *arg)
{
	t_philosopher	*philosopher = (t_philosopher *)arg;
	
	while (1)
	{
		update_state(philosopher);
		usleep(1000);
	}
	return (NULL);
}

void start_simulation(t_philosopher	**philosophers)
{
	int i;

	i = 0;
	while (philosophers[i])
	{
		pthread_create(&philosophers[i]->thread, NULL, simulate_philosopher, philosophers[i]);
		pthread_detach(philosophers[i]->thread);
		i++;
	}
}

int	main(int argc, char const *argv[])
{
	t_philosopher	**philosophers;

	if (argc == 1)
		return (1);
	philosophers = init_philosophers(argv);
	pthread_t display_thread; 
	pthread_create(&display_thread, NULL, display_log, philosophers);
	start_simulation(philosophers);
	pthread_join(display_thread, NULL);
}

// 4 3000 200 300 8
// cc main.c -Wall -Wextra -Werror && ./a.out 5 410 200 200 8
