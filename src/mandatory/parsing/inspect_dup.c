/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:41:21 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 13:41:23 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mandatory/cub3d.h"
#include "../inc/mandatory/err_type.h"

static void	examine_path(t_map *map, char **tmp, t_pos pos, char *to_fill)
{
	if (pos.y < 0 || pos.x < 0 \
		|| pos.y >= map->map_len + 2 \
		|| !ft_strchr(to_fill, tmp[pos.y][pos.x]) \
		|| tmp[pos.y][pos.x] == '1' || map->anomaly)
		return ;
	if (tmp[pos.y][pos.x] && tmp[pos.y][pos.x] == '/')
		map->anomaly = true;
	tmp[pos.y][pos.x] = 'X';
	examine_path(map, tmp, (t_pos){pos.x - 1, pos.y}, to_fill);
	examine_path(map, tmp, (t_pos){pos.x + 1, pos.y}, to_fill);
	examine_path(map, tmp, (t_pos){pos.x, pos.y - 1}, to_fill);
	examine_path(map, tmp, (t_pos){pos.x, pos.y + 1}, to_fill);
}

bool	flood_fill(t_map *map, char **tmp)
{
	int		i;
	t_pos	pos;

	i = -1;
	map->anomaly = false;
	while (tmp[++i])
	{
		while (tmp[i] && ft_strchr(tmp[i], '0'))
		{
			pos = find_pos('0', tmp);
			if (pos.x < 0 || pos.y < 0)
				return (false);
			examine_path(map, tmp, pos, "0/NWSE");
		}
		if (map->anomaly == true)
			return (false);
	}
	return (true);
}
