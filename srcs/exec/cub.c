/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:53:37 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/02 11:47:25 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_parameters(t_ray *ray, t_player *player, t_game *game);
static void	find_wall(t_ray *ray, t_cimg *image, t_game *game);
void		minimap(t_game *game, t_cimg *image, t_player *player);

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
	(void)game;
	if (ray->side == 0)
		ray->dist = (ray->map_x - (player->x / 64.0f) + (1 - ray->stepx) * 0.5f)
			/ ray->ray_dir_x;
	else
		ray->dist = (ray->map_y - (player->y / 64.0f) + (1 - ray->stepy) * 0.5f)
			/ ray->ray_dir_y;
	ray->height = (int)(HEIGHT / ray->dist);
	ray->start_y = -ray->height / 2 + HEIGHT / 2;
	if (ray->start_y < 0)
		ray->start_y = 0;
	ray->end = ray->height / 2 + HEIGHT / 2;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
}

void	minimap(t_game *game, t_cimg *image, t_player *player)
{
	draw_map(game, image);
	draw_square(player->x, player->y, 10, image);
}

// static void	set_parameters(t_ray *ray, t_player *player, t_game *game)
// {
// 	ray->dist = fixed_dist(ray->pos_x - player->x, ray->pos_y - player->y,
// 			game);
// 	ray->height = (BLOCK / ray->dist) * (WIDTH / 2);
// 	ray->start_y = (HEIGHT - ray->height) / 2;
// 	ray->end = ray->start_y + ray->height;
// }
