/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:16:50 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/18 10:32:12 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_win(t_game *parse)
{
	mlx_destroy_image(parse->mlx, parse->texture[0].img);
	mlx_destroy_image(parse->mlx, parse->texture[1].img);
	mlx_destroy_image(parse->mlx, parse->texture[2].img);
	mlx_destroy_image(parse->mlx, parse->texture[3].img);
	mlx_destroy_window(parse->mlx, parse->win);
	mlx_destroy_display(parse->mlx);
	free(parse->map);
	free(parse->mlx);
	parse->mlx = NULL;
	exit(0);
}

int	close_window(t_game *parse)
{
	destroy_win(parse);
	return (0);
}

int	key_hook(int keycode, t_game *parse)
{
	if (keycode == 65307)
		destroy_win(parse);
	return (0);
}

int	key_press(int keycode, t_game *parse)
{
	t_player	*player;

	player = NULL;
	player = &parse->player;
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
		destroy_win(parse);
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
