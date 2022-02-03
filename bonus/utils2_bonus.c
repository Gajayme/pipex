/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:00:20 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 19:00:22 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	arg_checker(t_pipex arg)
{
	if (arg.arg_amount < 4 && ft_putstr_pipex("Invalid arguments\n"))
		exit(1);
}

int	waiter(t_pipex arg, int **fd, pid_t *pid)
{
	arg.wait_counter = -1;
	while (++arg.wait_counter < arg.counter)
		wrapper_pid(waitpid(pid[arg.wait_counter], NULL, 0),
			fd, pid, arg.counter);
	freer_pid(pid, fd, arg.arg_amount - 4);
	return (0);
}
