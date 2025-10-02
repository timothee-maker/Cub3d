/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:17:43 by barnaud           #+#    #+#             */
/*   Updated: 2025/10/01 11:17:45 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err_msg("Error\nCan't open file\n", 0));
	return (fd);
}

int	verify_extension(char *file)
{
	int		i;
	int		j;
	char	extension[4];

	if (!file)
		return (0);
	j = 0;
	i = ft_strlen(file) - 4;
	while (i < ft_strlen(file))
		extension[j++] = file[i++];
	extension[j] = '\0';
	if (strncmp(extension, ".cub", 4))
		return (err_msg("Error\nwrong file extension, try with .cub", 0));
	return (1);
}
