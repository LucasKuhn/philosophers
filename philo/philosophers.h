/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:16:10 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/09 14:34:25 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>  // pthread
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // sleep

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define USAGE_MSG "Usage: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				locked;
}					t_fork;

typedef struct s_philosopher
{
	int				id;
	_Atomic int		state;
	int				program_start_time;
	int				started_state_at;
	int				last_meal_at;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	_Atomic int		meals_eaten;
	int				meals_goal;
	int				holding_left_fork;
	int				holding_right_fork;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
}					t_philosopher;

typedef enum e_states
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}					t_states;

// state utils
int					is_thinking(t_philosopher *philosopher);
int					is_eating(t_philosopher *philosopher);
int					is_sleeping(t_philosopher *philosopher);
int					is_dead(t_philosopher *philosopher);

// libft
int					ft_atoi(const char *str);

// philo eat utils
int					is_satisfied(t_philosopher *philosopher);
int					should_die(t_philosopher *philosopher, int timestamp);
int					done_eating(t_philosopher *philosopher, int timestamp);

// main utils
t_philosopher		**create_philosophers(const char **argv);
void				simulate_philosophers(t_philosopher **philosophers);
int					invalid_args(int argc, char const *argv[]);

// philo state utils
int					is_thinking(t_philosopher *philosopher);
int					is_eating(t_philosopher *philosopher);
int					is_sleeping(t_philosopher *philosopher);
int					is_dead(t_philosopher *philosopher);
int					is_holding_a_fork(t_philosopher *philosopher);

// timestamp
int					get_timestamp(int program_start_time);

// update_state
void				update_state(t_philosopher *philosopher);
void				print_state(t_philosopher *philosopher, int timestamp);

// fork utils
void				drop_forks(t_philosopher *philosopher);
void				pick_a_fork(t_philosopher *philosopher);

#endif
