/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:45:27 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/24 13:00:51 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_onephilo_death(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data_in->mut_death))
		return (mutex_error(philo->data_in));
	if (philo->data_in->philo_death == 1)
	{
		if (pthread_mutex_unlock(&philo->data_in->mut_death))
			return (mutex_error(philo->data_in));
		return (1);
	}
	if (pthread_mutex_unlock(&philo->data_in->mut_death))
		return (mutex_error(philo->data_in));
	if (pthread_mutex_lock(&philo->mut_t_lastmeal))
		return (mutex_error(philo->data_in));
	if (philo->tlast_meal == 0)
		philo->tlast_meal = philo->data_in->start_time;
	if (timestamp() - philo->tlast_meal > philo->data_in->dead_time)
	{
		if (pthread_mutex_unlock(&philo->mut_t_lastmeal))
			return (mutex_error(philo->data_in));
		print_mes(philo, 'd');
		return (1);
	}
	if (pthread_mutex_unlock(&philo->mut_t_lastmeal))
		return (mutex_error(philo->data_in));
	return (0);
}

static int	check_philos_finish(t_data *data)
{
	if (pthread_mutex_lock(&data->mut_death))
		return (mutex_error(data));
	if (pthread_mutex_lock(&data->philo_finish))
		return (mutex_error(data));
	if (data->philo_death == 1 || data->philos_finish == data->num_philos)
	{
		if (pthread_mutex_unlock(&data->mut_death))
			return (mutex_error(data));
		if (pthread_mutex_unlock(&data->philo_finish))
			return (mutex_error(data));
		return (1);
	}
	if (pthread_mutex_unlock(&data->mut_death))
		return (mutex_error(data));
	if (pthread_mutex_unlock(&data->philo_finish))
		return (mutex_error(data));
	return (0);
}

static int	check_this_philo_dead(t_data *data, int i)
{
	if (pthread_mutex_lock(&data->all_ph[i].mut_t_lastmeal))
		return (mutex_error(data));
	if (!data->all_ph[i].tlast_meal)
		data->all_ph[i].tlast_meal = data->start_time;
	if (timestamp() - data->all_ph[i].tlast_meal > data->dead_time)
	{
		if (pthread_mutex_unlock(&data->all_ph[i].mut_t_lastmeal))
			return (mutex_error(data));
		print_mes(&data->all_ph[i], 'd');
		return (1);
	}
	if (pthread_mutex_unlock(&data->all_ph[i].mut_t_lastmeal))
		return (mutex_error(data));
	return (0);
}

int	check_allphilos_death(t_data *data)
{
	int	i;

	i = 0;
	if (check_philos_finish(data))
		return (1);
	while (i < data->num_philos)
	{
		if (pthread_mutex_lock(&data->all_ph[i].mut_n_meals))
			return (mutex_error(data));
		if (!data->num_meals || data->all_ph[i].n_meals != data->num_meals)
		{
			if (check_this_philo_dead(data, i))
				return (1);
		}
		if (pthread_mutex_unlock(&data->all_ph[i].mut_n_meals))
			return (mutex_error(data));
		i++;
	}
	return (0);
}
