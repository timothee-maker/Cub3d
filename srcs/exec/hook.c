/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:16:50 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/26 10:57:42 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_win(t_game *game)
{
	mlx_destroy_image(game->mlx, game->texture[0].img);
	mlx_destroy_image(game->mlx, game->texture[1].img);
	mlx_destroy_image(game->mlx, game->texture[2].img);
	mlx_destroy_image(game->mlx, game->texture[3].img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_tab((void *)game->map);
	free(game->mlx);
	free(game->texinfo.ceiling);
	free(game->texinfo.floor);
	game->mlx = NULL;
	exit(0);
}

int	close_window(t_game *game)
{
	destroy_win(game);
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		destroy_win(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = NULL;
	player = &game->player;
	if (keycode == W)
		player->k_up = true;
	if (keycode == S)
		player->k_down = true;
	if (keycode == A)
		player->k_right = true;
	if (keycode == D)
		player->k_left = true;
	if (keycode == LEFT)
		player->r_right = true;
	if (keycode == RIGHT)
		player->r_left = true;
	if (keycode == ECHAP)
		destroy_win(game);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->k_up = false;
	if (keycode == S)
		player->k_down = false;
	if (keycode == A)
		player->k_right = false;
	if (keycode == D)
		player->k_left = false;
	if (keycode == LEFT)
		player->r_right = false;
	if (keycode == RIGHT)
		player->r_left = false;
	return (0);
}
