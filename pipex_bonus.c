/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:05:33 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/25 14:15:57 by tabadawi         ###   ########.fr       */
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
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.heredocflag = 0;
	data.limiter = NULL;
	if (ac < 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 ... cmdN file2\n", 46);
		exit(1);
	}
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		if (ac < 6)
		{
			write(2, "Usage: ./pipex here_doc \
				LIMITER cmd1 cmd2 ... cmdN outfile", 58);
			exit(1);
		}
		data.heredocflag = 1;
		data.limiter = ft_strdup(av[2]);
		data.cmd_count -= 1;
	}
	initialize(ac, &data);
	getting_cmds(av, ac, env, &data);
	loop(av, ac, env, &data);
	death(&data);
	exit(data.status);
}
