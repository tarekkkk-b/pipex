/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:45:20 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/24 13:11:06 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc(t_data *data)
{
	char	*str;

	close(data->fd[0]);
	data->fd[0] = -1;
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		(perror(NULL), disappointment(data, NULL, 0), exit(1));
	close(data->fd[1]);
	data->fd[1] = -1;
	str = get_next_line(0);
	while (str && (ft_strncmp(str, data->limiter, ft_strlen(str) - 1) != 0)
		&& (str[ft_strlen(str) - 1] == '\n'))
	{
		ft_putstr_fd(str, 1);
		free (str);
		str = get_next_line(0);
	}
	free (str);
	if (data->limiter)
		free (data->limiter);
}
