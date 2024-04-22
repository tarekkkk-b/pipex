/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:02:28 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/22 21:17:09 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_call(char **av, t_data *data)
{
	int	fd;

	close(data->fd[0]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		(perror(av[1]), exit(127));
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(data->fd[1]);
	close (fd);
}

void	middle_call(t_data *data)
{
	close(data->fd[0]);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close (data->fd[1]);
}

void	last_call(char **av, int ac, t_data *data)
{
	int	fd;

	close(data->fd[0]);
	close (data->fd[1]);
	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av[ac - 1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close (fd);
}

void	parent_dup(t_data *data)
{
	close (data->fd[1]);
	dup2(data->fd[0], STDIN_FILENO);
	close (data->fd[0]);
	data->lastpid = data->child;
}
