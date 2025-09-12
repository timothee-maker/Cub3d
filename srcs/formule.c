/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:47:19 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 09:47:10 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(float px, float py, t_parse *parse)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	// printf("[%d][%d][%f][%f]\n", x, y, px, py);
	if (parse->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	// printf("x[%f]y[%f]", x, y);
	// printf("sqrt[%f]", sqrt(x * x + y * y));
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_parse *parse)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	// (void)parse;
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	// printf("[%f][%f]", delta_x, delta_y);
	angle = atan2(delta_y, delta_x) - parse->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_square(int x, int y, int size, int color, t_cimg *image)
{
	int	i;

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


int	cast_ray(t_parse *parse, t_player *player, t_ray *ray)
{

	int		hit;

	// position de départ (case de la grille)
	ray->map_x = (int)(player->x / BLOCK);
	ray->map_y = (int)(player->y / BLOCK);
	// longueur du rayon pour traverser une case en X ou Y
	ray->deltaDistX = fabs(1 / ray->cos_angle);
	ray->deltaDistY = fabs(1 / ray->sin_angle);
	// calcul de step et sideDist
	if (ray->cos_angle < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->x / BLOCK - ray->map_x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->map_x + 1.0 - player->x / BLOCK) * ray->deltaDistX;
	}
	if (ray->sin_angle < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->y / BLOCK - ray->map_y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->map_y + 1.0 - player->y / BLOCK) * ray->deltaDistY;
	}
	// DDA loop
	hit = 0;
	while (!hit)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->map_x += ray->stepX;
			ray->side = 0; // mur vertical (Est/Ouest)
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->map_y += ray->stepY;
			ray->side = 1; // mur horizontal (Nord/Sud)
		}
		if (parse->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (parse->map[ray->map_y][ray->map_x]); // retourne le numéro du mur
}
