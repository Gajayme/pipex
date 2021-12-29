/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:15:36 by gajayme           #+#    #+#             */
/*   Updated: 2021/12/27 11:50:41 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

char	*path_parse(char **env, char *cmd)
{
	int		i;
	char	**pathes;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i ++;
	env[i] = ft_strtrim(env[i], "PATH=");
	pathes = ft_split(env[i], ':');
	i = 0;
	while (pathes[i])
	{
		if (access(ft_strjoin(pathes[i], cmd), F_OK) == 0)
			return (ft_strjoin(pathes[i], cmd));
		i += 1;
	}
	return (NULL);
}

int	left_side(int *fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	printf("Left_1\n");
	close(fd[0]);
	arglist = ft_split(argv[2], ' ');
	cmd = path_parse(env, arglist[0]);
	file_1 = open(argv[1], O_RDONLY);
	if (file_1 < 0)
		return (1);
	printf("Left_2\n");
	file_2 = dup2(file_1, STDIN_FILENO);
	file_3 = dup2(fd[1], STDOUT_FILENO);
	printf("Left_before_exec\n");
	if (execve(cmd, arglist, env) == -1)
	{
		perror("Script executing error\n");
		return (1);
	}
}

int	right_side(int *fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	close(fd[1]);
	arglist = ft_split(argv[3], ' ');
	cmd = path_parse(env, arglist[0]);
	file_1 = open(argv[4], O_WRONLY);
	if (file_1 < 0)
		return (1);
	file_2 = dup2(fd[0], STDIN_FILENO);
	file_3 = dup2(file_1, STDOUT_FILENO);
	if (execve(cmd, arglist, env) == -1)
	{
		perror("Script executing error\n");
		return (1);
	}
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
