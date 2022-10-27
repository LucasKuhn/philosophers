/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:54:05 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/10/27 13:18:13 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_timestamp(void)
{
	struct timeval	tv;
	int				timestamp;
	static int		start_time;

	gettimeofday(&tv, NULL);
	if (!start_time)
		start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp - start_time);
}
