/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:35:05 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 16:42:01 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	sum_one_philo_finish(t_philo *philo)
{
	if (check_onephilo_death(philo) == 0)
	{
		if (pthread_mutex_lock(&philo->data_in->philo_finish))
			return (mutex_error(philo->data_in));
		philo->data_in->philos_finish++;
		if (pthread_mutex_unlock(&philo->data_in->philo_finish))
			return (mutex_error(philo->data_in));
	}
	return (0);
}

static int	start_program(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data_in->mut_start))
		return (1);
	while (philo->data_in->start_time == 0)
		;
	if (pthread_mutex_unlock(&philo->data_in->mut_start))
		return (1);
	return (0);
}

static int	sum_one_philo_meal(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mut_n_meals))
		return (1);
	philo->n_meals++;
	if (pthread_mutex_unlock(&philo->mut_n_meals))
		return (1);
	return (0);
}

void	*philo_start(t_philo *philo)
{
	if (start_program(philo) == 1)
		return (NULL);
	if (philo->data_in->num_meals != 0) 
	{
		while (!check_onephilo_death(philo) && philo->n_meals < \
			philo->data_in->num_meals)
		{
			if (philo_routine(philo))
				return (NULL);
			if (sum_one_philo_meal(philo))
				return (NULL);
		}
	}
	else
	{
		while (check_onephilo_death(philo) == 0)
		{
			if (philo_routine(philo))
				return (NULL);
			if (sum_one_philo_meal(philo))
				return (NULL);
		}
	}
	sum_one_philo_finish(philo);
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_lock(&data->mut_start))
		return (mutex_error(data));
	while (i < data->num_philos)
	{
		if (pthread_create(&data->all_ph[i].thread, NULL, \
			(void *)philo_start, &data->all_ph[i]))
			return (1);
		i++;
	}
	data->start_time = timestamp();
	if (pthread_mutex_unlock(&data->mut_start))
		return (mutex_error(data));
	return (0);
}
