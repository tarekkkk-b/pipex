/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:03:40 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/22 21:29:34 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prep_inp(char *str, int ind, t_data *data, int ac)
{
	int	i;

	i = 1;
	while (++i < ac - 1)
	{
		data->cmds[ind] = ft_split(str, ' ');
		data->j_cmds[ind] = ft_strjoin("/", data->cmds[ind][0], 0);
		data->cmd_count++;
	}
}

void	getting_cmds(char **av, int ac, char **env, t_data *data)
{
	int	i;

	i = -1;
	data->placeholder = NULL;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			data->placeholder = ft_strdup(env[i]);
	if (data->placeholder)
	{
		data->path = ft_split(data->placeholder, ':');
		free(data->placeholder);
		data->placeholder = NULL;
	}
	else
		data->path = NULL;
	i = 1;
	data->cmd_count = 0;
	data->j_cmds = malloc(sizeof(char *) * ac - 3);
	data->cmds = malloc(sizeof(char **) * (ac - 3));
	prep_inp(av[i], data->cmd_count, data, ac);
}

void	loop(char **av, int ac, char **env, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		pipe(data->fd);
		data->child = fork();
		if (data->child == 0)
		{
			if (i == 0)
				first_call(av, data);
			else if (i == data->cmd_count - 1)
				last_call(av, ac, data);
			else
				middle_call(data);
			execution(i, env, data);
			exit(1);
		}
		parent_dup(data);
	}
}

void	execution(int i, char **env, t_data *data)
{
	int	j;

	j = -1;
	if (!access(data->cmds[i][0], X_OK | F_OK))
		execve(data->cmds[i][0], data->cmds[i], env);
	if (data->path)
	{
		while (data->path[++j])
		{
			data->cmd_path = ft_strjoin(data->path[j], data->j_cmds[i], 0);
			if (!access(data->cmd_path, X_OK | F_OK))
				execve(data->cmd_path, data->cmds[i], env);
		}
	}
}

void	death(t_data *data)
{
	pid_t	dead;
	int		temp;

	dead = 0;
	while (dead != -1)
	{
		dead = wait(&temp);
		if (dead == data->lastpid)
			data->status = WEXITSTATUS(temp);
	}
}
