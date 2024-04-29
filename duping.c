/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:02:28 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/29 21:32:59 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_call(char **av, t_data *data)
{
	int	fd;

	close(data->fd[0]);
	data->fd[0] = -1;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		(perror(av[1]), disappointment(data, &fd, 0), exit(127));
	if (dup2(fd, STDIN_FILENO) == -1)
		(perror(NULL), disappointment(data, &fd, 1), exit(1));
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		(perror(NULL), disappointment(data, &fd, 1), exit(1));
	close(data->fd[1]);
	data->fd[1] = -1;
	close (fd);
	fd = -1;
}

void	middle_call(t_data *data)
{
	close(data->fd[0]);
	data->fd[0] = -1;
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		(perror(NULL), disappointment(data, NULL, 0), exit(1));
	close (data->fd[1]);
	data->fd[1] = -1;
}

void	last_call(char **av, int ac, t_data *data)
{
	int	fd;

	close(data->fd[0]);
	data->fd[0] = -1;
	close (data->fd[1]);
	data->fd[1] = -1;
	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		(perror(av[ac - 1]), disappointment(data, &fd, 0), exit(127));
	if (dup2(fd, STDOUT_FILENO) == -1)
		(perror(NULL), disappointment(data, &fd, 1), exit(1));
	close (fd);
	fd = -1;
}

void	parent_dup(t_data *data)
{
	close (data->fd[1]);
	data->fd[1] = -1;
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		(perror(NULL), disappointment(data, NULL, 0), exit(1));
	close (data->fd[0]);
	data->fd[0] = -1;
}
