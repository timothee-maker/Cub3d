/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:47:19 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/08 16:19:34 by tnolent          ###   ########.fr       */
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


int	cast_ray(t_parse *parse, t_player *player, float rayDirX, float rayDirY,
		int *side)
{
	int		mapX;
	int		mapY;
	float	deltaDistX;
	float	deltaDistY;
	int		hit;

	// position de départ (case de la grille)
	mapX = (int)(player->x / BLOCK);
	mapY = (int)(player->y / BLOCK);
	// longueur du rayon pour traverser une case en X ou Y
	deltaDistX = fabs(1 / rayDirX);
	deltaDistY = fabs(1 / rayDirY);
	// calcul de step et sideDist
	int stepX, stepY;
	float sideDistX, sideDistY;
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (player->x / BLOCK - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - player->x / BLOCK) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (player->y / BLOCK - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - player->y / BLOCK) * deltaDistY;
	}
	// DDA loop
	hit = 0;
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			*side = 0; // mur vertical (Est/Ouest)
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			*side = 1; // mur horizontal (Nord/Sud)
		}
		if (parse->map[mapY][mapX] == '1')
			hit = 1;
	}
	return (parse->map[mapY][mapX]); // retourne le numéro du mur
}
