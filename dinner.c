/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:05:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/01/26 18:50:23 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_something(int wait, t_philo *philo)
{
	size_t	start;
	t_rules	*r;

	r = philo->rules;
	start = time_stamp();
	while (time_stamp() - start < (size_t)wait
		&& !r->died)
		usleep(10);
}

void	check_died(t_rules *rules, t_philo **p_philo)
{
	t_philo	*philo;
	int		i;

	philo = *p_philo;
	while (!rules->died && rules->done != rules->num_of_philo)
	{
		i = -1;
		while (++i < rules->num_of_philo && !rules->died)
		{
			if (philo->eat == rules->num_of_eat || rules->died)
				return ;
			if (time_stamp() - philo[i].last_eat >= (size_t)rules->time_to_die)
			{
				print_log(&philo[i], "died");
				rules->died = 1;
			}
		}
	}
}

int	dinner(t_philo **p_philo, t_rules *rules)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = *p_philo;
	while (++i < rules->num_of_philo)
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (1);
	check_died(rules, &philo);
	i = 0;
	while (i < rules->num_of_philo)
		if (pthread_join(philo[i++].thread_id, NULL))
			return (1);
	return (0);
}
