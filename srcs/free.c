/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:07:33 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/26 13:15:45 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i++] = NULL;
		}
	}
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
