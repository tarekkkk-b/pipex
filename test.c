/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:59:12 by tabadawi          #+#    #+#             */
/*   Updated: 2024/04/15 19:07:08 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

typedef struct s_split
{
	int		i;
	char	**split;
	int		wordcount;
}	t_split;

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	x;

	x = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && (i < size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	s;
	size_t	t;
	size_t	destl;
	size_t	srcl;

	s = 0;
	t = 0;
	while (dest[t] != '\0')
		t++;
	destl = t;
	srcl = ft_strlen(src);
	if (dstsize == 0 || dstsize <= destl)
		return (srcl + dstsize);
	while (src[s] != '\0' && s < dstsize - destl - 1)
		dest[t++] = src[s++];
	dest[t] = '\0';
	return (destl + srcl);
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

int main(int ac, char **av, char **env)
{
	if (ac != 5)
		exit (1);
	char **cmd1;
	char **cmd2;

	cmd1  = ft_split(av[2], ' ');

	cmd2  = ft_split(av[3], ' ');
	
	char	test1[ft_strlen(cmd1[0]) + ft_strlen("/") + 1];
	ft_strlcpy(test1, "/", 2);
	ft_strlcat(test1, cmd1[0], 10);
	
	char	test2[ft_strlen(cmd2[0]) + ft_strlen("/") + 1];
	ft_strlcpy(test2, "/", 2);
	ft_strlcat(test2, cmd2[0], 10);

	printf("%s\n\n", test1);
	printf("%s\n\n", test2);

	printf("\n\n\n");

	int i  = 0;
	while (cmd1[i])
	{
		printf("%s\n\n", cmd1[i]);
		i++;
	}
	printf("\n\n\n");
	i  = 0;
	while (cmd2[i])
	{
		printf("%s\n\n", cmd2[i]);
		i++;
	}
}