/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:53:37 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/25 11:34:10 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_parameters(t_ray *ray, t_player *player, t_game *parse);
static void	find_wall(t_ray *ray, t_cimg *image, t_game *parse);
void		minimap(t_game *parse, t_cimg *image, t_player *player);

void	draw_line(t_player *player, t_game *parse, t_index *index,
		t_cimg *image)
{
	t_ray	ray;
	t_pixel	tex;

	init_ray(&ray, player, index->start_x, index->i);
	find_wall(&ray, image, parse);
	cast_ray(parse, player, &ray);
	set_parameters(&ray, player, parse);
	set_texture(parse, &ray, player, &tex);
	while (++ray.index < HEIGHT)
	{
		if (ray.index < ray.start_y)
			put_pixel(ray.rev_screen, ray.index, 0xADD8E6, image);
		else if (ray.index < ray.end)
		{
			get_color_pixel(&tex, parse);
			put_pixel(ray.rev_screen, ray.index, tex.color, image);
		}
		else
			put_pixel(ray.rev_screen, ray.index, 0x228B22, image);
	}
}

static void	find_wall(t_ray *ray, t_cimg *image, t_game *parse)
{
	while (!touch(ray->pos_x, ray->pos_y, parse))
	{
		if (BONUS)
			put_pixel(ray->pos_x, ray->pos_y, 0xFF0000, image);
		ray->pos_x += ray->cos_angle;
		ray->pos_y += ray->sin_angle;
	}
}

static void	set_parameters(t_ray *ray, t_player *player, t_game *parse)
{
	ray->dist = fixed_dist(ray->pos_x - player->x, ray->pos_y - player->y,
			parse);
	ray->height = (BLOCK / ray->dist) * (WIDTH / 2);
	ray->start_y = (HEIGHT - ray->height) / 2;
	ray->end = ray->start_y + ray->height;
}

void	minimap(t_game *parse, t_cimg *image, t_player *player)
{
	draw_map(parse, image);
	draw_square(player->x, player->y, 10, image);
}
