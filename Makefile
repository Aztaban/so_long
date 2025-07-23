# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 23:57:47 by mjusta            #+#    #+#              #
#    Updated: 2025/07/24 01:28:43 by mjusta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRC_DIR = src
OBJ_DIR = build
INCLUDE_DIR = include

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = $(SRC_DIR)/main.c \
			$(SRC_DIR)/controls.c \
			$(SRC_DIR)/animate.c \
			$(SRC_DIR)/game.c \
			$(SRC_DIR)/map.c \
			$(SRC_DIR)/validate.c \
			$(SRC_DIR)/graphics.c \
			$(SRC_DIR)/validate_path.c \
			$(SRC_DIR)/ui.c \
			$(SRC_DIR)/cleanup.c \
			$(SRC_DIR)/draw.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = $(MLX_LIB) -lXext -lX11 -lm

INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d -empty -delete || true
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(NAME) maps/level_02.ber

norminette:
	@norminette $(SRC_DIR)/*.c $(INCLUDE_DIR)/*.h

.PHONY: all clean fclean re norminette
