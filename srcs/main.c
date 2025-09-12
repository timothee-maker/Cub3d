/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:11 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 13:06:01 by tnolent          ###   ########.fr       */
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

void	load_img(t_parse *parse, t_cimg *texture, char *str)
{
	texture->img = mlx_xpm_file_to_image(parse->mlx, str, &texture->width,
			&texture->height);
	// if (!texture->img)
	// 	print_error(parse, "chargement de l'image.", -1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	// if (!texture->addr)
	// 	print_error(parse, "chargement de l'image.", -1);
}

void	set_mlx(t_parse *parse)
{
	// proteger les malloc
	parse->map = get_map();
	parse->mlx = mlx_init();
	parse->win = mlx_new_window(parse->mlx, WIDTH, HEIGHT, "Cub3d");
	load_img(parse, &parse->texture[0], "img1.xpm");
	load_img(parse, &parse->texture[1], "img1.xpm");
	load_img(parse, &parse->texture[2], "chat.xpm");
	load_img(parse, &parse->texture[3], "chat.xpm");
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

int	find_face(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->ray_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
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

void	set_texture(t_parse *parse, t_ray *ray, t_player *player, t_pixel *tex)
{
	init_tex(tex, ray);
	if (ray->side == 0) // mur vertical
		ray->corrected_dist = (ray->map_x - player->x / 64.0f + (1
					- ray->cos_angle) / 2) / ray->ray_x;
	else // mur horizontal
		ray->corrected_dist = (ray->map_y - player->y / 64.0f + (1
					- ray->sin_angle) / 2) / ray->ray_y;
	if (ray->side == 0) // mur vertical
		tex->wall_x = player->y / 64.0f + ray->corrected_dist * ray->ray_y;
	else // mur horizontal
		tex->wall_x = player->x / 64.0f + ray->corrected_dist * ray->ray_x;
	tex->wall_x -= floor(tex->wall_x);
	tex->tex_x = (int)(tex->wall_x * (float)(parse->texture[tex->face].width));
	if ((ray->side == 0 && ray->ray_x > 0) || (ray->side == 1
			&& ray->ray_y < 0))
		tex->tex_x = parse->texture[tex->face].width - tex->tex_x - 1;
	tex->step = (float)parse->texture[tex->face].height / ray->height;
	tex->tex_pos = (tex->start_y - HEIGHT / 2 + ray->height / 2) * tex->step;
}

void	draw_line(t_player *player, t_parse *parse, float start_x, int i,
		t_cimg *image)
{
	t_ray	ray;
	t_pixel	tex;

	ray.cos_angle = cos(start_x);
	ray.sin_angle = sin(start_x);
	ray.ray_x = player->x;
	ray.ray_y = player->y;
	ray.index = -1;
	while (!touch(ray.ray_x, ray.ray_y, parse))
	{
		if (DEBUG)
			put_pixel(ray.ray_x, ray.ray_y, 0xFF0000, image);
		ray.ray_x += ray.cos_angle;
		ray.ray_y += ray.sin_angle;
	}
	if (!DEBUG)
	{
		cast_ray(parse, player, &ray);
		ray.dist = fixed_dist(player->x, player->y, ray.ray_x, ray.ray_y,
				parse);
		ray.height = (BLOCK / ray.dist) * (WIDTH / 2);
		ray.start_y = (HEIGHT - ray.height) / 2;
		ray.end = ray.start_y + ray.height;
		set_texture(parse, &ray, player, &tex);
		while (++ray.index < HEIGHT)
		{
			if (ray.index < ray.start_y)
				put_pixel(i, ray.index, 0xFFA500, image); // plafond
			else if (ray.index < ray.end)
			{
				tex.tex_y = (int)tex.tex_pos;
				if (tex.tex_y < 0)
					tex.tex_y = 0;
				else if (tex.tex_y >= parse->texture[tex.face].height)
					tex.tex_y = parse->texture[tex.face].height - 1;
				tex.tex_pos += tex.step;
				tex.color = get_pixel(&parse->texture[tex.face], tex.tex_x,
						tex.tex_y);
				put_pixel(i, ray.index, tex.color, image);
				// ray.color = get_side_color(ray.side, ray.cos_angle,
				// 		ray.sin_angle);
				// put_pixel(i, ray.index, ray.color, image); // mur
			}
			else
				put_pixel(i, ray.index, 0xADD8E6, image); // sol
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

	init_img(parse, &image);
	clear_image(&image);
	player = &parse->player;
	start_x = player->angle - PI / 6;
	fraction = PI / 3 / WIDTH;
	move_player(player);
	if (DEBUG)
	{
		draw_map(parse, &image);
		draw_square(player->x, player->y, 10, 0x00FF00, &image);
	}
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, parse, start_x, i++, &image);
		start_x += fraction;
	}
	mlx_put_image_to_window(parse->mlx, parse->win, image.img, 0, 0);
	mlx_destroy_image(parse->mlx, image.img);
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
