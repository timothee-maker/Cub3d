/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:53:37 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 15:53:54 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_player *player, t_parse *parse, float start_x, int i,
		t_cimg *image)
{
	t_ray	ray;
	t_pixel	tex;
	int		screen_x;

	ray.ray_dir_x = cos(start_x);
	ray.ray_dir_y = sin(start_x);
	ray.pos_x = player->x;
	ray.pos_y = player->y;
	ray.cos_angle = ray.ray_dir_x;
	ray.sin_angle = ray.ray_dir_y;
	ray.index = -1;
	while (!touch(ray.pos_x, ray.pos_y, parse))
	{
		if (DEBUG)
			put_pixel(ray.pos_x, ray.pos_y, 0xFF0000, image);
		ray.pos_x += ray.cos_angle;
		ray.pos_y += ray.sin_angle;
	}
	if (!DEBUG)
	{
		cast_ray(parse, player, &ray);
		ray.dist = fixed_dist(player->x, player->y, ray.pos_x, ray.pos_y,
				parse);
		ray.height = (BLOCK / ray.dist) * (WIDTH / 2);
		ray.start_y = (HEIGHT - ray.height) / 2;
		ray.end = ray.start_y + ray.height;
		set_texture(parse, &ray, player, &tex);
		while (++ray.index < HEIGHT)
		{
			screen_x = WIDTH - i - 1;
			if (ray.index < ray.start_y)
				put_pixel(screen_x, ray.index, 0xFFA500, image);
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
				put_pixel(screen_x, ray.index, tex.color, image);
			}
			else
				put_pixel(screen_x, ray.index, 0xADD8E6, image);
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