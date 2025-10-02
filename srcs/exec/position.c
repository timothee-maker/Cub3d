/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:26:59 by barnaud           #+#    #+#             */
/*   Updated: 2025/10/01 11:31:23 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_up(t_game *game, t_player *player, float cos_angle,
		float sin_angle)
{
	float	new_x;
	float	new_y;

	new_x = player->x + cos_angle * SPEED;
	new_y = player->y + sin_angle * SPEED;
	if (!is_wall(game, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static void	move_down(t_game *game, t_player *player, float cos_angle,
		float sin_angle)
{
	float	new_x;
	float	new_y;

	new_x = player->x - cos_angle * SPEED;
	new_y = player->y - sin_angle * SPEED;
	if (!is_wall(game, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static void	move_left(t_game *game, t_player *player, float cos_angle,
		float sin_angle)
{
	float	new_x;
	float	new_y;

	new_x = player->x + sin_angle * SPEED;
	new_y = player->y - cos_angle * SPEED;
	if (!is_wall(game, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static void	move_right(t_game *game, t_player *player, float cos_angle,
		float sin_angle)
{
	float	new_x;
	float	new_y;

	new_x = player->x - sin_angle * SPEED;
	new_y = player->y + cos_angle * SPEED;
	if (!is_wall(game, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	handle_position(t_game *game, t_player *player, float cos_angle,
		float sin_angle)
{
	if (player->k_up)
		move_up(game, player, cos_angle, sin_angle);
	if (player->k_down)
		move_down(game, player, cos_angle, sin_angle);
	if (player->k_left)
		move_left(game, player, cos_angle, sin_angle);
	if (player->k_right)
		move_right(game, player, cos_angle, sin_angle);
}
