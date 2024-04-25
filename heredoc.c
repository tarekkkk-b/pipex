/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:45:20 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/25 14:36:38 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc_child(t_data *data)
{
	char	*str;

	close(data->fd[0]);
	data->fd[0] = -1;
	write(1, "> ", 2);
	str = get_next_line(0);
	while (str && (ft_strncmp(str, data->limiter, ft_strlen(str) - 1) != 0)
		&& (str[ft_strlen(str) - 1] == '\n'))
	{
		write(1, "> ", 2);
		ft_putstr_fd(str, data->fd[1]);
		free (str);
		str = get_next_line(0);
	}
	close(data->fd[1]);
	data->fd[1] = -1;
	free (str);
	if (data->limiter)
		free (data->limiter);
	exit(EXIT_SUCCESS);
}

void	heredoc_parent(t_data *data, pid_t child)
{
	waitpid(child, &data->status, 0);
	close (data->fd[1]);
	data->fd[1] = -1;
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		(ft_putstr_fd("duping failed\n", 2), disappointment(data, NULL, 0), exit(1));
	close (data->fd[0]);
	data->fd[0] = -1;
}

void	heredoc(t_data *data)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		(disappointment(data, NULL, 0), exit(1));
	if (child == 0)
		heredoc_child(data);
	heredoc_parent(data, child);
}
