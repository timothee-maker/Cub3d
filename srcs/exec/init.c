/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:57:36 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 15:22:00 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_parse *parse)
{
	parse->mlx = NULL;
	parse->win = NULL;
	init_player(&parse->player);
	parse->map = NULL;
}

void	init_texture_img(t_parse *parse, t_cimg *image, char *path)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(parse->mlx, path, &parse->img.width,
			&parse->img.height);
	if (image->img == NULL)
		exit(0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}

void	init_img_clean(t_cimg *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	init_img(t_parse *parse, t_cimg *image)
{
	init_img_clean(image);
	image->img = mlx_new_image(parse->mlx, WIDTH, HEIGHT);
	if (image->img == NULL)
		exit(0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}

void	init_tex(t_pixel *tex, t_ray *ray)
{
	tex->color = 0;
	tex->face = find_face(ray);
	tex->start_y = (HEIGHT - ray->height) / 2;
	tex->end_y = tex->start_y + ray->height;
	tex->step = 0.0f;
	tex->tex_pos = 0.0f;
	tex->tex_x = 0;
	tex->tex_y = 0;
	tex->wall_x = 0.0f;
	tex->y = 0;
}
