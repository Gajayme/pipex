/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:00:41 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 19:00:43 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	left_side(int *fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	arglist = ft_split(argv[2], ' ');
	cmd = cmd_checker(env, arglist[0]);
	file_1 = wrapper(open(argv[1], O_RDONLY), argv[0], arglist, cmd);
	file_2 = wrapper(dup2(file_1, STDIN_FILENO), argv[0], arglist, cmd);
	file_3 = wrapper(dup2(fd[WRITE_END], STDOUT_FILENO), argv[0], arglist, cmd);
	closer(file_1, fd);
	wrapper(execve(cmd, arglist, env), argv[0], arglist, cmd);
	return (0);
}

int	right_side(int *fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	arglist = ft_split(argv[3], ' ');
	cmd = cmd_checker(env, arglist[0]);
	file_1 = wrapper(open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 420),
			argv[0], arglist, cmd);
	file_2 = wrapper(dup2(fd[READ_END], STDIN_FILENO), argv[0], arglist, cmd);
	file_3 = wrapper(dup2(file_1, STDOUT_FILENO), argv[0], arglist, cmd);
	closer(file_1, fd);
	wrapper(execve(cmd, arglist, env), argv[0], arglist, cmd);
	return (0);
}

int	wrapper(int ret_val, char *name, char **arglist, char *cmd)
{
	if (ret_val == -1)
	{
		if (arglist && cmd)
			freer(arglist, cmd);
		perror(name);
		exit(1);
	}
	else
		return (ret_val);
}

int	main(int args, char *argv[], char *env[])
{
	pid_t	pid_1;
	pid_t	pid_2;
	int		fd[2];

	if (args != 5)
	{
		ft_putstr_fd(ft_strrchr(argv[0], '/') + 1, 1);
		ft_putstr_fd(": Strictly 4 args: input_file cmd1 cmd2 output_file\n", 1);
		exit(1);
	}
	wrapper(pipe(fd), argv[0], NULL, NULL);
	pid_1 = fork();
	wrapper(pid_1, argv[0], NULL, NULL);
	if (pid_1 == 0)
		left_side(fd, argv, env);
	pid_2 = fork();
	wrapper(pid_2, argv[0], NULL, NULL);
	if (pid_2 == 0)
		right_side(fd, argv, env);
	closer(0, fd);
	wrapper(waitpid(pid_1, NULL, 0), argv[0], NULL, NULL);
	wrapper(waitpid(pid_2, NULL, 0), argv[0], NULL, NULL);
	return (0);
}
