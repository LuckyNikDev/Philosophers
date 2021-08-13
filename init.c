/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsailor <bsailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:37:02 by bsailor           #+#    #+#             */
/*   Updated: 2021/08/12 23:06:28 by bsailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_validation_number(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_table_init(t_table *table, int argc, char **argv)
{
	table->number_of_philo = ft_atoi(argv[1]);
	table->i_m_full = 0;
	table->have_dead = 0;
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->print = malloc(sizeof(pthread_mutex_t));
	if (!(table->print) || pthread_mutex_init(table->print, NULL))
		return (1);
	if (argc == 6)
		table->number_of_time_meals = ft_atoi(argv[5]);
	else
		table->number_of_time_meals = -1;
	return (0);
}

int	ft_malloc_thread(pthread_t	**threads, char **argv)
{
	*threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (!threads)
		return (1);
	return (0);
}
