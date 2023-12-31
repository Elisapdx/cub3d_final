/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:17:51 by kquetat-          #+#    #+#             */
/*   Updated: 2023/11/11 16:42:28 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"
#include <stdio.h>

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	if (!s1)
		s1 = ft_calloc(1, 1);
	i = 0;
	len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	result = ft_calloc(len + 1, sizeof(char));
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	return (result);
}

static char	*ft_stock_next_call(char *stash)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == 0)
	{
		free(stash);
		return (0);
	}
	tmp = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	if (stash[i] == '\n')
		i++;
	j = 0;
	while (stash[i])
	{
		tmp[j] = stash[i];
		j++;
		i++;
	}
	free(stash);
	return (tmp);
}

static char	*ft_stock_result(char *stash)
{
	char	*result;
	int		i;

	i = 0;
	if (stash[i] == 0)
		return (0);
	while (stash[i] && stash[i] != '\n')
		i++;
	result = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		result[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		result[i] = '\n';
	return (result);
}

static char	*ft_read_and_stock(int fd, char	*stash)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (i != 0 && !ft_strchr(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free(buffer);
			free(stash);
			return (0);
		}
		buffer[i] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	stash = ft_read_and_stock(fd, stash);
	if (!stash)
		return (0);
	line = ft_stock_result(stash);
	stash = ft_stock_next_call(stash);
	return (line);
}
