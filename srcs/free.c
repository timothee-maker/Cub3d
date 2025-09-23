/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:07:33 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/23 16:12:58 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	free_tex(t_texinfo *texture)
{
	free(texture->north);
	free(texture->south);
	free(texture->east);
	free(texture->west);
}
