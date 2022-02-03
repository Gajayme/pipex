/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:00:05 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 19:19:42 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define READ_END 0
# define WRITE_END 1

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "./../lib/libft.h"

typedef struct s_pipex {
	int		counter;
	int		wait_counter;
	int		arg_amount;
	char	**arguments;
	char	**envrnm;
}				t_pipex;

char	*path_parse(char **env, char *cmd);
char	*cmd_checker(char **env, char *cmd);
void	arg_checker(t_pipex arg);
void	distributor(t_pipex arg, int **fd, pid_t *pid);
void	malloc_pid(t_pipex *arg, int ***fd, pid_t **pid);
void	middle(t_pipex arg, int **fd, char *argv[], char *env[]);
void	left_side(t_pipex arg, int **fd, char *argv[], char *env[]);
void	right_side(t_pipex arg, int **fd, char *argv[], char *env[]);
int		ft_putstr_pipex(char *s);
int		freer(char **arr, char *cmd);
int		waiter(t_pipex arg, int **fd, pid_t *pid);
int		freer_pid(pid_t *pid, int **fd, int counter);
int		wrapper(int ret_val, char **arglist, char *str);
int		wrapper_pid(int ret_val, int **fd, pid_t *pid, int counter);
#endif
