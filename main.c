/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:40:23 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/22 21:11:18 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	getting_cmds(av, ac, env, &data);
	loop(av, ac, env, &data);
	death(&data);
	exit(data.status);
}

//input fails: exit 127

//output fails: exit 127

//cmd fails: exit 127

//else exit: 1