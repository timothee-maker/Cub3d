/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:11 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/09 10:28:34 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_parse *parse)
{
	parse->mlx = NULL;
	parse->win = NULL;
	init_player(&parse->player);
	// init_texinfo(&parse->texinfo);
	parse->map = NULL;
	// init_mapinfo(&parse->mapinfo);
	// parse->texture_pixels = NULL;
	parse->textures = NULL;
}

void	init_texture_img(t_parse *parse, t_cimg *image, char *path)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(parse->mlx, path, &parse->tex_w,
			&parse->tex_h);
	if (image->img == NULL)
		exit(0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}

void	set_mlx(t_parse *parse)
{
	// proteger les malloc
	parse->map = get_map();
	parse->mlx = mlx_init();
	parse->win = mlx_new_window(parse->mlx, WIDTH, HEIGHT, "Cub3d");
	// parse->img = mlx_new_image(parse->mlx, WIDTH, HEIGHT);
	// parse->addr = mlx_get_data_addr(parse->img, &parse->bits_per_pixel,
	// 		&parse->line_length, &parse->endian);
}

void	init_img_clean(t_cimg *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	init_img(t_parse *parse, t_cimg *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(parse->mlx, width, height);
	if (image->img == NULL)
		exit(0);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}

static int	*xpm_to_img(t_parse	 *parse, char *path)
{
	t_cimg	tmp;
	int		*buffer;
	int		x;
	int		y;

	(void)path;
	init_texture_img(parse, &tmp, path);
	buffer = calloc(1, sizeof * buffer * 64 * 64);
	if (!buffer)
		exit(0);
	y = -1;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
			buffer[y * 64 + x] = tmp.addr[y * 64 + x];
	}
	mlx_destroy_image(parse->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_parse *parse)
{
	parse->textures = calloc(5, sizeof * parse->textures);
	if (!parse->textures)
		exit(1);
	parse->textures[0] = xpm_to_img(parse, "chat.xpm");
	parse->textures[1] = xpm_to_img(parse, "chat.xpm");
	parse->textures[2] = xpm_to_img(parse, "chat.xpm");
	parse->textures[3] = xpm_to_img(parse, "chat.xpm");
}

// int	pixel_color(t_parse *parse, int texX, int texY)
// {
// 	char	*pixel;

// 	pixel = parse->addr + (texY * parse->line_length + texX
// 			* (parse->bits_per_pixel / 8));
// 	return (*(int *)pixel);
// }

int	get_side_color(int side, float cos_angle, float sin_angle)
{
	if (side == 0)
	{
		if (cos_angle > 0)
			return (0x00FF00);
		else
			return (0xFF00FF);
	}
	else
	{
		if (sin_angle > 0)
			return (255);
		else
			return (0xFF0000);
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

void	set_image_pixel(t_cimg *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_length / 4) + x;
	image->addr[pixel] = color;
}

void	draw_line(t_player *player, t_parse *parse, float start_x, int i, t_cimg *image)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		side;
	int		color;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, parse))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, image);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, parse);
		height = (BLOCK / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;
		cast_ray(parse, player, cos_angle, sin_angle, &side);
		// dessiner
		while (start_y < end)
		{
			// color = pixel_color(parse, texX, texY);
			color = get_side_color(side, cos_angle, sin_angle);
			put_pixel(i, start_y++, color, image);
			// set_image_pixel(&image, i, start_y++, color);
		}
	}
}

int	draw_loop(t_parse *parse)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;
	t_cimg		image;

	init_img(parse, &image, WIDTH, HEIGHT);
	clear_image(&image);
	player = &parse->player;
	start_x = player->angle - PI / 6;
	fraction = PI / 3 / WIDTH;
	move_player(player);
	// // printf("[%f]", player->angle);
	// if (DEBUG)
	// {
	// 	draw_map(parse, &image);
	// 	draw_square(player->x, player->y, 10, 0x00FF00, &image);
	// }
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, parse, start_x, i++, &image);
		start_x += fraction;
	}
	mlx_put_image_to_window(parse->mlx, parse->win, image.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_parse	parse;

	init_mlx(&parse);
	set_mlx(&parse);
	mlx_hook(parse.win, 2, 1L << 0, key_press, &parse);
	mlx_hook(parse.win, 3, 1L << 1, key_release, &parse.player);
	mlx_loop_hook(parse.mlx, draw_loop, &parse);
	mlx_hook(parse.win, 17, 0, close_window, &parse);
	mlx_loop(parse.mlx);
	return (0);
}
