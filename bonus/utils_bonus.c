/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:00:11 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 19:00:13 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

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
	i = -1;
	while (pathes[++i])
	{
		full_cmd = ft_strjoin(pathes[i], cmd);
		if (access(full_cmd, F_OK) == 0 && freer(pathes, cmd))
			return (full_cmd);
		free(full_cmd);
		full_cmd = NULL;
	}
	freer(pathes, cmd);
	return (NULL);
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

int	wrapper(int ret_val, char **arglist, char *cmd)
{
	if (ret_val == -1)
	{
		if (arglist && cmd)
			freer(arglist, cmd);
		perror("pipex.c");
		exit(1);
	}
	else
		return (ret_val);
}

int	wrapper_pid(int ret_val, int **fd, pid_t *pid, int counter)
{
	if (ret_val == -1)
	{
		if (fd || pid)
			freer_pid(pid, fd, counter);
		perror("pipex.c");
		exit(1);
	}
	else
		return (ret_val);
}
