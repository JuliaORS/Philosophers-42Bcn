/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:02:12 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/29 17:00:59 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->all_ph = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->all_ph)
		return (1);
	while (i < data->num_philos)
	{
		data->all_ph[i].n_phi = i + 1;
		data->all_ph[i].n_meals = 0;
		data->all_ph[i].tlast_meal = 0;
		data->all_ph[i].data_in = data;
		if (pthread_mutex_init(&data->all_ph[i].mut_n_meals, NULL))
			return (mutex_error(data));
		if (pthread_mutex_init(&data->all_ph[i].mut_t_lastmeal, NULL))
			return (mutex_error(data));
		i++;
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (mutex_error(data));
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (mutex_error(data));
		i++;
	}
	return (0);
}

int	init_vars(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atol(argv[1]);
	data->dead_time = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]);
	data->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atol(argv[5]);
	else
		data->num_meals = 0;
	data->start_time = 0;
	data->philo_death = 0;
	data->philos_finish = 0;
	if (pthread_mutex_init(&data->print, NULL))
		return (mutex_error(data));
	if (pthread_mutex_init(&data->philo_finish, NULL))
		return (mutex_error(data));
	if (pthread_mutex_init(&data->mut_death, NULL))
		return (mutex_error(data));
	if (pthread_mutex_init(&data->mut_start, NULL))
		return (mutex_error(data));
	if (init_forks(data) == 1)
		return (mutex_error(data));
	if (init_philos(data) == 1)
		return (mutex_error(data));
	return (0);
}
