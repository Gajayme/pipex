/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:00:52 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 19:01:10 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

char	*cmd_checker(char **env, char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	else
		return (path_parse(env, cmd));
}

char	*path_parse(char **env, char *cmd)
{
	int		i;
	char	**pathes;
	char	*full_cmd;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i ++;
	env[i] = ft_strtrim(env[i], "PATH=");
	pathes = ft_split(env[i], ':');
	free(env[i]);
	i = 0;
	while (pathes[i])
	{
		full_cmd = ft_strjoin(pathes[i], cmd);
		if (access(full_cmd, F_OK) == 0 && freer(pathes, cmd))
			return (full_cmd);
		i += 1;
		free(full_cmd);
		full_cmd = NULL;
	}
	freer(pathes, cmd);
	return (NULL);
}

int	freer(char **arr, char *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		free(cmd);
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

int	ft_putstr_pipex(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		write(1, s, 1);
		s += 1;
	}
	return (1);
}

int	closer(int file_fd, int *pipe_fd)
{
	if (file_fd)
		close(file_fd);
	if (pipe_fd)
	{
		close(pipe_fd[READ_END]);
		close(pipe_fd[WRITE_END]);
	}
	return (1);
}
