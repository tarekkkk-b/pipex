/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:36:52 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/15 21:01:44 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef struct s_data
{
	int		cmd_count;
	int		fd[2];
	char	***cmds;
	char 	**path;
	char	**j_cmds;
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
	data->j_cmds[ind] = ft_strjoin(data->cmds[ind][0], "/", 0);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	t_data data;

	i = 0;
	data.cmd_count = ac - 3;
	data.j_cmds = malloc(sizeof(char *) * ac - 1);
	data.cmds = malloc(sizeof(char **) * (ac - 1));
	while (++i < ac - 1)
		prep_inp(av[i], i - 1, &data);
	i = 0;
	int j = 1;
	int t = 0;
	while (data.cmds[j])
	{
		t = 0;
		printf("command: ");
		while (data.cmds[j][t])
		{
			printf ("%s ", data.cmds[j][t]);
			t++;
		}
		printf("\n\n");
		j++;
	}
}
