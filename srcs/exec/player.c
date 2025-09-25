/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:37:28 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/25 12:24:35 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pos_player(t_player *player, t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				player->dir = game->map[y][x];
				player->x = (x + 0.5) * BLOCK;
				player->y = (y + 0.5) * BLOCK;
			}
		}
	}
}

void	set_angle(t_player *player)
{
	if (player->dir == 'N')
		player->angle = PI * 1.5;
	if (player->dir == 'S')
		player->angle = PI / 2;
	if (player->dir == 'E')
		player->angle = 0;
	if (player->dir == 'W')
		player->angle = PI;
}

void	set_player(t_player *player, t_game *game)
{
	set_pos_player(player, game);
	set_angle(player);
	player->k_up = false;
	player->k_down = false;
	player->k_left = false;
	player->k_right = false;
	player->r_left = false;
	player->r_right = false;
}

void	handle_position(t_player *player, float cos_angle, float sin_angle)
{
	if (player->k_up)
	{
		player->x += cos_angle * SPEED;
		player->y += sin_angle * SPEED;
	}
	if (player->k_down)
	{
		player->x -= cos_angle * SPEED;
		player->y -= sin_angle * SPEED;
	}
	if (player->k_left)
	{
		player->x += sin_angle * SPEED;
		player->y -= cos_angle * SPEED;
	}
	if (player->k_right)
	{
		player->x -= sin_angle * SPEED;
		player->y += cos_angle * SPEED;
	}
}

void	handle_angle(t_player *player)
{
	if (player->r_left)
		player->angle -= ANGLE_SPEED;
	if (player->r_right)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_player(t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	handle_angle(player);
	handle_position(player, cos_angle, sin_angle);
}
