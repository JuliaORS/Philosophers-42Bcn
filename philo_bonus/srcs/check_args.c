/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:13:45 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/31 13:32:33 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philobonus.h"

static int	ft_strdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (-1);
		i++;
	}
	return (0);
}

long long int	ft_atol(const char *str)
{
	int				i;
	long long int	result;

	result = 0;
	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i] != '\0' && ('0' <= str[i] && str[i] <= '9'))
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result);
}

int	check_args(int argc, char **argv)
{
	if (ft_strdigit(argv[1]) == -1 || ft_strdigit(argv[2]) == -1 || \
		ft_strdigit(argv[3]) == -1 || ft_strdigit(argv[4]) == -1)
		return (1);
	if (ft_atol(argv[1]) >= INT_MAX || ft_atol(argv[2]) >= INT_MAX || \
		ft_atol(argv[3]) >= INT_MAX || ft_atol(argv[4]) >= INT_MAX)
		return (1);
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[2]) <= 0 || \
		ft_atol(argv[3]) <= 0 || ft_atol(argv[4]) <= 0)
		return (1);
	if (argc == 6)
	{
		if (ft_strdigit(argv[5]) == -1)
			return (1);
		if (ft_atol(argv[5]) > INT_MAX || ft_atol(argv[5]) <= 0)
			return (1);
	}
	return (0);
}
