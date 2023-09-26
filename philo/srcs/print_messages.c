/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:24:41 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/24 12:47:45 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	print_aux(t_philo *philo, char c)
{
	long long	time;

	time = timestamp() - philo->data_in->start_time;
	if (c == 'f')
		printf("%lli	%i has taken a fork\n", time, philo->n_phi);
	else if (c == 'e')
		printf("\033[32m%lli	%i is eating\033[0m\n", time, philo->n_phi);
	else if (c == 's')
		printf("\033[36m%lli	%i is sleeping\033[0m\n", time, philo->n_phi);
	else if (c == 't')
		printf("\033[33m%lli	%i is thinking\033[0m\n", time, philo->n_phi);
	else if (c == 'd')
		printf("\033[31m%lli	%i died\033[0m\n", time, philo->n_phi);
}

int	print_mes(t_philo *philo, char c)
{
	if (pthread_mutex_lock(&philo->data_in->mut_death))
		return (mutex_error(philo->data_in));
	if (philo->data_in->philo_death == 1)
	{
		if (pthread_mutex_unlock(&philo->data_in->mut_death))
			return (mutex_error(philo->data_in));
		return (1);
	}
	if (pthread_mutex_lock(&philo->data_in->print))
		return (mutex_error(philo->data_in));
	if (c == 'd')
		philo->data_in->philo_death = 1;
	print_aux(philo, c);
	if (pthread_mutex_unlock(&philo->data_in->mut_death))
		return (mutex_error(philo->data_in));
	if (pthread_mutex_unlock(&philo->data_in->print))
		return (mutex_error(philo->data_in));
	if (c == 'd')
		return (1);
	return (0);
}
