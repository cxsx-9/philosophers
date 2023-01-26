/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:53:55 by csantivi          #+#    #+#             */
/*   Updated: 2023/01/26 16:30:04 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				died;
	int				done;
	size_t			start;
	pthread_mutex_t	*fork;
}				t_rules;

typedef struct s_philo
{
	int				id;
	int				eat;
	size_t			last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread_id;
	t_rules			*rules;
}				t_philo;

/*		util.c		*/
int		ft_atoi(char *av, int *arg);
int		parse_args(int ac, char **av, t_rules *rules);
int		error_exit(int e);
void	clear_philo_exit(t_philo **philo, t_rules *rules);
void	print_log(t_philo *philo, char *str);
/*		init.c		*/
int		init_rules(int ac, char **av, t_rules *rules);
int		init_mutex(t_rules *rules);
int		init_philo(t_philo **philo, t_rules *rules);
/*		dinner.c	*/
int		dinner(t_philo **p_philo, t_rules *rules);
void	do_something(int wait, t_philo *philo);
/*		routine.c	*/
void	eating_state(t_philo *philo);
void	sleeping_state(t_philo *philo);
void	*routine(void *void_philo);
/*		main.c		*/
size_t	time_stamp(void);

#endif
