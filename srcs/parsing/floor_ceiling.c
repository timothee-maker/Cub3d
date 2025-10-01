/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:16:53 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/01 11:40:49 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	valid_number(char *str)
{
	long long	val;
	int			j;
	int			i;

	i = 0;
	j = 1;
	val = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[i] == '-')
			j *= -1;
		i++;
	}
	if (str[i] == '\0')
		return (false);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		val = val * 10 + (str[i] - '0');
		if ((j == 1 && val > INT_MAX) || (j == -1 && (-val) < INT_MIN - 1))
			return (false);
		i++;
	}
	return (true);
}

int	check_rgb(char *rgb)
{
	int	i;

	i = 0;
	while (rgb[i] && (rgb[i] == ' ' || rgb[i] == '\t'))
		i++;
	if (!valid_number(&rgb[i]))
		return (free(rgb), err_msg("RGB must be lower than 2147483647\n", 0));
	if (ft_atoi(&rgb[i]) < 0)
		return (free(rgb), err_msg("RGB must be greater than 0\n", 0));
	return (free(rgb), 1);
}

int	fill_view_texture(t_texinfo *texinfo, char *map, int j)
{
	if (map[j] == 'C' && !texinfo->ceiling)
		texinfo->ceiling = get_view(map, j + 1);
	else if (map[j] == 'F' && !texinfo->floor)
		texinfo->floor = get_view(map, j + 1);
	else
		return (0);
	return (1);
}
