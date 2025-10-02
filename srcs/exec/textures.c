/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:19:54 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/02 11:53:49 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(t_game *parse, t_ray *ray, t_player *player, t_pixel *tex)
{
	init_tex(tex, ray);
	if (ray->side == 0)
		ray->dist = (ray->map_x - player->x / 64.0f + (1 - ray->stepx) / 2)
			/ ray->ray_dir_x;
	else
		ray->dist = (ray->map_y - player->y / 64.0f + (1 - ray->stepy) / 2)
			/ ray->ray_dir_y;
	if (ray->side == 0)
		tex->wall_x = player->y / 64.0f + ray->dist * ray->ray_dir_y;
	else
		tex->wall_x = player->x / 64.0f + ray->dist * ray->ray_dir_x;
	tex->wall_x -= floor(tex->wall_x);
	tex->tex_x = (int)(tex->wall_x * (float)(parse->texture[tex->face].width));
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex->tex_x = parse->texture[tex->face].width - tex->tex_x - 1;
	tex->step = (float)parse->texture[tex->face].height / ray->height;
	tex->tex_pos = (tex->start_y - (HEIGHT / 2) + ray->height / 2)
		* (int)tex->step;
}

void	get_color_pixel(t_pixel *tex, t_game *parse)
{
	tex->tex_y = (int)tex->tex_pos;
	if (tex->tex_y < 0)
		tex->tex_y = 0;
	else if (tex->tex_y >= parse->texture[tex->face].height)
		tex->tex_y = parse->texture[tex->face].height - 1;
	tex->tex_pos += tex->step;
	tex->color = get_pixel(&parse->texture[tex->face], tex->tex_x, tex->tex_y);
}

int	find_face(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

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

// void	set_texture(t_game *parse, t_ray *ray, t_player *player, t_pixel *tex)
// {
// 	init_tex(tex, ray);
// 	if (ray->side == 0)
// 		ray->corrected_dist = (ray->map_x - player->x / 64.0f + (1 - ray->stepx)
// 				/ 2) / ray->ray_dir_x;
// 	else
// 		ray->corrected_dist = (ray->map_y - player->y / 64.0f + (1 - ray->stepy)
// 				/ 2) / ray->ray_dir_y;
// 	if (ray->side == 0)
// 		tex->wall_x = player->y / 64.0f + ray->corrected_dist * ray->ray_dir_y;
// 	else
// 		tex->wall_x = player->x / 64.0f + ray->corrected_dist * ray->ray_dir_x;
// 	tex->wall_x -= floor(tex->wall_x);
// 	tex->tex_x = (int)(tex->wall_x * (float)(parse->texture[tex->face].width));
// 	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
// 			&& ray->ray_dir_y < 0))
// 		tex->tex_x = parse->texture[tex->face].width - tex->tex_x - 1;
// 	tex->step = (float)parse->texture[tex->face].height / ray->height;
// 	tex->tex_pos = (tex->start_y - (HEIGHT / 2) + ray->height / 2)
		// * (int)tex->step;
// }
