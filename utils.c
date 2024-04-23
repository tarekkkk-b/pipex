/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:03:40 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/23 21:48:33 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prep_inp(char **av, t_data *data, int ac)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (++i < ac - 1)
	{
		data->cmds[j] = ft_split(av[i], ' ');
		data->j_cmds[j] = ft_strjoin("/", data->cmds[j][0], 0);
		j++;
	}
}

void	getting_cmds(char **av, int ac, char **env, t_data *data)
{
	int	i;

	i = -1;
	if (env && env[0])
	{
		while (env[++i])
			if (ft_strncmp(env[i], "PATH", 4) == 0)
				data->placeholder = ft_strdup(env[i]);
	}
	if (data->placeholder)
	{
		data->path = ft_split(data->placeholder, ':');
		free(data->placeholder);
		data->placeholder = NULL;
		data->j_cmds = malloc(sizeof(char *) * data->cmd_count);
	}
	data->cmds = malloc(sizeof(char **) * (data->cmd_count));
	prep_inp(av, data, ac);
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
		}
		parent_dup(data);
		data->lastpid = data->child;
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
			if (data->cmd_path)
			{
				free (data->cmd_path);
				data->cmd_path = NULL;
			}
		}
		ft_putstr_fd(data->cmds[i][0], 2);
		(write(2, ": Command not found\n", 20), cleaning(data), exit(127));
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
