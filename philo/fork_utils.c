/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:00:18 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/10/27 13:15:39 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	drop_left_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->left_fork->lock);
	philosopher->left_fork->locked = FALSE;
	pthread_mutex_unlock(&philosopher->left_fork->lock);
	philosopher->holding_left_fork = FALSE;
}

void	drop_right_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork->lock);
	philosopher->right_fork->locked = FALSE;
	pthread_mutex_unlock(&philosopher->right_fork->lock);
	philosopher->holding_right_fork = FALSE;
}
