/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:13:40 by barnaud           #+#    #+#             */
/*   Updated: 2025/10/01 11:15:16 by barnaud          ###   ########.fr       */
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
