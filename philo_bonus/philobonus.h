/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philobonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 14:41:12 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOBONUS_H
# define PHILOBONUS_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data {
	int				num_philos;
	int				dead_time;
	int				eat_time;
	int				sleep_time;
	int				num_meals;
	long long		start_time;
	int				n_phi;
	int				n_meals_ph;
	long long		tlast_meal;
	long long		tlast_sleep;
	pid_t			*pid;
	pthread_t		thread;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
	sem_t			*stop;
}	t_data;

int				check_args(int argc, char **argv);
long long int	ft_atol(const char *str);
int				create_process(t_data *data);
long long		timestamp(void);
int				*check_onephilo_death(t_data *data);
void			print_mes(t_data *data, char c);
void			philo_routine(t_data *data);
void			wait_time(t_data *data);
int				check_philos_death(t_data *data);
void			routine_time(t_data *data, char c);

#endif
