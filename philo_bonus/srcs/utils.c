/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:34:13 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 14:38:20 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philobonus.h"

long long	timestamp(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (timev.tv_sec * 1000 + timev.tv_usec / 1000);
}

void	wait_time(t_data *data)
{
	int			time;
	long long	init_time;

	init_time = timestamp();
	time = 0;
	if (!data->n_meals_ph && data->n_phi % 2 != 0 && data->n_phi != \
		data->num_philos)
		return ;
	else if (!data->n_meals_ph && data->n_phi % 2 == 0)
		time = data->eat_time;
	else if (!data->n_meals_ph && data->n_phi % 2 != 0 && data->n_phi \
		== data->num_philos)
		time = data->eat_time * 2;
	else if (data->n_meals_ph && data->num_philos % 2 != 0)
		time = (data->eat_time * 2) - data->sleep_time;
	else if (data->n_meals_ph && data->num_philos % 2 == 0)
		time = data->eat_time - data->sleep_time;
	while (timestamp() - init_time < time)
		usleep(50);
}

void	routine_time(t_data *data, char c)
{
	long long	init_time;
	long long	routine_time;

	if (c == 'e')
	{
		init_time = data->tlast_meal;
		routine_time = data->eat_time;
	}
	else
	{
		init_time = data->tlast_sleep;
		routine_time = data->sleep_time;
	}
	while (timestamp() - init_time < routine_time)
		usleep(50);
}

void	print_mes(t_data *data, char c)
{
	long long	time;

	sem_wait(data->print);
	time = timestamp() - data->start_time;
	if (c == 'f')
		printf("%lli	%i has taken a fork\n", time, data->n_phi);
	else if (c == 'e')
		printf("\033[32m%lli	%i is eating\033[0m\n", time, data->n_phi);
	else if (c == 's')
		printf("\033[36m%lli	%i is sleeping\033[0m\n", time, data->n_phi);
	else if (c == 't')
		printf("\033[33m%lli	%i is thinking\033[0m\n", time, data->n_phi);
	else if (c == 'd')
		printf("\033[31m%lli	%i died\033[0m\n", time, data->n_phi);
	if (c != 'd')
		sem_post(data->print);
}
