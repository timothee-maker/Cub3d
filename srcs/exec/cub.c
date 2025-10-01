/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:53:37 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/01 11:12:29 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_parameters(t_ray *ray, t_player *player, t_game *game);
static void	find_wall(t_ray *ray, t_cimg *image, t_game *game);
void		minimap(t_game *game, t_cimg *image, t_player *player);

int	create_rgb(t_game *game, int i)
{
	int	r;
	int	g;
	int	b;

	if (i == 1)
	{
		r = game->texinfo.ceiling[0];
		g = game->texinfo.ceiling[1];
		b = game->texinfo.ceiling[2];
	}
	else
	{
		r = game->texinfo.floor[0];
		g = game->texinfo.floor[1];
		b = game->texinfo.floor[2];
	}
	return ((r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16));
}

void	draw_line(t_player *player, t_game *game, t_index *index, t_cimg *image)
{
	t_ray	ray;
	t_pixel	tex;

	init_ray(&ray, player, index->start_x, index->i);
	find_wall(&ray, image, game);
	cast_ray(game, player, &ray);
	set_parameters(&ray, player, game);
	set_texture(game, &ray, player, &tex);
	if (!BONUS)
	{
		while (++ray.index < HEIGHT)
		{
			if (ray.index < ray.start_y)
				put_pixel(ray.rev_screen, ray.index, create_rgb(game, 1),
					image);
			else if (ray.index < ray.end)
			{
				get_color_pixel(&tex, game);
				put_pixel(ray.rev_screen, ray.index, tex.color, image);
			}
			else
				put_pixel(ray.rev_screen, ray.index, create_rgb(game, 2),
					image);
		}
	}
}

static void	find_wall(t_ray *ray, t_cimg *image, t_game *game)
{
	while (!touch(ray->pos_x, ray->pos_y, game))
	{
		if (BONUS)
			put_pixel(ray->pos_x, ray->pos_y, 0xFF0000, image);
		ray->pos_x += ray->cos_angle;
		ray->pos_y += ray->sin_angle;
	}
}

static void	set_parameters(t_ray *ray, t_player *player, t_game *game)
{
	ray->dist = fixed_dist(ray->pos_x - player->x, ray->pos_y - player->y,
			game);
	ray->height = (BLOCK / ray->dist) * (WIDTH / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end = ray->start_y + ray->height;
}

void	minimap(t_game *game, t_cimg *image, t_player *player)
{
	draw_map(game, image);
	draw_square(player->x, player->y, 10, image);
}
