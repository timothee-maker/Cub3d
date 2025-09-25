/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:11 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/25 11:56:41 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_loop(t_game *game);

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Must have 2 arguments\n"), 0);
	init_mlx(&game);
	parse_args(av[1], &game);
	set_mlx(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	t_index		index;
	t_cimg		image;

	init_index(&index);
	init_img(game, &image);
	clear_image(&image);
	player = &game->player;
	index.start_x = player->angle - PI / 6;
	fraction = PI / 3 / WIDTH;
	move_player(player);
	if (BONUS)
		minimap(game, &image, player);
	index.i = 0;
	while (index.i < WIDTH)
	{
		draw_line(player, game, &index, &image);
		index.start_x += fraction;
		index.i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
	return (0);
}
