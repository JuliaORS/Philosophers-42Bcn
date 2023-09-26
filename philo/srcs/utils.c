/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:34:13 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/24 15:07:59 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	timestamp(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (timev.tv_sec * 1000 + timev.tv_usec / 1000);
}

int	wait_time(t_philo *philo)
{
	int			time;
	long long	init_time;

	init_time = timestamp();
	time = 0;
	if (!philo->n_meals && philo->n_phi % 2 != 0 && philo->n_phi != \
		philo->data_in->num_philos)
		return (0);
	else if (!philo->n_meals && philo->n_phi % 2 == 0)
		time = philo->data_in->eat_time;
	else if (!philo->n_meals && philo->n_phi % 2 != 0 && philo->n_phi \
		== philo->data_in->num_philos)
		time = philo->data_in->eat_time * 2;
	else if (philo->n_meals && philo->data_in->num_philos % 2 != 0)
		time = (philo->data_in->eat_time * 2) - philo->data_in->sleep_time;
	else if (philo->n_meals && philo->data_in->num_philos % 2 == 0)
		time = philo->data_in->eat_time - philo->data_in->sleep_time;
	while (timestamp() - init_time < time)
	{
		if (check_onephilo_death(philo) == 0)
			usleep(50);
		else
			return (1);
	}
	return (0);
}

int	routine_time(t_philo *philo, char c)
{
	long long	init_time;
	long long	routine_time;

	if (c == 'e')
	{
		if (pthread_mutex_lock(&philo->mut_t_lastmeal))
			return (mutex_error(philo->data_in));
		init_time = philo->tlast_meal;
		if (pthread_mutex_unlock(&philo->mut_t_lastmeal))
			return (mutex_error(philo->data_in));
		routine_time = philo->data_in->eat_time;
	}
	else
	{
		init_time = philo->tlast_sleep;
		routine_time = philo->data_in->sleep_time;
	}
	while (timestamp() - init_time < routine_time)
	{
		if (check_onephilo_death(philo) == 0)
			usleep(50);
		else
			return (1);
	}
	return (0);
}

int	mutex_error(t_data *data)
{
	if (pthread_mutex_lock(&data->mut_death))
		return (1);
	data->philo_death = 1;
	if (pthread_mutex_unlock(&data->mut_death))
		return (1);
	return (1);
}

int	manage_errors(t_data *data, char error_type)
{
	(void)data;
	if (error_type == 'a')
		printf("Invalid arguments.");
	else if (error_type == 'v')
		printf("Program error during variable initialization.\n");
	else if (error_type == 't')
		printf("Program error creating threads.\n");
	else if (error_type == 'j')
		printf("Program error closing threads.\n");
	else if (error_type == 'f')
		printf("Program error freeing memory.\n");
	if (error_type != 'f' && error_type != 'a')
		free_all(data);
	return (0);
}
