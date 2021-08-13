/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsailor <bsailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:29:34 by bsailor           #+#    #+#             */
/*   Updated: 2021/08/12 22:44:43 by bsailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	negative;

	negative = 0;
	result = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (negative)
		result *= -1;
	return (result);
}

void	my_sleep(long long time)
{
	long long	check_time;

	check_time = ft_get_time() + time;
	while (ft_get_time() < check_time)
		usleep(100);
}

void	ft_console_helper(char *message, t_philo *philo, char *id, int flag)
{
	char	*str;
	char	*time;

	time = ft_itoa(ft_get_time() - philo->table->start_time);
	str = ft_strjoin(time, " ", id, message);
	pthread_mutex_lock(philo->table->print);
	write(1, str, ft_strlen(str));
	free(str);
	if (flag)
		pthread_mutex_unlock(philo->table->print);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_clear_properties(t_philo *philos, \
t_table *table, pthread_t *pthreads)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(table->print);
	free(table->print);
	while (i < table->number_of_philo)
	{
		pthread_mutex_destroy(philos[i].right_m);
		free(philos[i].right_m);
		i++;
	}
	free(pthreads);
	free(philos);
}
