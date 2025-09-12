/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:16:50 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/09 10:37:36 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_win(t_parse *parse)
{
	// mlx_destroy_image(parse->mlx, &parse->img.img);
	mlx_destroy_window(parse->mlx, parse->win);
	mlx_destroy_display(parse->mlx);
	free(parse->map);
	free(parse->mlx);
	parse->mlx = NULL;
	exit(0);
}	

int	close_window(t_parse *parse)
{
	destroy_win(parse);
	return (0);
}

int	key_hook(int keycode, t_parse *parse)
{
	if (keycode == 65307)
		destroy_win(parse);
	return (0);
}