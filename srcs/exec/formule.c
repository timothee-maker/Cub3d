/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:47:19 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/15 15:29:12 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(float px, float py, t_game *parse)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (parse->map[y][x] == '1')
		return (true);
	return (false);
}

float	fixed_dist(float delta_x, float delta_y, t_game *parse)
{
	float	angle;
	float	fix_dist;

	angle = atan2(delta_y, delta_x) - parse->player.angle;
	fix_dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_square(int x, int y, int size, t_cimg *image)
{
	int	i;
	int	color;

	color = 255;
	i = 0;
	while (i < size)
		put_pixel(x + i++, y, color, image);
	i = 0;
	while (i < size)
		put_pixel(x, y + i++, color, image);
	i = 0;
	while (i < size)
		put_pixel(x + size, i++ + y, color, image);
	i = 0;
	while (i < size)
		put_pixel(x + i++, y + size, color, image);
}

static void	init_ray_dda(t_player *player, t_ray *ray)
{
	ray->map_x = (int)(player->x / BLOCK);
	ray->map_y = (int)(player->y / BLOCK);
	ray->delta_dx = fabs(1 / ray->cos_angle);
	ray->delta_dy = fabs(1 / ray->sin_angle);
	if (ray->cos_angle < 0)
	{
		ray->stepx = -1;
		ray->side_dx = (player->x / BLOCK - ray->map_x) * ray->delta_dx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_dx = (ray->map_x + 1.0 - player->x / BLOCK) * ray->delta_dx;
	}
	if (ray->sin_angle < 0)
	{
		ray->stepy = -1;
		ray->side_dy = (player->y / BLOCK - ray->map_y) * ray->delta_dy;
	}
	else
	{
		ray->stepy = 1;
		ray->side_dy = (ray->map_y + 1.0 - player->y / BLOCK) * ray->delta_dy;
	}
}

int	cast_ray(t_game *parse, t_player *player, t_ray *ray)
{
	int	hit;

	init_ray_dda(player, ray);
	hit = 0;
	while (!hit)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->map_x += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->map_y += ray->stepy;
			ray->side = 1;
		}
		if (parse->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (parse->map[ray->map_y][ray->map_x]);
}
