/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:40:07 by barnaud           #+#    #+#             */
/*   Updated: 2025/10/01 11:40:41 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_next_rgb_value(char *rgb, int *start)
{
	int	end;
	int	value;

	end = *start;
	while (rgb[end] && rgb[end] != '\n' && rgb[end] != ',')
		end++;
	if (!check_rgb(ft_substr(rgb, *start, end - *start)))
		return (-1);
	value = ft_atoi_free(ft_substr(rgb, *start, end - *start));
	if (rgb[end] == ',')
		end++;
	*start = end;
	return (value);
}

static int	check_rgb_line_end(char *rgb, int end)
{
	while (rgb[end])
	{
		if (rgb[end] != ' ' && rgb[end] != '\t' && rgb[end] != '\n')
			return (0);
		end++;
	}
	return (1);
}

int	*get_view(char *rgb, int i)
{
	int	start;
	int	l;
	int	tmp_rslt;
	int	*result;

	result = malloc(sizeof(int) * 3);
	if (!result)
		return (err_msg(ERR_MALLOC, 0), NULL);
	while (rgb[i] && (rgb[i] == ' ' || rgb[i] == '\t' || rgb[i] == '\n'))
		i++;
	start = i;
	l = 0;
	while (rgb[start] && (rgb[start] != '\n') && l < 3)
	{
		tmp_rslt = get_next_rgb_value(rgb, &start);
		if (tmp_rslt == -1)
			return (free(result), NULL);
		result[l++] = tmp_rslt;
	}
	if (!check_rgb_line_end(rgb, start))
		return (free(result), NULL);
	return (result);
}
