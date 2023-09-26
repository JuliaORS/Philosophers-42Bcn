/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:35:05 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 16:49:55 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philobonus.h"

int	*check_onephilo_death(t_data *data)
{
	if (!data->tlast_meal)
		data->tlast_meal = data->start_time;
	while (1)
	{
		if (timestamp() - data->tlast_meal > data->dead_time)
		{
			print_mes(data, 'd');
			sem_wait(data->death);
			exit (1);
		}
		else if (data->num_meals && data->n_meals_ph == data->num_meals)
			exit (0);
	}
	return (NULL);
}

static int	philo_start(t_data *data, int i)
{
	data->n_phi = i + 1;
	pthread_create(&data->thread, NULL, (void *)check_onephilo_death, data);
	while (1)
		philo_routine(data);
	return (0);
}

int	wait_finish(t_data *data)
{
	int	exit_process;
	int	philos_finish;

	philos_finish = 0;
	while (1)
	{
		if (waitpid (-1, &exit_process, 0) != -1) 
		{
			if (WEXITSTATUS(exit_process) == 1)
			{
				sem_post(data->stop);
				break ;
			}
			else if (WEXITSTATUS(exit_process) == 0)
				philos_finish++;
			if (philos_finish == data->num_philos)
			{
				sem_post(data->stop);
				break ;
			}
		}
	}
	return (0);
}

int	create_process(t_data *data)
{
	int	i;
	int	philos_finish;

	i = 0;
	philos_finish = 0;
	data->start_time = timestamp ();
	while (i < data->num_philos)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			philo_start(data, i);
		i++;
	}
	wait_finish(data);
	return (0);
}
