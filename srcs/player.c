/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:37:28 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 14:40:40 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI * 1.5;
	player->k_up = false;
	player->k_down = false;
	player->k_left = false;
	player->k_right = false;
	player->r_left = false;
	player->r_right = false;
}

int	key_press(int keycode, t_parse *parse)
{
	t_player *player = NULL;

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

void	move_player(t_player *player)
{
	int speed;
	float angle_speed;
	float cos_angle;
	float sin_angle;

	angle_speed = 0.01;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	speed = 2;
	if (player->r_left)
		player->angle -= angle_speed;
	if (player->r_right)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->k_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->k_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->k_left)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->k_right)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
	// printf("[%f][%f]\n", player->x, player->y);
}