/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:41:48 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/18 11:46:44 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buffer);
char	*keep_line(char *stash);
char	*clean_stash(char *stash);

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, 1);
	stash = read_file(fd, stash);
	line = keep_line(stash);
	stash = clean_stash(stash);
	return (line);
}

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	int		len;
	char	*last_stash;

	i = 0;
	j = 0;
	len = ft_strlen(stash);
	if (stash == NULL)
		return (stash);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (i == len || (len == 1 && i == 0) || ((i + 1) == len))
	{
		free(stash);
		stash = NULL;
		return (stash);
	}
	while (stash[i + j])
		j++;
	last_stash = (char *)ft_calloc(sizeof(char), j + 1);
	ft_memcpy(last_stash, &stash[i + 1], j - 1);
	last_stash[j] = '\0';
	free(stash);
	return (last_stash);
}

char	*keep_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (stash == NULL)
		return (stash);
	else if (!ft_strchr(stash, '\n'))
		return (ft_strdup(stash));
	else
		while (stash[i] != '\n')
			i++;
	i++;
	line = (char *)ft_calloc(sizeof(char), i + 1);
	if (!line)
		return (NULL);
	while (i > j)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*read_file(int fd, char *stash)
{
	int		bytes;
	char	*buffer;

	buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!stash || !buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0 || !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < BUFFER_SIZE && bytes != 0)
			buffer[bytes] = '\0';
		else if (bytes == 0 && (!ft_strlen(stash)) > 0)
		{
			free(stash);
			stash = NULL;
			break ;
		}
		if (bytes != 0)
			stash = ft_strjoin_custom(stash, buffer);
		if (ft_strchr(stash, '\n') || bytes < BUFFER_SIZE)
			break ;
	}
	return (free(buffer), stash);
}

/*
int	main(void)
{
	int		fd;
	char	*buffer;
	int	i = 0;

	fd = open("test1.txt", O_RDONLY);
	if (fd == -1)
		return (0);
	do
	{
		buffer = get_next_line(fd);
		printf("%s", buffer);
		free(buffer);
		i++;
	} while (i <= 33);
	// buffer = get_next_line(fd);
	// printf("%s", buffer);
	// free(buffer);
	close(fd);
	return (0);
}
	*/