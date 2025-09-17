/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:32:09 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 17:35:02 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_tex(t_pixel *tex, t_ray *ray)
{
	tex->color = 0;
	tex->face = find_face(ray);
	tex->start_y = (HEIGHT - ray->height) / 2;
	tex->end_y = tex->start_y + ray->height;
	tex->step = 0.0f;
	tex->tex_pos = 0.0f;
	tex->tex_x = 0;
	tex->wall_x = 0.0f;
	tex->tex_y = 0;
	tex->y = 0;
}

void	init_ray(t_ray *ray, t_player *player, float start_x, int x)
{
	ray->ray_dir_x = cos(start_x);
	ray->ray_dir_y = sin(start_x);
	ray->pos_x = player->x;
	ray->pos_y = player->y;
	ray->cos_angle = ray->ray_dir_x;
	ray->sin_angle = ray->ray_dir_y;
	ray->index = -1;
	ray->rev_screen = WIDTH - x - 1;
}
