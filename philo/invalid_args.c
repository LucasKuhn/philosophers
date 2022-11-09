/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:08:55 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/09 14:04:00 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_numeric(const char *str)
{
	while (*str)
	{
		if (*str != '-' && (*str < '0' || *str > '9'))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	invalid_args(int argc, char const *argv[])
{
	int	i;

	if (argc < 4)
		return (TRUE);
	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]) || ft_atoi(argv[i]) == 0)
		{
			printf("Invalid argument: %s\n", argv[i]);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
