/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:57:36 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/03 15:00:34 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	game->texture[0].img = NULL;
	game->texture[1].img = NULL;
	game->texture[2].img = NULL;
	game->texture[3].img = NULL;
}

void	init_mlx(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	init_mapinfo(&game->mapinfo);
	init_texinfo(&game->texinfo);
	init_textures(game);
}

void	init_texture_img(t_game *game, t_cimg *image, char *path)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(game->mlx, path, &game->img.width,
			&game->img.height);
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

void	init_img(t_game *game, t_cimg *image)
{
	init_img_clean(image);
	image->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (image->img == NULL)
		exit(0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}
