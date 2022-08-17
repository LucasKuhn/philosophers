/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philophers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:36:32 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/08/17 16:27:23 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>    // printf
#include <stdlib.h>   // malloc
#include <string.h>   // strdup ## TODO: remove
#include <sys/time.h> // gettimeofday
#include <unistd.h>   // sleep
#include <pthread.h> // pthread

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int	locked;
}					t_fork;

typedef struct s_philosopher
{
	char			*name;
	int				id;
	int				state;
	int				started_state_at;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_eaten;
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
int	is_thinking(t_philosopher *philosopher);
int	is_eating(t_philosopher *philosopher);
int	is_sleeping(t_philosopher *philosopher);
int	is_dead(t_philosopher *philosopher);
