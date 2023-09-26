/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 16:48:05 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo {
	int				n_phi;
	int				n_meals;
	long long		tlast_meal;
	long long		tlast_sleep;
	pthread_t		thread;
	pthread_mutex_t	mut_n_meals;
	pthread_mutex_t	mut_t_lastmeal;
	struct s_data	*data_in;
}	t_philo;

typedef struct s_data {
	int				num_philos;
	int				dead_time;
	int				eat_time;
	int				sleep_time;
	int				num_meals;
	int				philos_finish;
	long long		start_time;
	int				philo_death;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	philo_finish;
	pthread_mutex_t	mut_death;
	pthread_mutex_t	mut_start;
	t_philo			*all_ph;
}	t_data;

int				check_args(int argc, char **argv);
long long int	ft_atol(const char *str);
int				init_vars(int argc, char **argv, t_data *data);
int				create_threads(t_data *data);
long long		timestamp(void);
int				check_onephilo_death(t_philo *philo);
int				check_allphilos_death(t_data *data);
int				print_mes(t_philo *philo, char c);
int				philo_routine(t_philo *philo);
int				wait_time(t_philo *philo);
int				routine_time(t_philo *philo, char c);
int				mutex_error(t_data *data);
int				manage_errors(t_data *data, char error_type);
int				free_all(t_data *data);

#endif
