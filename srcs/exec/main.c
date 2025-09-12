/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:11 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 15:59:22 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_parse	parse;

	init_mlx(&parse);
	set_mlx(&parse);
	mlx_hook(parse.win, 2, 1L << 0, key_press, &parse);
	mlx_hook(parse.win, 3, 1L << 1, key_release, &parse.player);
	mlx_loop_hook(parse.mlx, draw_loop, &parse);
	mlx_hook(parse.win, 17, 0, close_window, &parse);
	mlx_loop(parse.mlx);
	return (0);
}
