/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:37:28 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/02 11:49:40 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
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

void	move_player(t_game *game, t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	handle_angle(player);
	handle_position(game, player, cos_angle, sin_angle);
}
