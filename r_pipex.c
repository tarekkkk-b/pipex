/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:36:52 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/17 20:55:43 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_data
{
	int		cmd_count;
	int		fd[2];
	char	***cmds;
	char 	**path;
	char	**j_cmds;
	char	*cmd_path;
	pid_t	child;
	pid_t	lastpid;
	int		status;
}	t_data;

typedef struct s_split
{
	int		i;
	char	**split;
	int		wordcount;
}	t_split;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *input, char *argv, int flag)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!argv || !(*argv))
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(input) + ft_strlen(argv) + 2));
	if (!str)
		return (NULL);
	while (input && input[i])
		str[j++] = input[i++];
	i = 0;
	while (argv[i] && argv[i] != '\n')
		str[j++] = argv[i++];
	str[j] = '\0';
	if (flag == 1)
		free (input);
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char *)malloc((ft_strlen(s1) * sizeof(char)) + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**freeer(char **split, int i)
{
	while (i-- > 0)
		free (split[i]);
	free (split);
	return (NULL);
}

static int	words(const char *s, char c)
{
	int		wordcount;

	wordcount = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (*s != c && *s)
		{
			s++;
			if (*s == c || *s == '\0')
				wordcount++;
		}
	}
	return (wordcount);
}

static char	*wordsize(const char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	t_split	var;

	var.i = 0;
	if (!s)
		return (NULL);
	var.wordcount = words(s, c);
	var.split = malloc(sizeof(char *) * (var.wordcount + 1));
	if (!var.split)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			var.split[var.i] = wordsize(s, c);
			if (!var.split[var.i])
				return (freeer(var.split, var.i));
			var.i++;
			while (*s && *s != c)
				s++;
		}
	}
	var.split[var.i] = (NULL);
	return (var.split);
}

void	prep_inp(char *str, int ind, t_data *data)
{
	data->cmds[ind] = ft_split(str, ' ');
	data->j_cmds[ind] = ft_strjoin("/", data->cmds[ind][0], 0);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	t_data data;

	char	*placeholder;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			placeholder = ft_strdup(env[i]);
		i++;
	}
	if (placeholder)
		(data.path = ft_split(placeholder, ':'), free (placeholder));
	i = 2;
	data.cmd_count = 0;
	data.j_cmds = malloc(sizeof(char *) * ac - 3);
	data.cmds = malloc(sizeof(char **) * (ac - 3));
	while (i < ac - 1)
	{
		prep_inp(av[i], data.cmd_count, &data);
		data.cmd_count++;
		i++;
	}
	int j = 0;
	// int t = 0;
	// while (data.cmds[j])
	// {
	// 	t = 0;
	// 	printf("command: ");
	// 	while (data.cmds[j][t])
	// 	{
	// 		printf ("%s ", data.cmds[j][t]);
	// 		t++;
	// 	}
	// 	printf("\n\n");
	// 	j++;
	// }
	// i = 0;
	// while (data.j_cmds[i])
	// {
	// 	printf("cmd path: %s\n", data.j_cmds[i]);
	// 	i++;
	// }
	i = -1;
	//0644
	while (++i < data.cmd_count)
	{
		j = -1;
		pipe(data.fd);
		data.child = fork();
		if (data.child == 0)
		{
			//duping read end first call
			if (i == 0)
			{
				printf("First child\n");
				close(data.fd[0]);
				int fd = open(av[1], O_RDONLY);
				if (fd == -1)
					exit(EXIT_FAILURE);
				// NEED CLEAMUP
				if (dup2(fd, STDIN_FILENO) == -1)
					exit(EXIT_FAILURE);
				if (dup2(data.fd[1], STDOUT_FILENO) == -1)
					exit(EXIT_FAILURE);
				close(data.fd[1]);
				close (fd);
			} 
			
			// duping the write end
				//last call (outfile)
			else if (i == data.cmd_count - 1)
			{
				printf("Last child\n");
				close(data.fd[0]);
				close (data.fd[1]);
				int fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd2 == -1)
					exit(EXIT_FAILURE);
				if (dup2(fd2, STDOUT_FILENO) == -1)
					exit(EXIT_FAILURE);
				close (fd2);
			}
			
				//other calls
			else
			{
				close(data.fd[0]);
				if (dup2(data.fd[1], STDOUT_FILENO) == -1)
					exit(EXIT_FAILURE);
				close (data.fd[1]);
			}
			while (data.path[++j])
			{
				data.cmd_path = ft_strjoin(data.path[j], data.j_cmds[i], 0);
				if (!access(data.cmd_path, X_OK | F_OK))
					execve(data.cmd_path, data.cmds[i], env);
				// if (access(data.cmd_path, F_OK) != -1)
				// 	if (access(data.cmd_path, X_OK) != -1)
				// 		execve(data.cmd_path, data.cmds[i], env);
			}
			exit(1);
		}
		// else
		// {
			// duping the read end
			// if (i > 0)
			// {
				close (data.fd[1]);
				if (dup2(data.fd[0], STDIN_FILENO) == -1)
					fprintf(stderr, "Parent duping\n");
				close (data.fd[0]);
			// }
			// else 
			// 	(close (data.fd[0]), close (data.fd[1]));
			
			data.lastpid = data.child;
		// }
	}
	pid_t	dead = 0;
	int		temp;
	while (dead != -1)
	{
		dead = wait(&temp);
		if (dead == data.lastpid)
			data.status = WEXITSTATUS(temp); 
	}
	exit(data.status);
}
