/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:11 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/18 10:32:31 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_loop(t_game *parse);

int	main(int ac, char **av)
{
	t_game	parse;

	// (void)ac;
	(void)av;
	if (ac < 0)
		return (0);
	init_mlx(&parse);
	parse_args(av[1], &parse);
	return (0);
	set_mlx(&parse);
	mlx_hook(parse.win, 2, 1L << 0, key_press, &parse);
	mlx_hook(parse.win, 3, 1L << 1, key_release, &parse.player);
	mlx_loop_hook(parse.mlx, draw_loop, &parse);
	mlx_hook(parse.win, 17, 0, close_window, &parse);
	mlx_loop(parse.mlx);
	return (0);
}

int	draw_loop(t_game *parse)
{
	t_player	*player;
	float		fraction;
	t_index		index;
	t_cimg		image;

	init_index(&index);
	init_img(parse, &image);
	clear_image(&image);
	player = &parse->player;
	index.start_x = player->angle - PI / 6;
	fraction = PI / 3 / WIDTH;
	move_player(player);
	if (BONUS)
		minimap(parse, &image, player);
	index.i = 0;
	while (index.i < WIDTH)
	{
		draw_line(player, parse, &index, &image);
		index.start_x += fraction;
		index.i++;
	}
	mlx_put_image_to_window(parse->mlx, parse->win, image.img, 0, 0);
	mlx_destroy_image(parse->mlx, image.img);
	return (0);
}
