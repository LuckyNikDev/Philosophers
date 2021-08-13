/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsailor <bsailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 22:35:42 by bsailor           #+#    #+#             */
/*   Updated: 2021/08/12 22:40:14 by bsailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_table
{
	int				have_dead;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_meals;
	long long		start_time;
	pthread_mutex_t	*print;
	int				i_m_full;
}					t_table;

typedef struct s_philo
{
	int				id;
	long long		deadline;
	int				number_of_meals;
	pthread_mutex_t	*left_m;
	pthread_mutex_t	*right_m;
	t_table			*table;
}					t_philo;

int			ft_init_philos(t_philo **philos, t_table *table);
void		ft_error_init(t_philo **philos, int i, t_table *table, int flag);
int			ft_table_init(t_table *table, int argc, char **argv);
int			ft_validation_number(char **argv);
int			ft_atoi(const char *str);
void		ft_init_philos_util_two(t_philo **philos, t_table *table);
int			ft_init_philos_util_one(t_philo **philos, t_table *table);
long long	ft_get_time(void);
void		*ft_philo_life(void *philo_arg);
void		ft_philo_life_util(t_philo *philo);
int			ft_start_thread(t_philo *philos, \
t_table *table, pthread_t *threads);
void		*ft_start_thread_check(void *philo_arg);
int			ft_strlen(const char *str);
void		ft_console_helper(char *message, \
t_philo *philo, char *id, int flag);
char		*ft_itoa(long n);
int			ft_numlen(long n);
char		*ft_strjoin(char *s1, char *s2, char *s3, char *s4);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		my_sleep(long long time);
void		ft_clear_properties(t_philo *philos, \
t_table *table, pthread_t *pthreads);
int			ft_malloc_thread(pthread_t	**threads, char **argv);

#endif