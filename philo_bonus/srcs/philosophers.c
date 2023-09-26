/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:43:31 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 15:23:55 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philobonus.h"

static int	manage_errors(char error_type)
{
	if (error_type == 'a')
		printf("Invalid arguments.");
	else if (error_type == 'i')
		printf("Program error initializing variables.\n");
	else if (error_type == 'p')
		printf("Program error creating process.\n");
	return (0);
}

static void	init_sem(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
	sem_unlink("stop");
	sem_unlink("philos_finish");
	data->forks = sem_open("forks", O_CREAT, 0600, data->num_philos);
	data->print = sem_open("print", O_CREAT, 0600, 1);
	data->death = sem_open("death", O_CREAT, 0600, 1);
	data->death = sem_open("stop", O_CREAT, 0600, 1);
}

static int	init_vars(int argc, char **argv, t_data *data)
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
	data->n_phi = 0;
	data->n_meals_ph = 0;
	data->tlast_meal = 0;
	data->tlast_sleep = 0;
	data->pid = malloc (sizeof(pid_t) * data->num_philos);
	if (!data->pid)
		return (1);
	init_sem(data);
	return (0);
}

static void	finish_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->death);
	sem_close(data->stop);
	free(data->pid);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc != 5 && argc != 6) || check_args(argc, argv) == 1)
		return (manage_errors('a'));
	if (init_vars(argc, argv, &data))
		return (manage_errors('i'));
	if (create_process(&data) == 1)
		return (manage_errors('p'));
	sem_wait(data.stop);
	finish_all(&data);
	return (0);
}
