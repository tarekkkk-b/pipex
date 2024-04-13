/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:42:19 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/13 22:07:02 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_split
{
	int		i;
	char	**split;
	int		wordcount;
}	t_split;

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

int main(int ac, char **av, char **env)
{
	int i = 0;
	char *placeholder;
	char **path;
	char *cmd_path;
	char *arg[] = {"ls", "-huya", NULL};
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			placeholder = ft_strdup(env[i]);
		i++;
	}
	if (placeholder)
		(path = ft_split(placeholder, ':'), free (placeholder));
	i = 0;
	// int id = fork();
	// if (id == 0)
	// {
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], "/ls", 0);
		// printf("hello\n");
		if (access(cmd_path, F_OK) == 0)
			break ;
		free (cmd_path);
		i++;
	}
	if (execve(cmd_path, arg, env) == -1)
		(write (2, "command not found\n", 18), exit (1));
	// free (path);
	// }
	// else{
	// wait(NULL);
	i = -1;
	while (path[++i])
		free (path[i]);
	free (path);
}
// }