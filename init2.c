/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsailor <bsailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:37:06 by bsailor           #+#    #+#             */
/*   Updated: 2021/08/12 20:13:15 by bsailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_philos(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	if (ft_init_philos_util_one(philos, table))
		return (1);
	while (i < table->number_of_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].number_of_meals = 0;
		(*philos)[i].table = table;
		if (pthread_mutex_init((*philos)[i].right_m, NULL))
		{
			ft_error_init(philos, i, table, 1);
			return (1);
		}
		i++;
	}
	ft_init_philos_util_two(philos, table);
	return (0);
}

int	ft_init_philos_util_one(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	*philos = (t_philo *) malloc(sizeof(t_philo) * table->number_of_philo);
	if (!(*philos))
	{
		pthread_mutex_destroy(table->print);
		free(table->print);
		return (1);
	}
	while (i < table->number_of_philo)
	{
		(*philos)[i].right_m = malloc(sizeof(pthread_mutex_t));
		if (!((*philos)[i].right_m))
		{
			ft_error_init(philos, i, table, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_init_philos_util_two(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	if (table->number_of_philo == 1)
	{
		(*philos)[i].left_m = (*philos)[i].right_m;
		return ;
	}
	while (i < table->number_of_philo)
	{
		if (i < table->number_of_philo - 1)
			(*philos)[i].left_m = (*philos)[i + 1].right_m;
		else
			(*philos)[i].left_m = (*philos)[0].right_m;
		i++;
	}
}

void	ft_error_init(t_philo **philos, int i, t_table *table, int flag)
{
	pthread_mutex_destroy(table->print);
	free(table->print);
	if (flag)
	{
		while (--i >= 0)
			pthread_mutex_destroy((*philos)[i].right_m);
		i = 0;
		while (i < table->number_of_philo)
		{
			free((*philos)[i].right_m);
			i++;
		}
	}
	else
	{
		while (--i >= 0)
		{
			free((*philos)[i].right_m);
			i++;
		}
	}
	free(philos);
}
