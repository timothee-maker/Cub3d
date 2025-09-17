/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:24 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/17 16:01:34 by tnolent          ###   ########.fr       */
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

int		verify_extension(char *file)
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
		return (err_msg("ERREUR fd", 0));
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

int		fill_tab(t_game *game)
{
	char	*line;
	t_index	index;

	init_index(&index);
	line = get_next_line(game->mapinfo.fd);
	while (line != NULL)
	{
		game->mapinfo.file[index.i] = ft_calloc(ft_strlen(line) + 1,
				sizeof(char));
		if (!game->mapinfo.file[index.i])
			return (free_tab((void **)game->mapinfo.file), err_msg(ERR_MALLOC, 0));
		while (line[index.k] != '\0')
			game->mapinfo.file[index.i][index.j++] = line[index.k++];
		game->mapinfo.file[index.i++][index.j] = '\0';
		index.j = 0;
		index.k = 0;
		free(line);
		line = get_next_line(game->mapinfo.fd);
	}
	game->mapinfo.file[index.i] = NULL;
	return (1);
}

int	parse_data(char *path, t_game *game)
{
	game->mapinfo.nb_line = get_nb_lines(path);
	if (game->mapinfo.nb_line == -1)
		return (0);
	game->mapinfo.path = path;
	game->mapinfo.file = ft_calloc(game->mapinfo.nb_line + 1, sizeof(char *));
	if (!(game->mapinfo.file))
		return (err_msg(ERR_MALLOC, 0));
	game->mapinfo.fd = open_file(path);
	if (game->mapinfo.fd < 0)
		return (err_msg("ERREUR fd", 0));
	if (!fill_tab(game))
		return (close(game->mapinfo.fd), 0);
	close(game->mapinfo.fd);
	return (1);
}

static int	ignore_whitespaces_get_info(t_game *game, char **map, int i, int j)
{
	(void)game;
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !ft_isdigit(map[i][j]))
		{
			// if (fill_direction_textures(&game->texinfo, map[i], j) == ERR)
			// 	return (err_msg("texture invalide", FAILURE));
			return (BREAK);
		}	
		else
		{
			// if (fill_color_textures(game, &game->texinfo, map[i], j) == ERR)
			// 	return (FAILURE);
			return (BREAK);
		}	
	}
	else if (ft_isdigit(map[i][j]))
	{
		// if (create_map(game, map, i) == FAILURE)
		// 	return (err_msg("invalid map", FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}

int	get_file_data(t_game *game, char **map)
{
	t_index index;

	init_index(&index);
	while (map[index.i])
	{
		index.j = 0;
		while (map[index.i][index.j])
		{
			index.k = ignore_whitespaces_get_info(game, map, index.i, index.j);
			if (index.k == BREAK)
				break ;
			else if (index.k == FAILURE)
				return (FAILURE);
			else if (index.k == SUCCESS)
				return (SUCCESS);
			index.j++;
		}
		index.i++;
	}
	return (SUCCESS);
}

int	parse_args(char *file, t_game *game)
{
	if (!verify_extension(file))
		return (0);
	if (!parse_data(file, game))
		return (0);
	return (1);
}
