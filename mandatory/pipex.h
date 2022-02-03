/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:00:47 by gajayme           #+#    #+#             */
/*   Updated: 2022/01/09 19:19:43 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0
# define WRITE_END 1

# define ARGS_ERROR 1

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "./../lib/libft.h"

char	*path_parse(char **env, char *cmd);
char	*cmd_checker(char **env, char *cmd);
int		ft_putstr_pipex(char *s);
int		freer(char **arr, char *cmd);
int		closer(int file_fd, int *pipe_fd);
int		left_side(int *fd, char *argv[], char *env[]);
int		right_side(int *fd, char *argv[], char *env[]);
int		wrapper(int ret_val, char *name, char **arglist, char *cmd);
#endif
