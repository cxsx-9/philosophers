/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:35:47 by csantivi          #+#    #+#             */
/*   Updated: 2023/01/26 16:37:35 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *av, int *arg)
{
	*arg = 0;
	while (*av && *av >= '0' && *av <= '9')
	{
		*arg *= 10;
		*arg += (*av - '0');
		av++;
	}
	if (*av)
		return (1);
	return (0);
}

int	parse_args(int ac, char **av, t_rules *rules)
{
	if (ac != 5 && ac != 6)
		return (1);
	else
	{
		if (ft_atoi(av[1], &rules->num_of_philo)
			|| ft_atoi(av[2], &rules->time_to_die)
			|| ft_atoi(av[3], &rules->time_to_eat)
			|| ft_atoi(av[4], &rules->time_to_sleep))
			return (1);
		if (ac == 6)
		{
			if (ft_atoi(av[5], &rules->num_of_eat))
				return (1);
		}
		else
			rules->num_of_eat = -1;
	}
	return (0);
}

int	error_exit(int e)
{
	if (e == 1)
		printf("Error : Input is not integer.\n");
	else if (e == 2)
		printf("Error : Can't create Mutex.\n");
	else if (e == 3)
		printf("Error : Can't malloc Philosophers.\n");
	else if (e == 4)
		printf("Error : Can't create thread of Philosophers.\n");
	return (0);
}

void	clear_philo_exit(t_philo **philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_of_philo)
		pthread_mutex_destroy(&rules->fork[i++]);
	free(*philo);
	free(rules->fork);
}

void	print_log(t_philo *philo, char *str)
{
	t_rules	*r;

	r = philo->rules;
	if (r->died)
	{
		usleep(r->time_to_die * 1000);	
		return ;
	}
	printf("%ld %d %s\n", time_stamp() - r->start, philo->id, str);
}
