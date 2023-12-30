#include "../src/mandatory/inc/cub3d.h"
#include "../src/mandatory/inc/parse_err.h"
#include "../src/mandatory/inc/mlx_win.h"
#include "../src/mandatory/inc/mlx_err.h"

double	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

char	identify_pos_player(t_player *p, int j, char *map_part, bool *identified)
{
	int		i;
	char	c;

	i = -1;
	c = '\0';
	while (map_part[++i])
	{
		if (ft_strchr("NWES", map_part[i]) != 0)
		{
			p->pos_y = i + 0.5;
			p->pos_x = j + 0.5;
			c = map_part[i];
			*identified = true;
			break ;
		}
	}
	return (c);
}

void	setup_player(t_player *character, char c)
{
	character->dir_x = 0;
	character->dir_y = 0;
	character->plane_x = 0;
	character->plane_y = 0;
	if (c == 'N')
	{
		character->dir_x = -1;
		character->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		character->dir_x = 1;
		character->plane_y = -0.66;
	}
	else if (c == 'E')
	{
		character->dir_y = 1;
		character->plane_x = 0.66;
	}
	else if (c == 'W')
	{
		character->dir_y = -1;
		character->plane_x = -0.66;
	}
}

int	init_cub(t_config **conf)
{
	int		i;
	char	c;
	char	**map;
	bool	identified;

	(*conf)->character = malloc(sizeof(t_player));
	if (!(*conf)->character)
		return (ft_putendl_fd(MALLOC_ERR, STDERR_FILENO));
	i = -1;
	identified = false;
	map = (*conf)->map;
	print_map(map);
	while (map[++i] && !identified)
		c = identify_pos_player((*conf)->character, i, map[i], &identified);
	if (!c)
		return (ft_putendl_fd("Error\nChar not found\n", 2));
	// (*conf)->character->pos_x = i + 0.5;
	printf("y:%f x:%f\n", (*conf)->character->pos_y, (*conf)->character->pos_x);
	setup_player((*conf)->character, c);
	(*conf)->character->old_dir_x = 0;
	(*conf)->character->old_plane_x = 0;
	return (0);
}
