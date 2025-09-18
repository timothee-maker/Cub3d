/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:24:26 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/18 10:48:23 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// void	verify_file(int fd)
// {
// 	char	*line;
// 	t_check	check;

// 	init_check(&check);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (!analyse_line(line, &check))
// 		{
// 			free(line);
// 			close(fd);
// 			exit(0);
// 		}
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// }

// int	is_check(t_check *check)
// {
// 	static int	j = 0;
// 	int			i;

// 	i = 0;
// 	if (check->NO == 1)
// 		i++;
// 	if (check->SO == 1)
// 		i++;
// 	if (check->EA == 1)
// 		i++;
// 	if (check->WE == 1)
// 		i++;
// 	if (check->C == 1)
// 		i++;
// 	if (check->F == 1)
// 		i++;
// 	if (j == i)
// 		return (0);
// 	j = i;
// 	return (i);
// }

// int	analyse_line(char *line, t_check *check)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
		// if (line[i] == 'N' && line[i + 1] == 'O')
		// 	check->NO = 1;
		// else if (line[i] == 'S' && line[i + 1] == 'O')
		// 	check->SO = 1;
		// else if (line[i] == 'E' && line[i + 1] == 'A')
		// 	check->EA = 1;
		// else if (line[i] == 'W' && line[i + 1] == 'E')
		// 	check->WE = 1;
		// else if (line[i] == 'C')
		// 	check->C = 1;
		// else if (line[i] == 'F')
		// 	check->F = 1;
// 		i++;
// 	}
// 	if (is_check(check))
// 		return (1);
// 	return (1);
// }
