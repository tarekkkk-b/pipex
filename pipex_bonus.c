/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:05:33 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/30 14:16:52 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	initialize(int ac, t_data *data)
{
	data->placeholder = NULL;
	data->path = NULL;
	data->j_cmds = NULL;
	data->cmds = NULL;
	data->cmd_path = NULL;
	data->cmd_count = ac - 3;
	data->heredocflag = 0;
	data->limiter = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	initialize(ac, &data);
	if (ac < 5 && ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) != 0)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 ... cmdN file2\n", 46);
		exit(1);
	}
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
		{
			write(2, "Usage: ./pipex here_doc LIMITER ", 33);
			(write (2, "cmd1 cmd2 ... cmdN outfile\n", 27), exit(1));
		}
		data.heredocflag = 1;
		data.limiter = ft_strjoin(av[2], "\n", 0);
		data.cmd_count -= 1;
	}
	getting_cmds(av, ac, env, &data);
	loop(av, ac, env, &data);
	death(&data);
	cleaning(&data);
	exit(data.status);
}
