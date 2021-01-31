NAME =		cub3D

FLAGS_WWW = -Wall -Wextra -Werror
LIBS_MLX_FT = -L ./$(LIBFT_DIR) -lft -L ./$(MLX_DIR) -lmlx
FLAGS_LIBS = -lm -lbsd -lX11 -lXext $(LIBS_MLX_FT)

SRC_DIR = 	sources
MLX_DIR =	mlx_linux
LIBFT_DIR = libft

INCLUDES = -I./includes -I./$(MLX_DIR) -I./$(LIBFT_DIR)/includes

SRC_FILES =	cub_utils.c \
			exit_game.c \
			get_info_player.c \
			get_info_sprites.c \
			get_line_map.c \
			get_map_identifier_1.c \
			get_map_identifier_2.c \
			get_next_line.c \
			get_textures.c \
			is_map_valid.c \
			key_event.c  \
			main.c \
			mlx_utils.c \
			move_player.c \
			process_map_file.c \
			process_map_file_utils.c \
			raycasting.c \
			raycasting_horz.c \
			raycasting_vert.c \
			render_projection_1.c \
			render_projection_2.c \
			render_sprites.c \
			save_bmp.c \
			update_game.c

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJS = 	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR)
	@clang $(OBJS) $(INCLUDES) $(FLAGS_WWW) $(FLAGS_LIBS) -o $(NAME)

%.o: %.c
	@clang $(FLAGS_WWW) $(INCLUDES) -c $< -o $@
	@echo "$@ created from $<"

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "OBJECTS deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -f *.bmp
	@make fclean -C $(LIBFT_DIR)
	@echo "$(NAME) deleted"

re: fclean all
