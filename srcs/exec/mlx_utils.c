/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:01:41 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/23 16:12:07 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_mlx(t_game *game)
{
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
	load_img(game, &game->texture[0], game->texinfo.north);
	load_img(game, &game->texture[1], game->texinfo.south);
	load_img(game, &game->texture[2], game->texinfo.east);
	load_img(game, &game->texture[3], game->texinfo.west);
	free_tex(&game->texinfo);
}

void	load_img(t_game *game, t_cimg *texture, char *str)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, str, &texture->width,
			&texture->height);
	if (!texture->img)
		exit(0);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		exit(0);
}

void	clear_image(t_cimg *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_pixel(i, j, 0, img);
			j++;
		}
		i++;
	}
}

void	put_pixel(int x, int y, int color, t_cimg *img)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * img->line_length + x * img->bits_per_pixel / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}

int	get_pixel(t_cimg *t, int x, int y)
{
	int				idx;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	idx = y * t->line_length + x * (t->bits_per_pixel / 8);
	r = t->addr[idx];
	g = t->addr[idx + 1];
	b = t->addr[idx + 2];
	return (r | (g << 8) | (b << 16));
}
