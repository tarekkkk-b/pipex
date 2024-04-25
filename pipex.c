/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:40:23 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/25 13:56:27 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	initialize(int ac, t_data *data)
{
	data->cmd_count = ac - 3;
	data->placeholder = NULL;
	data->path = NULL;
	data->j_cmds = NULL;
	data->cmds = NULL;
	data->cmd_path = NULL;
	data->heredocflag = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
		(write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37), exit(1));
	initialize(ac, &data);
	getting_cmds(av, ac, env, &data);
	loop(av, ac, env, &data);
	death(&data);
	exit(data.status);
}
