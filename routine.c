/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:31:25 by csantivi          #+#    #+#             */
/*   Updated: 2023/01/26 16:19:49 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_state(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, "has taken a fork");
	if (rules->num_of_philo == 1)
	{
		do_something(rules->time_to_die, philo);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, "has taken a fork");
	philo->last_eat = time_stamp();
	print_log(philo, "is eating");
	do_something(rules->time_to_eat, philo);
	philo->eat++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->eat == rules->num_of_eat)
		rules->done++;
}

void	sleeping_state(t_philo *philo)
{
	print_log(philo, "is sleeping");
	do_something(philo->rules->time_to_sleep, philo);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = void_philo;
	rules = philo->rules;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!rules->died)
	{
		eating_state(philo);
		if (philo->eat == rules->num_of_eat || rules->died)
			return (0);
		sleeping_state(philo);
		if (rules->died)
			return (0);
		print_log(philo, "is thinking");
	}
	return (0);
}
