/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:37:28 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/02 11:11:20 by tnolent          ###   ########.fr       */
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

void	init_fov(t_fov *fov, t_player *player)
{
	fov->fov_radian = FOV * (PI / 180.0f);
	fov->camera_planelenght = tan(fov->fov_radian / 2.0f);
	fov->camera_planex = -sin(player->angle) * fov->camera_planelenght;
	fov->camera_planey = cos(player->angle) * fov->camera_planelenght;
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
	init_fov(&game->fov, &game->player);
}

int is_wall(t_game *game, float x, float y)
{
    int map_x = (int)(x / BLOCK);
    int map_y = (int)(y / BLOCK);

    if (game->map[map_y][map_x] == '1')
        return (1);
    return (0);
}

void handle_position(t_game *game, t_player *player, float cos_angle, float sin_angle)
{
    float new_x;
    float new_y;

    if (player->k_up)
    {
        new_x = player->x + cos_angle * SPEED;
        new_y = player->y + sin_angle * SPEED;
        if (!is_wall(game, new_x, new_y))
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->k_down)
    {
        new_x = player->x - cos_angle * SPEED;
        new_y = player->y - sin_angle * SPEED;
        if (!is_wall(game, new_x, new_y))
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->k_left)
    {
        new_x = player->x + sin_angle * SPEED;
        new_y = player->y - cos_angle * SPEED;
        if (!is_wall(game, new_x, new_y))
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->k_right)
    {
        new_x = player->x - sin_angle * SPEED;
        new_y = player->y + cos_angle * SPEED;
        if (!is_wall(game, new_x, new_y))
        {
            player->x = new_x;
            player->y = new_y;
        }
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

void	move_player(t_game *game, t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	handle_angle(player);
	handle_position(game, player, cos_angle, sin_angle);
}
