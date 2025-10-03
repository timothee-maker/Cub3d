/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:56:18 by barnaud           #+#    #+#             */
/*   Updated: 2025/10/03 12:57:14 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_biggest_line(char **map, int start)
{
	int	biggest;
	int	j;
	int	len;

	biggest = 0;
	j = start;
	while (map[j])
	{
		len = ft_strlen(map[j]);
		if (len > biggest)
			biggest = len;
		j++;
	}
	return (biggest);
}

int	check_map_char(char c, int *flag)
{
	if (!ft_isdigit(c) && c != ' ' && c != '\t' && c != '\n')
	{
		if (ft_strchr("NSEW", c) && !*flag)
			*flag = 1;
		else
			return (0);
	}
	return (1);
}

int	check_map_lines(char **map, int start, int *flag, int *end)
{
	int	j;
	int	k;

	j = start;
	while (map[j])
	{
		k = -1;
		while (map[j][++k])
		{
			if (!check_map_char(map[j][k], flag))
				return (err_msg("Wrong element in map\n", 0));
			if (empty_line(map, j, k))
				break ;
		}
		if (empty_line(map, j, k))
			break ;
		j++;
	}
	*end = j;
	return (1);
}

int	check_map_user(int flag)
{
	if (!flag)
		return (err_msg("Miss user in map\n", 0));
	return (1);
}

int	check_map_after(char **map, int j, int k)
{
	while (map[j])
	{
		if (!empty_line(map, j++, k))
			return (err_msg("Map is not the last element in file\n", 0));
	}
	return (1);
}
