/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:38:13 by csantivi          #+#    #+#             */
/*   Updated: 2023/01/26 00:08:51 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_rules(int ac, char **av, t_rules *rules)
{
	if (parse_args(ac, av, rules))
		return (1);
	rules->done = 0;
	rules->died = 0;
	rules->start = time_stamp();
	return (0);
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->fork = malloc(rules->num_of_philo * sizeof(pthread_mutex_t));
	if (!rules->fork)
		return (1);
	while (i < rules->num_of_philo)
	{
		if (pthread_mutex_init(&rules->fork[i++], NULL))
		{
			while (i >= 0)
				pthread_mutex_destroy(&rules->fork[--i]);
			free(rules->fork);
			return (1);
		}
	}
	return (0);
}

int	init_philo(t_philo **philo, t_rules *rules)
{	
	t_philo	*p_philo;
	int		i;

	i = 0;
	p_philo = malloc(rules->num_of_philo * sizeof(p_philo));
	if (!p_philo)
		return (1);
	while (i < rules->num_of_philo)
	{
		p_philo[i].id = i + 1;
		p_philo[i].eat = 0;
		p_philo[i].last_eat = time_stamp();
		p_philo[i].l_fork = &rules->fork[i];
		p_philo[i].r_fork = &rules->fork[(i + 1) % rules->num_of_philo];
		p_philo[i].rules = rules;
		i++;
	}
	*philo = p_philo;
	return (0);
}
