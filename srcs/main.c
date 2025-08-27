/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:11 by tnolent           #+#    #+#             */
/*   Updated: 2025/08/27 15:47:01 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_mlx(t_parse *parse)
{
	parse->mlx = mlx_init();
	parse->win = mlx_new_window(parse->mlx, LARGEUR, HAUTEUR, "FRACTOL");
	parse->img = mlx_new_image(parse->mlx, LARGEUR, HAUTEUR);
	parse->addr = mlx_get_data_addr(parse->img, &parse->bits_per_pixel,
			&parse->line_length, &parse->endian);
}

int main()
{
    t_parse parse;
    set_mlx(&parse);
    return (0);
}

