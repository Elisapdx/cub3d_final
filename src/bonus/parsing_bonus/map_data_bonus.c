#include "../inc_bonus/cub3d_bonus.h"
#include "../inc_bonus/parse_err_bonus.h"
#include "../inc_bonus/mlx_win_bonus.h"

/*
* CheckList for the Data ABOVE the map.
TODO check if all data is present. 🤗
TODO check if path of texture is valid. 🤗
TODO check format of data SO, WE, NO, EA, C, F. 🤗
TODO color: check that colors are separated by colons ",". 🤗
TODO color: check that integer doesn't exceed 0 - 255. 🤗
*/

void	init_texture(t_config **conf)
{
	(*conf)->count_data = 0;
	(*conf)->door_text = NULL;
	(*conf)->no_text = NULL;
	(*conf)->so_text = NULL;
	(*conf)->we_text = NULL;
	(*conf)->ea_text = NULL;
}

bool	is_dir(char *arg)
{
	int		fd;
	bool	res;

	res = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		res = true;
	}
	return (res);
}

char	*format_path_texture(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			j = -1;
			while (str[++j])
				str[j] = str[j + 1];
			i = -1;
		}
		else
			break ;
	}
	i = ft_strlen(str);
	i--;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
	{
		str[i] = '\0';
		i--;
	}
	return (str);
}

char	**get_wall_texture(t_config **conf)
{
	char	**table;

	table = malloc(sizeof(char *) * 5);
	if (!table)
		return (NULL);
	table[0] = (*conf)->no_text;
	table[1] = (*conf)->so_text;
	table[2] = (*conf)->ea_text;
	table[3] = (*conf)->we_text;
	table[4] = "./src/bonus/textures_bonus/door.xpm";  // a supp de la partie normale
	table[5] = NULL;
	return (table);
}

/*
* transform all xpm files to images for wall textures.
*/
int	stock_image(t_config **conf, t_vars *mlx)
{
	int		i;
	int		width;
	int		height;
	char	**wall_text;

	i = -1;
	width = TEXTURE_W;
	height = TEXTURE_H;
	wall_text = get_wall_texture(conf);
	while (++i < 5)
	{
		(*conf)->text[i].img = mlx_xpm_file_to_image(mlx->mlx, \
			wall_text[i], &width, &height);
		if (!(*conf)->text[i].img)
			return (FAILS);
		(*conf)->text[i].addr = mlx_get_data_addr((*conf)->text[i].img, \
			&(*conf)->text[i].bpp, &(*conf)->text[i].line_len, \
			&(*conf)->text[i].endian);
		if (!(*conf)->text[i].addr)
			return (FAILS);
	}
	return (0);
}

int	check_data(t_config **conf)
{
	int	i;

	i = -1;
	init_texture(conf);
	while (++i < (*conf)->map_loc)
		if (get_textures(conf, i) == ERROR || get_colors(conf, i) == ERROR)
			return (ERROR);
	printf("oui\n");
	if ((*conf)->count_data != 6)
		return (ft_putendl_fd(ELEMENT_ERR, STDERR_FILENO));
	printf("oui2\n");
	if (same_color(conf) == ERROR)
		return (ERROR);
	printf("oui3\n");
	if (initialize_mlx_win(conf) || stock_image(conf, (*conf)->mlx) == FAILS)
		return (ERROR);
	return (SUCCES);
}
