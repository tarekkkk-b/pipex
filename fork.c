/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:46:12 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/13 11:03:01 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	pid_t	pid;
	
	pid = fork();
	wait(NULL);
	if (pid == 0)
		printf("in child process:\nidentifier is %d, pid is %d, and parent is %d\n\n", pid, getpid(), getppid());
	else
		printf("in parent process:\nidentifier is  = to child pid that being %d, this parent pid is %d, and it also has a parent is %d\n\n", pid, getpid(), getppid());
}