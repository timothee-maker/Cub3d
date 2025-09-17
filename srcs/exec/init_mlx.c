/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:57:36 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/17 11:30:00 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_game *parse)
{
	parse->mlx = NULL;
	parse->win = NULL;
	init_player(&parse->player);
	parse->map = NULL;
	init_mapinfo(&parse->mapinfo);
}

void	init_texture_img(t_game *parse, t_cimg *image, char *path)
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

void	init_img(t_game *parse, t_cimg *image)
{
	init_img_clean(image);
	image->img = mlx_new_image(parse->mlx, WIDTH, HEIGHT);
	if (image->img == NULL)
		exit(0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}
