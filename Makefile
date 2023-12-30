
# --- SRC / OBJ --- #
SRC_PATH	=	./src/
SRC_PATH_BONUS	=	./src/

SRC			=	${addprefix ${SRC_PATH}, mandatory/main.c \
											mandatory/initialize/init_cub.c \
											mandatory/initialize/mlx_win.c \
											mandatory/parsing/check_color.c \
											mandatory/parsing/get_texture.c \
											mandatory/parsing/inspect_dup.c \
											mandatory/parsing/map_data.c \
											mandatory/parsing/map_parser.c \
											mandatory/parsing/map_tools.c \
											mandatory/parsing/parsing.c \
											mandatory/raycast/drawing.c}

SRC_BONUS			=	${addprefix ${SRC_PATH_BONUS}, bonus/main_bonus.c \
											bonus/initialize_bonus/init_cub_bonus.c \
											bonus/initialize_bonus/mlx_win_bonus.c \
											bonus/parsing_bonus/check_color_bonus.c \
											bonus/parsing_bonus/get_texture_bonus.c \
											bonus/parsing_bonus/inspect_dup_bonus.c \
											bonus/parsing_bonus/map_data_bonus.c \
											bonus/parsing_bonus/map_parser_bonus.c \
											bonus/parsing_bonus/map_tools_bonus.c \
											bonus/parsing_bonus/parsing_bonus.c \
											bonus/raycast_bonus/drawing_bonus.c \
											bonus/minimap_bonus/minimap_bonus.c }

### TEXT EDIT ###
BOLD		=	\033[1m
RESET		=	\033[0m
ITALIC		=	\033[3m
### Colors ###
GRAY		=	\033[38;5;245m
RED			=	\033[31m
GREEN		=	\033[32m
BLUE		=	\033[34m
PURPLE		=	\033[35m

# --- SRC / OBJ --- #
SRC_PATH	=	./src/

OBJ			=	${SRC:.c=.o}
OBJ_BONUS	=	${SRC_BONUS:.c=.o}

# --- COMPILER --- #
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
OFLAGS		=	-framework OpenGL -framework AppKit

# --- DEBUG PURPOSES --- #
ifdef	DEBUG
	CC	+=	-g
endif

HEADER		=	./inc/
HEADER_BONUS		=	./inc_bonus/

### Loading Bar ###
COUNTER		=	0
CUR_UP		=	\033[A
TOTAL_SRCS	=	${shell find . -type f -name "*.c" -not -path "./Lib/Libft/*" -not -path "./mlx/*" | wc -l}
PERCENT		=	${shell expr 100 \* ${COUNTER} / ${TOTAL_SRCS}}
BAR			=	${shell expr 19 \* ${COUNTER} / ${TOTAL_SRCS}}

${SRC_PATH}%.o: ${SRC_PATH}%.c
	@${eval COUNTER = ${shell expr ${COUNTER} + 1}}
	@${CC} ${CFLAGS} -Imlx -I${HEADER} -c $< -o $@
	@echo " ${GREEN}${BOLD} ↳ ${BLUE}cooking [${PURPLE}${NAME}${BLUE}]:${RESET}"
	@printf "\t\t\t${BOLD}${BLUE}[${PURPLE}%-19.${BAR}s${BLUE}] %d/%d [${GREEN}%d%%${BLUE}]${RESET}" "////////////////////" ${COUNTER} ${TOTAL_SRCS} ${PERCENT}
	@echo "${CUR_UP}${CUR_UP}"

${SRC_PATH_BONUS}%.o: ${SRC_PATH_BONUS}%.c
	@${CC} ${CFLAGS} -Imlx -I${HEADER_BONUS} -c $< -o $@
	@${eval COUNTER = ${shell expr ${COUNTER} + 1}}
	@${CC} ${CFLAGS} -Imlx -I${HEADER_BONUS} -c $< -o $@
	@echo " ${GREEN}${BOLD} ↳ ${BLUE}cooking [${PURPLE}${NAME_BONUS}${BLUE}]:${RESET}"
	@printf "\t\t\t${BOLD}${BLUE}[${PURPLE}%-19.${BAR}s${BLUE}] %d/%d [${GREEN}%d%%${BLUE}]${RESET}" "////////////////////" ${COUNTER} ${TOTAL_SRCS} ${PERCENT}
	@echo "${CUR_UP}${CUR_UP}"

# --- EXEC / RULES --- #
NAME		=	cub3D
NAME_BONUS	=	cub3D_bonus
LIBFT		=	./Lib/Libft/
MLX			=	./mlx/

all:	${NAME}

${NAME}:	brew_libft brew_mlx ${OBJ}
	@clear
	@printf "\n\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
	@${CC} ${CFLAGS} -Lmlx -lmlx ${OFLAGS} ${LIBFT}libft.a ${MLX}libmlx.a ${OBJ} -o ${NAME}
	@printf "${BOLD}${GREEN} ↳ ${BLUE}[${PURPLE}${NAME}${BLUE}] ${GREEN}compiled !${RESET}"
	@printf "\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"

bonus: brew_libft brew_mlx ${OBJ_BONUS}
	@clear
	@printf "\n\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
	@${CC} ${CFLAGS} -Lmlx -lmlx ${OFLAGS} ${LIBFT}libft.a ${MLX}libmlx.a ${OBJ_BONUS} -o ${NAME_BONUS}
	@printf "${BOLD}${GREEN} ↳ ${BLUE}[${PURPLE}${NAME_BONUS}${BLUE}] ${GREEN}compiled !${RESET}"
	@printf "\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"

brew_libft:
	@make -C ${LIBFT}

brew_mlx:
	@make -C ${MLX}

debug:
	@${MAKE} DEBUG=1

clean:
	@make clean -C ${LIBFT}
	@rm -f ${OBJ}
	@printf "\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
	@printf "${BOLD}${GREEN} ↳ ${BLUE}[${PURPLE}${NAME}${BLUE}] object ${RED}cleaned${RESET}"
	@printf "\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"

fclean:	clean
	@make clean -C ${MLX}
	@rm -f ${LIBFT}libft.a ${NAME}
	@printf "\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
	@printf "${BOLD}${GREEN} ↳ ${BLUE}[${PURPLE}${NAME}${BLUE}] ${RED}removed${RESET}"
	@printf "\n${GRAY}━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"

re:	fclean
	@${MAKE} all

.PHONY: all brew_libft brew_mlx debug clean fclean re