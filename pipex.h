/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:40:39 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/24 13:23:10 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_data
{
	int		cmd_count;
	int		fd[2];
	int		status;
	char	***cmds;
	char	**path;
	char	**j_cmds;
	char	*cmd_path;
	char	*placeholder;
	char	*limiter;
	pid_t	child;
	pid_t	lastpid;
	int		heredocflag;
}	t_data;

void	first_call(char **av, t_data *data);
void	middle_call(t_data *data);
void	last_call(char **av, int ac, t_data *data);
void	parent_dup(t_data *data);
void	prep_inp(char **av, t_data *data, int ac);
void	getting_cmds(char **av, int ac, char **env, t_data *data);
void	loop(char **av, int ac, char **env, t_data *data);
void	execution(int i, char **env, t_data *data);
void	death(t_data *data);
void	disappointment(t_data *data, int *fd, int flag);
void	cleaning(t_data *data);
void	heredoc(t_data *data);

#endif