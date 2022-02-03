/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:59:47 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 18:59:55 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	freer(char **arr, char *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		free (cmd);
		cmd = NULL;
	}
	while (arr[i])
	{
		free(arr[i]);
		i += 1;
	}
	free(arr);
	arr = NULL;
	return (1);
}

int	freer_pid(pid_t *pid, int **fd, int counter)
{
	int	i;

	i = 0;
	if (pid)
	{
		free(pid);
		pid = NULL;
	}
	while (i < counter)
	{
		free(fd[i]);
		i += 1;
	}
	free (fd);
	fd = NULL;
	return (1);
}
