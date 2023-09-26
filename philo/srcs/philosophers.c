/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:43:31 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 16:45:23 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_all(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->all_ph)
		free(data->all_ph);
	return (0);
}

static int	destroy_mutex_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_unlock(&data->forks[i]))
			return (mutex_error(data));
		if (pthread_mutex_destroy(&data->forks[i]))
			return (mutex_error(data));
		if (pthread_mutex_unlock(&data->all_ph[i].mut_n_meals))
			return (mutex_error(data));
		if (pthread_mutex_destroy(&data->all_ph[i].mut_n_meals))
			return (mutex_error(data));
		if (pthread_mutex_unlock(&data->all_ph[i].mut_t_lastmeal))
			return (mutex_error(data));
		if (pthread_mutex_destroy(&data->all_ph[i].mut_t_lastmeal))
			return (mutex_error(data));
		i++;
	}
	return (0);
}

static int	destroy_mutex(t_data *data)
{
	if (pthread_mutex_unlock(&data->print))
		return (mutex_error(data));
	if (pthread_mutex_destroy(&data->print))
		return (mutex_error(data));
	if (pthread_mutex_unlock(&data->philo_finish))
		return (mutex_error(data));
	if (pthread_mutex_destroy(&data->philo_finish))
		return (mutex_error(data));
	if (pthread_mutex_destroy(&data->mut_start))
		return (mutex_error(data));
	if (destroy_mutex_philos(data))
		return (1);
	return (0);
}

static int	close_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_philos == 1)
	{
		if (pthread_detach(data->all_ph[0].thread))
			return (1);
	}
	else 
	{
		while (i < data->num_philos)
		{
			if (pthread_join(data->all_ph[i].thread, NULL))
				return (1);
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc != 5 && argc != 6) || check_args(argc, argv) == 1)
		return (manage_errors(&data, 'a'));
	if (init_vars(argc, argv, &data) == 1)
		return (manage_errors(&data, 'v'));
	if (create_threads(&data) == 1)
		return (manage_errors(&data, 't'));
	while (check_allphilos_death(&data) == 0)
		;
	if (close_threads(&data))
		return (manage_errors(&data, 'j'));
	if (destroy_mutex(&data) == 1)
		return (manage_errors(&data, 'f'));
	if (free_all(&data) == 1)
		return (manage_errors(&data, 'f'));
	return (0);
}
