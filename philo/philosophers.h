/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:16:10 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/10 23:29:20 by lalex-ku         ###   ########.fr       */
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
	int				state;
	pthread_mutex_t	state_lock;
	int				program_start_time;
	int				started_state_at;
	int				last_meal_at;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_lock;
	int				meals_goal;
	int				holding_left_fork;
	int				holding_right_fork;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	pthread_mutex_t	*print_lock;
}					t_philosopher;

typedef enum e_states
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	SIMULATION_OVER
}					t_states;

// state utils
void				set_state(t_philosopher *philosopher, t_states new_state,
						int timestamp);
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
void				check_state_change(t_philosopher *philosopher);
void				print_state(t_philosopher *philosopher, int timestamp);

// fork utils
void				drop_forks(t_philosopher *philosopher);
void				pick_a_fork(t_philosopher *philosopher);
int					has_both_forks(t_philosopher *philosopher);

#endif
