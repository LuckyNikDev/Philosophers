/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsailor <bsailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 22:05:10 by bsailor           #+#    #+#             */
/*   Updated: 2021/08/12 23:25:27 by bsailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;
	pthread_t	*threads;

	if (argc < 5 || argc > 6 || ft_validation_number(&argv[1]) \
	|| argv[1][0] == '0' || ft_malloc_thread(&threads, argv) || \
	ft_table_init(&table, argc, argv) || ft_init_philos(&philos, &table))
		return (1);
	ft_start_thread(philos, &table, threads);
	return (0);
}

int	ft_start_thread(t_philo *philos, t_table *table, pthread_t *threads)
{
	pthread_t	thread_check;
	int			i;

	table->start_time = ft_get_time();
	i = 0;
	while (i < table->number_of_philo)
	{
		philos[i].deadline = table->start_time + table->time_to_die;
		if (pthread_create(&threads[i], \
		NULL, ft_philo_life, (void *)&philos[i]))
			break ;
		pthread_detach(threads[i]);
		i++;
	}
	pthread_create(&thread_check, NULL, ft_start_thread_check, (void *)philos);
	pthread_join(thread_check, NULL);
	ft_clear_properties(philos, table, threads);
	return (0);
}

void	*ft_start_thread_check(void *philo_arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		i = 0;
		while (i < philo[0].table->number_of_philo)
		{
			if (philo[0].table->number_of_philo == philo[0].table->i_m_full)
			{
				philo->table->have_dead = 1;
				pthread_mutex_lock(philo[0].table->print);
				return (NULL);
			}
			if (philo[i].deadline < ft_get_time())
			{
				philo[0].table->have_dead = 1;
				ft_console_helper(" died\n", &philo[i], ft_itoa(philo[i].id), 0);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	*ft_philo_life(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (!(philo->table->have_dead))
	{
		ft_philo_life_util(philo);
		(philo->number_of_meals)++;
		if (philo->number_of_meals == philo->table->number_of_time_meals)
		{
			(philo->table->i_m_full)++;
			return (NULL);
		}
		ft_console_helper(" is sleeping\n", philo, ft_itoa(philo->id), 1);
		my_sleep(philo->table->time_to_sleep);
		ft_console_helper(" is thinking\n", philo, ft_itoa(philo->id), 1);
	}
	return (NULL);
}

void	ft_philo_life_util(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_m);
		ft_console_helper(" has taken a fork\n", philo, ft_itoa(philo->id), 1);
		pthread_mutex_lock(philo->right_m);
	}
	else
	{
		pthread_mutex_lock(philo->right_m);
		ft_console_helper(" has taken a fork\n", philo, ft_itoa(philo->id), 1);
		pthread_mutex_lock(philo->left_m);
	}
	philo->deadline = ft_get_time() + philo->table->time_to_die;
	ft_console_helper(" is eating\n", philo, ft_itoa(philo->id), 1);
	my_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_m);
	pthread_mutex_unlock(philo->right_m);
}
