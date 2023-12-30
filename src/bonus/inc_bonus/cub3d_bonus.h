#include "../Lib/Libft/inc/libft.h"
#include "../Lib/Libft/inc/get_next_line.h"
#include "../mlx/mlx.h"

#include <fcntl.h>
#include <stdbool.h>
#include <math.h>

# define WHITE 0xFFFFFF
# define GRAY 0x808080

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

# define SIZE_MINMAP 11
# define MID_MIMMAP 6

// KEY PRESSED
# define ESC_KEY 53
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define W_KEY 13
# define D_KEY 2
# define S_KEY 1
# define A_KEY 0

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR  //partie bonus
}	t_dir;

// char position in map struct for parsing purposes, kquetat-
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player
{
	char c;
	double	pos_x; // start position
	double	pos_y;

	double	dir_x; // initial direction vector
	double	dir_y;

	double	plane_x; // 2d raycaster version of camera plane
	double	plane_y;

	double	old_dir_x;
	double	old_plane_x;
}	t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;

	double	cam_x;

	double	ray_x;
	double	ray_y;

	double	side_dist_x;
	double	side_dist_y;

	double	delta_x;
	double	delta_y;

	double	step_x;
	double	step_y;
	bool	side;

	double	wall_dist; // perpWallDist !
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_hit; // wallX !
	int		tex_x; // x coordinate on the texture
	int		tex_y; // y coordinate on the texture
	double	step_text;
	double	text_pos;
	bool	door_hit;
}	t_ray;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_vars;

typedef struct s_config
{
	//char	**data;
	char	**map;
	char	**file;
	int		file_size;
	int		map_loc;
	int		map_len;
	bool	anomaly; // kquetat-
	int		player; // kquetat-
	int		count_data; // epraduro
	char	*no_text;// epraduro
	char 	*so_text;// epraduro
	char 	*we_text;// epraduro
	char 	*ea_text;// epraduro
	char	*door_text; // bonus
	int		no_find;
	int		so_find;
	int		we_find;
	int		ea_find;
	int 	f_find;// epraduro
	int 	c_find;// epraduro
	char	**f_color;// epraduro
	char	**c_color;// epraduro
	double	pos_mmap_x; //partie bonus
	double	pos_mmap_y; // partie bonus
	/*
	mlx window
	donnees parsing
	map**
	*/
	t_vars		text[5];
	t_vars		*mlx;
	t_vars		wall;  //partie bonus
	t_vars		empty;  //partie bonus
	t_vars		tex_player;  //partie bonus
	t_vars		floor;  //partie bonus
	t_vars		door_o; //partie bonus
	t_vars		door_c; //partie bonus
	t_ray		*ray;
	t_player	*character;
	bool		mouse_show;
}	t_config;


/* --- PARSING --- kquetat- */
int		parse_data(t_config **conf, char **av);
int		find_map(t_config **conf);
int		map_len(t_config **conf);
int		text_size(char **av, int fd);
char	*trim_newline(char *str, char c);
bool	inspect_line(t_config **conf, char *map_line, char *to_find);
int		longest_line(char **map);

/* INSPECT_MAP functions kquetat- */
char	*fill_map(char *map, char *tmp, int line_len);
char	*fill_extremities(char *tmp, int line_len);
bool	flood_fill(t_config **conf, char **tmp);
t_pos	find_pos(char letter, char **map);

/* PRINT MAP WHEN ALREADY STOCKED (must be removed before push) */
void	print_map(char **map);

// kquetat- raycasting part && mlx_window.
int		initialize_mlx_win(t_config **conf);
int		init_cub(t_config **conf);
int		init_game(t_config **conf);
void	my_mlx_pixel_put(t_vars *data, int x, int y, int color);
double	ft_abs(double num);


/* --- epraduro --- */

/*	GET_TEXTURE.C	*/
int		skip(char *line);
int	get_colors(t_config **conf, int i);
int	get_textures(t_config **conf, int i);
int		get_texture_path(char *str, char **store_data, int *data);

/*	CHECK_COLOR.C	*/
int	ft_strcmp(char *s1, char *s2);
int	same_color(t_config **conf);
int	len_tab(char **tab);
int	valid_color(char **color);
int	check_color(char ***color, char *str, int *data);

/*	MAP_DATA.C	*/
bool	is_dir(char *arg);
int	check_path(char *arg);
int check_data(t_config **conf);

char *format_path_texture(char *str);

int ft_contain(char *str, char *find);

int	load_map(t_config **conf, t_vars *vars);
void	load_img(t_config **conf);
// int	ft_close(t_vars *vars);

int	inspect_map_bonus(t_config **conf);