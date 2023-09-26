/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:53:01 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/24 13:31:17 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	get_forks(t_philo *philo)
{
	if (check_onephilo_death(philo) != 0)
		return (1);
	if (pthread_mutex_lock(&philo->data_in->forks[philo->n_phi - 1]))
		return (mutex_error(philo->data_in));
	if (print_mes(philo, 'f'))
		return (1);
	if (check_onephilo_death(philo) != 0)
		return (1);
	if (philo->n_phi == philo->data_in->num_philos)
	{
		if (pthread_mutex_lock(&philo->data_in->forks[0]))
			return (mutex_error(philo->data_in));
	}
	else if (philo->n_phi != philo->data_in->num_philos)
	{
		if (pthread_mutex_lock(&philo->data_in->forks[philo->n_phi]))
			return (mutex_error(philo->data_in));
	}
	if (print_mes(philo, 'f'))
		return (1);
	if (check_onephilo_death(philo) != 0)
		return (1);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	if (get_forks(philo))
		return (1);
	if (pthread_mutex_lock(&philo->mut_t_lastmeal))
		return (mutex_error(philo->data_in));
	philo->tlast_meal = timestamp();
	if (pthread_mutex_unlock(&philo->mut_t_lastmeal))
		return (mutex_error(philo->data_in));
	if (print_mes(philo, 'e'))
		return (1);
	if (routine_time(philo, 'e') == 1) 
		return (1);
	if (pthread_mutex_unlock(&philo->data_in->forks[philo->n_phi - 1]))
		return (mutex_error(philo->data_in));
	if (philo->n_phi == philo->data_in->num_philos)
	{
		if (pthread_mutex_unlock(&philo->data_in->forks[0]))
			return (mutex_error(philo->data_in));
	}
	else
	{
		if (pthread_mutex_unlock(&philo->data_in->forks[philo->n_phi]))
			return (mutex_error(philo->data_in));
	}
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (check_onephilo_death(philo) != 0)
		return (1);
	philo->tlast_sleep = timestamp();
	if (print_mes(philo, 's'))
		return (1);
	if (routine_time(philo, 's'))
		return (1);
	return (0);
}

static int	philo_think(t_philo *philo)
{
	if (check_onephilo_death(philo) != 0)
		return (1);
	if (print_mes(philo, 't'))
		return (1);
	if (wait_time(philo))
		return (1);
	return (0);
}

int	philo_routine(t_philo *philo)
{
	if (philo_think(philo))
		return (1);
	if (philo_eat(philo))
		return (1);
	if (philo_sleep(philo))
		return (1);
	return (0);
}
