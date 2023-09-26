/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:53:01 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 16:50:42 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philobonus.h"

static void	philo_eat(t_data *data)
{
	sem_wait(data->forks);
	print_mes(data, 'f');
	sem_wait(data->forks);
	print_mes(data, 'f');
	data->tlast_meal = timestamp();
	sem_wait(data->death);
	sem_post(data->death);
	print_mes(data, 'e');
	routine_time(data, 'e');
	data->n_meals_ph++;
	sem_post(data->forks);
	sem_post(data->forks);
}

static void	philo_sleep(t_data *data)
{
	data->tlast_sleep = timestamp();
	print_mes(data, 's');
	routine_time(data, 's');
}

static void	philo_think(t_data *data)
{
	print_mes(data, 't');
	wait_time(data);
}

void	philo_routine(t_data *data)
{
	philo_think(data);
	philo_eat(data);
	philo_sleep(data);
}
