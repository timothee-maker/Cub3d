/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:57:36 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/06 10:15:06 by tnolent          ###   ########.fr       */
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
	if (!image->img)
		destroy_win(game, 0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	if (!image->addr)
	{
		mlx_destroy_image(game->mlx, image->img);
		destroy_win(game, 0);
	}
	return ;
}
