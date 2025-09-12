/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:19:54 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 15:58:59 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(t_parse *parse, t_ray *ray, t_player *player, t_pixel *tex)
{
	init_tex(tex, ray);
	if (ray->side == 0) // mur vertical
		ray->corrected_dist = (ray->map_x - player->x / 64.0f + (1 - ray->stepX)
				/ 2) / ray->ray_dir_x;
	else // mur horizontal
		ray->corrected_dist = (ray->map_y - player->y / 64.0f + (1 - ray->stepY)
				/ 2) / ray->ray_dir_y;
	// Calcul du point d'impact sur le mur
	if (ray->side == 0) // mur vertical
		tex->wall_x = player->y / 64.0f + ray->corrected_dist * ray->ray_dir_y;
	else // mur horizontal
		tex->wall_x = player->x / 64.0f + ray->corrected_dist * ray->ray_dir_x;
	tex->wall_x -= floor(tex->wall_x);
	tex->tex_x = (int)(tex->wall_x * (float)(parse->texture[tex->face].width));
	// Correction du flip de texture
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex->tex_x = parse->texture[tex->face].width - tex->tex_x - 1;
	tex->step = (float)parse->texture[tex->face].height / ray->height;
	tex->tex_pos = (tex->start_y - HEIGHT / 2 + ray->height / 2) * tex->step;
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

// int	get_side_color(int side, float cos_angle, float sin_angle)
// {
// 	if (side == 0)
// 	{
// 		if (cos_angle > 0)
// 			return (0x00FF00);
// 		else
// 			return (0xFF00FF);
// 	}
// 	else
// 	{
// 		if (sin_angle > 0)
// 			return (255);
// 		else
// 			return (0xFF0000);
// 	}
// }