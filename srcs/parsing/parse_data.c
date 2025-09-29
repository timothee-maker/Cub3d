/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:40:38 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/29 09:33:22 by tnolent          ###   ########.fr       */
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

int	get_nb_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_msg(ERR_MALLOC, -1));
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (line_count);
}

void	free_texture(t_texinfo *texture)
{
	if (texture->ceiling)
		free(texture->ceiling);
	if (texture->floor)
		free(texture->floor);
	if (texture->north)
		free(texture->north);
	if (texture->south)
		free(texture->south);
	if (texture->west)
		free(texture->west);
	if (texture->east)
		free(texture->east);
}

void	clean_parse(t_game *game, char *str)
{
	if (game->mapinfo.file)
		free_tab((void *)game->mapinfo.file);
	if (str)
		free(str);
	free_texture(&game->texinfo);
}

int	fill_tab(t_game *game)
{
	char	*line;
	t_index	index;

	init_index(&index);
	line = get_next_line(game->mapinfo.fd);
	if (!line)
		return (err_msg(ERR_MALLOC, 0));
	while (line != NULL)
	{
		game->mapinfo.file[index.i] = ft_calloc(ft_strlen(line) + 1,
				sizeof(char));
		if (!game->mapinfo.file[index.i])
			return (clean_parse(game, line), err_msg(ERR_MALLOC, 0));
		while (line[index.k] != '\0')
			game->mapinfo.file[index.i][index.j++] = line[index.k++];
		game->mapinfo.file[index.i++][index.j] = '\0';
		index.j = 0;
		index.k = 0;
		free(line);
		line = get_next_line(game->mapinfo.fd);
	}
	if (line)
		free(line);
	return (game->mapinfo.file[index.i] = NULL, 1);
}

int	parse_data(char *path, t_game *game)
{
	game->mapinfo.nb_line = get_nb_lines(path);
	if (game->mapinfo.nb_line <= 0)
		return (0);
	game->mapinfo.path = path;
	game->mapinfo.file = ft_calloc(game->mapinfo.nb_line + 1, sizeof(char *));
	if (!(game->mapinfo.file))
		return (err_msg(ERR_MALLOC, 0));
	game->mapinfo.fd = open_file(path);
	if (game->mapinfo.fd < 0)
		return (err_msg("ERREUR fd", 0));
	if (!fill_tab(game))
		return (close(game->mapinfo.fd));
	close(game->mapinfo.fd);
	return (1);
}
