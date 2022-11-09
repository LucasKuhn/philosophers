/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_a_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:52:33 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/09 14:56:23 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	try_right_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork->lock);
	if (philosopher->right_fork->locked == FALSE)
	{
		philosopher->right_fork->locked = TRUE;
		philosopher->holding_right_fork = TRUE;
	}
	pthread_mutex_unlock(&philosopher->right_fork->lock);
}

void	try_left_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->left_fork->lock);
	if (philosopher->left_fork->locked == FALSE)
	{
		philosopher->left_fork->locked = TRUE;
		philosopher->holding_left_fork = TRUE;
	}
	pthread_mutex_unlock(&philosopher->left_fork->lock);
}

void	pick_a_fork(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		try_right_fork(philosopher);
		usleep(200);
		try_left_fork(philosopher);
	}
	else
	{
		try_left_fork(philosopher);
		usleep(200);
		try_right_fork(philosopher);
	}
}
