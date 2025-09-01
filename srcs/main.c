/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:11 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/01 15:59:27 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_parse *parse)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * parse->line_length + x * parse->bits_per_pixel / 8;
	parse->addr[index] = color & 0xFF;
	parse->addr[index + 1] = (color >> 8) & 0xFF;
	parse->addr[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_parse *parse)
{
	int	i;

	i = 0;
	while (i < size)
		put_pixel(x + i++, y, color, parse);
	i = 0;
	while (i < size)
		put_pixel(x, y + i++, color, parse);
	i = 0;
	while (i < size)
		put_pixel(x + size, i++ + y, color, parse);
	i = 0;
	while (i < size)
		put_pixel(x + i++, y + size, color, parse);
}

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	set_mlx(t_parse *parse)
{
	init_player(&parse->player);
	parse->map = get_map();
	parse->mlx = mlx_init();
	parse->win = mlx_new_window(parse->mlx, WIDTH, HEIGHT, "Cub3d");
	parse->img = mlx_new_image(parse->mlx, WIDTH, HEIGHT);
	parse->addr = mlx_get_data_addr(parse->img, &parse->bits_per_pixel,
			&parse->line_length, &parse->endian);
}

void	clear_image(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_pixel(i, j, 0, parse);
			j++;
		}
		i++;
	}
}

void	draw_map(t_parse *parse)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = parse->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, parse);
			x++;
		}
		y++;
	}
}

bool	touch(float px, float py, t_parse *parse)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (parse->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_parse *parse)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - parse->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_player *player, t_parse *parse, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	int	j = 0;
	while (!touch(ray_x, ray_y, parse))
	{ 
		// && j == 100
		if (DEBUG)
		{
			j = 0;
			put_pixel(ray_x, ray_y, 0xFF0000, parse);
		}
		else if (j != 100)
			j++;
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	// if (touch(ray_x, ray_y, parse))
	// 	printf("[%f][%f]\n", ray_x, ray_y);
	if (!DEBUG)
	{
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, parse);
		height = (BLOCK / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 255, parse);
			start_y++;
		}
	}
}

int	draw_loop(t_parse *parse)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &parse->player;
	start_x = player->angle - PI / 6;
	fraction = PI / 3 / WIDTH;
	move_player(player);
	clear_image(parse);
	if (DEBUG)
	{
		draw_map(parse);
		draw_square(player->x, player->y, 10, 0x00FF00, parse);
	}
	i = 0;
	// usleep(100000);
	while (i < WIDTH)
	{
		draw_line(player, parse, start_x, i++);
		start_x += fraction;
	}
	mlx_put_image_to_window(parse->mlx, parse->win, parse->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_parse	parse;

	set_mlx(&parse);
	mlx_hook(parse.win, 2, 1L << 0, key_press, &parse.player);
	mlx_hook(parse.win, 3, 1L << 1, key_release, &parse.player);
	mlx_loop_hook(parse.mlx, draw_loop, &parse);
	mlx_put_image_to_window(parse.mlx, parse.win, parse.img, 0, 0);
	mlx_loop(parse.mlx);
	return (0);
}
