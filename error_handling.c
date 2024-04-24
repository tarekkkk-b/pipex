/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:31:03 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/24 12:43:08 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	freeing(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free (str[i]);
	free (str);
}

void	cleaning(t_data *data)
{
	int	i;

	if (data->placeholder)
		free(data->placeholder);
	if (data->j_cmds)
		freeing(data->j_cmds);
	if (data->path)
		freeing(data->path);
	if (data->cmd_path)
		free (data->cmd_path);
	if (data->cmds)
	{
		i = -1;
		while (data->cmds[++i])
			freeing(data->cmds[i]);
		free (data->cmds);
	}
}

void	disappointment(t_data *data, int *fd, int flag)
{
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->fd[1] != -1)
		close(data->fd[1]);
	if ((*fd) && (*fd) != -1 && flag == 1)
		close ((*fd));
	cleaning(data);
}
