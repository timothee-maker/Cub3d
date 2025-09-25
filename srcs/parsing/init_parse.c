/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:30:26 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/25 09:13:04 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_index(t_index *index)
{
	index->i = 0;
	index->j = 0;
	index->k = 0;
	index->i = 0;
}

void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->fd = 0;
	mapinfo->nb_line = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->end_of_map = 0;
	mapinfo->start_of_map = 0;
}

void	init_texinfo(t_texinfo *texinfo)
{
	texinfo->ceiling = NULL;
	texinfo->floor = NULL;
	texinfo->north = NULL;
	texinfo->south = NULL;
	texinfo->east = NULL;
	texinfo->west = NULL;
}