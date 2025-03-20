NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = Libft
MLX_DIR = minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX = -L./minilibx-linux -lmlx -lm -lbsd -lX11 -lXext

SRC = main.c map.c map_utils.c map_utils2.c parse_map.c parse_utils.c parse_elements.c \
      textures.c draw.c utils.c game.c player.c player_utils.c raycasting.c \
      raycasting_draw.c parse_map2.c parse_utils2.c fuck.c \
	  get_next_line/get_next_line.c \
	  get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)
RM = rm -f

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

COMPILING = "$(GREEN)✓$(RESET) Compilation de $(YELLOW)$<$(RESET)"
LINKING = "$(GREEN)✓$(RESET) Création de $(YELLOW)$(NAME)$(RESET)"
CLEANING = "$(GREEN)✓$(RESET) Nettoyage des fichiers objets"
FCLEANING = "$(GREEN)✓$(RESET) Nettoyage complet"

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@echo $(LINKING)
	@chmod 777 $(MLX_DIR)/Makefile
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

%.o: %.c
	@echo $(COMPILING)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX_LIB):
	@make -C $(MLX_DIR) --no-print-directory

clean:
	@echo $(CLEANING)
	@$(RM) $(OBJ)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@make -C $(MLX_DIR) clean --no-print-directory

fclean: clean
	@echo $(FCLEANING)
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
