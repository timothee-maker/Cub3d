/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:58:49 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/01 17:14:53 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 800
# define WIDTH 1080

# define PI 3.14159265359
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define BLOCK 64

# define DEBUG 1

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	bool		k_up;
	bool		k_down;
	bool		k_left;
	bool		k_right;
	bool		r_left;
	bool		r_right;

}				t_player;

typedef struct s_parse
{
	t_player	player;
	char		**map;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_parse;

void			move_player(t_player *player);
int				key_press(int keycode, t_player *player);
void			init_player(t_player *player);
int				key_release(int keycode, t_player *player);

#endif