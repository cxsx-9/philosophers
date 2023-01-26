/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:38:05 by csantivi          #+#    #+#             */
/*   Updated: 2023/01/26 17:46:47 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	time_stamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_rules	rules;

	if (init_rules(ac, av, &rules))
		return (error_exit(1));
	if (init_mutex(&rules))
		return (error_exit(2));
	if (init_philo(&philo, &rules))
		return (error_exit(3));
	if (dinner(&philo, &rules))
		return (error_exit(4));
	clear_philo_exit(&philo, &rules);
	return (0);
}
