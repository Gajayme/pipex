/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:15:36 by gajayme           #+#    #+#             */
/*   Updated: 2021/12/28 10:45:38 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memory free
// checking if we received path with program

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*cmd_checker(char **env, char *cmd);
char	*path_parse(char **env, char *cmd);
void	freer(char **arr, char *cmd);

char	*cmd_checker(char **env, char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	else
		return (path_parse(env, cmd));
}

void	freer(char **arr, char *cmd)
{
	int	i;

	i = 0;
	if (cmd)
		free (cmd);
	while (arr[i])
	{
		//printf("arr[%d]: %s\n", i, arr[i]);
		free(arr[i]);
		i += 1;
	}
	free(arr);
	return ;
}

char	*path_parse(char **env, char *cmd)
{
	int		i;
	char	**pathes;
	char	*full_cmd;

	i = 0;
	cmd = ft_strjoin("/", cmd); // allocate + (2)
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i ++;
	env[i] = ft_strtrim(env[i], "PATH="); // allocate + (3)
	pathes = ft_split(env[i], ':'); // allocate + (4)
	free(env[i]); //free (3)
	i = 0;
	while (pathes[i])
	{
		full_cmd = ft_strjoin(pathes[i], cmd);// allocate +- (5)
		if (access(full_cmd, F_OK) == 0)
		{
			freer(pathes, cmd); //free (2, 4)
			return (full_cmd); // non freed
		}
		i += 1;
		free(full_cmd); //free (5)
	}
	freer(pathes, cmd); //free (2, 4)
	return (NULL);
}

int	left_side(int *fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	close(fd[0]);
	arglist = ft_split(argv[2], ' '); // allocate (1)
	cmd = cmd_checker(env, arglist[0]);
	file_1 = open(argv[1], O_RDONLY);
	if (file_1 < 0)
		return (1);
	file_2 = dup2(file_1, STDIN_FILENO);
	file_3 = dup2(fd[1], STDOUT_FILENO);
	if (execve(cmd, arglist, env) == -1)
	{
		freer(arglist, cmd);
		perror("Script executing error\n"); //????
		return (1);
	}
	exit(1);// ?????
}

int	right_side(int *fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	close(fd[1]);
	arglist = ft_split(argv[3], ' '); // allocate (2)
	cmd = cmd_checker(env, arglist[0]);
	if (cmd)
	{
		file_1 = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
		if (file_1 < 0)
			return (1);
		file_2 = dup2(fd[0], STDIN_FILENO);
		file_3 = dup2(file_1, STDOUT_FILENO);
		if (execve(cmd, arglist, env) == -1)
		{
			freer(arglist, cmd);
			perror("Script executing error\n"); //??????
			return (1);
		}
	}
	exit(1); //????
}

int	main(int args, char *argv[], char *env[])
{
	pid_t	pid_1;
	pid_t	pid_2;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid_1 = fork();
	if (pid_1 == -1)
		return (1);
	if (pid_1 == 0)
		left_side(fd, argv, env);
	pid_2 = fork();
	if (pid_2 == -1)
		return (1);
	if (pid_2 == 0)
		right_side(fd, argv, env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
	return (0);
}
