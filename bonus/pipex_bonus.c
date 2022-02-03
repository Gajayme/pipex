/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:59:56 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 19:00:00 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	left_side(t_pipex arg, int **fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	file_1 = wrapper(open(argv[1], O_RDONLY), NULL, NULL);
	file_2 = wrapper(dup2(file_1, STDIN_FILENO), NULL, NULL);
	file_3 = wrapper(dup2(fd[arg.counter][WRITE_END],
				STDOUT_FILENO), NULL, NULL);
	arglist = ft_split(argv[2], ' ');
	cmd = cmd_checker(env, arglist[0]);
	close(file_1);
	close(fd[arg.counter][WRITE_END]);
	close(fd[arg.counter][READ_END]);
	wrapper(execve(cmd, arglist, env), arglist, cmd);
}

void	middle(t_pipex arg, int **fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_2;
	int		file_3;
	char	**arglist;

	file_2 = wrapper(dup2(fd[arg.counter - 1][READ_END], STDIN_FILENO),
			NULL, NULL);
	file_3 = wrapper(dup2(fd[arg.counter][WRITE_END], STDOUT_FILENO),
			NULL, NULL);
	arglist = ft_split(argv[arg.counter + 2], ' ');
	cmd = cmd_checker(env, arglist[0]);
	close(fd[arg.counter - 1][READ_END]);
	close(fd[arg.counter - 1][WRITE_END]);
	close(fd[arg.counter][READ_END]);
	close(fd[arg.counter][WRITE_END]);
	wrapper(execve(cmd, arglist, env), arglist, cmd);
}

void	right_side(t_pipex arg, int **fd, char *argv[], char *env[])
{
	char	*cmd;
	int		file_1;
	int		file_2;
	int		file_3;
	char	**arglist;

	file_1 = wrapper(open(argv[arg.arg_amount - 1], O_TRUNC | O_WRONLY
				| O_CREAT, 420), NULL, NULL);
	file_2 = wrapper(dup2(fd[arg.counter - 1][READ_END], STDIN_FILENO),
			NULL, NULL);
	file_3 = wrapper(dup2(file_1, STDOUT_FILENO), NULL, NULL);
	arglist = ft_split(argv[arg.counter + 2], ' ');
	cmd = cmd_checker(env, arglist[0]);
	close(file_1);
	close(fd[arg.counter - 1][READ_END]);
	close(fd[arg.counter - 1][WRITE_END]);
	wrapper(execve(cmd, arglist, env), arglist, cmd);
}

void	distributor(t_pipex arg, int **fd, pid_t *pid)
{
	arg.counter = -1;
	while (++arg.counter < (arg.arg_amount - 3))
	{
		pid[arg.counter] = fork();
		wrapper(pid[arg.counter], NULL, NULL);
		if (arg.counter == 0 && pid[arg.counter] == 0)
			left_side(arg, fd, arg.arguments, arg.envrnm);
		else if (arg.counter == 0 && pid[arg.counter] != 0)
			close(fd[arg.counter][WRITE_END]);
		else if (arg.counter == (arg.arg_amount - 4) && pid[arg.counter] == 0)
			right_side(arg, fd, arg.arguments, arg.envrnm);
		else if (arg.counter == (arg.arg_amount - 4) && pid[arg.counter] != 0)
			close(fd[arg.counter - 1][READ_END]);
		else if (pid[arg.counter] == 0)
			middle(arg, fd, arg.arguments, arg.envrnm);
		else if (pid[arg.counter] != 0)
		{
			close(fd[arg.counter - 1][READ_END]);
			close(fd[arg.counter][WRITE_END]);
		}
	}	
}

int	main(int args, char *argv[], char *env[])
{
	t_pipex			arg;
	pid_t			*pid;
	int				**fd;

	arg.arg_amount = args;
	arg.arguments = argv;
	arg.envrnm = env;
	arg_checker(arg);
	fd = (int **)malloc(sizeof(int *) * (args - 4));
	if (!fd)
		exit(1);
	arg.counter = -1;
	while (++arg.counter < (args - 4))
	{
		fd[arg.counter] = malloc(sizeof(int) * 2);
		if (!fd[arg.counter] && freer_pid(NULL, fd, arg.counter))
			exit(1);
		wrapper_pid(pipe(fd[arg.counter]), fd, NULL, arg.counter);
	}
	pid = (pid_t *)malloc(sizeof(pid_t) * (args - 3));
	if (!pid && freer_pid(NULL, fd, arg.counter))
		exit(1);
	distributor(arg, fd, pid);
	return (waiter(arg, fd, pid));
}
