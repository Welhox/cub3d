# **************************************************************************** #
#                                                                               #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 11:59:53 by clundber          #+#    #+#              #
#    Updated: 2024/02/16 12:18:31 by clundber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

# ------------ PROJECT -------#
NAME = cub3D
LIBFTNAME = libft.a

# ------------ DIRECTORIES ---#
LIBFT_DIR = ./libft
SRCS_DIR = ./src
BONUS_DIR = ./bonus
OBJ_DIR = ./src/temp
MLX_DIR = ./MLX42

#------------- SOURCE FILES ------#
CFILES = 	$(SRCS_DIR)/cub3d.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/init.c $(SRCS_DIR)/parsing/parsing.c \
			$(SRCS_DIR)/mlx.c $(SRCS_DIR)/image_utils.c  $(SRCS_DIR)/movement.c \
			$(SRCS_DIR)/ray_caster.c $(SRCS_DIR)/parsing/validate_data_utils.c $(SRCS_DIR)/parsing/map_parse.c \
			$(SRCS_DIR)/parsing/extract_data.c  $(SRCS_DIR)/parsing/check_line.c $(SRCS_DIR)/parsing/check_line_utils.c \
			$(SRCS_DIR)/safe_mlx.c $(SRCS_DIR)/dda.c $(SRCS_DIR)/dda_two.c $(SRCS_DIR)/movement_two.c \
			$(SRCS_DIR)/sprite.c $(SRCS_DIR)/utils_two.c $(SRCS_DIR)/render.c $(SRCS_DIR)/sprite_parse.c \
			$(SRCS_DIR)/minimap.c $(SRCS_DIR)/sprite_utils.c $(SRCS_DIR)/minimap.c $(SRCS_DIR)/fps.c

BONUS =		$(BONUS_DIR)/

OFILES = $(CFILES:.c=.o)

BOFILES = $(BONUS:.c=.o)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

LIBS	= $(MLX_DIR)/build/libmlx42.a

#MLX_LIBS = -L$(MLX_DIR)/build -lmlx42 -L"/User/$(USER)/.brew/opt/glfw/lib" -lglfw -ldl -pthread -lm 
MLX_LIBS = -L$(MLX_DIR)/build -lmlx42 -lglfw -ldl -pthread -lm 

#--------- FLAGS ----------#
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -Wunreachable-code -Ofast
HEADERS	:= -I ./include -I $(MLX_DIR)/include/MLX42/

all: mlx42 libmlx $(NAME)

mlx42:
	@if [ ! -d $(MLX_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
libmlx:
	@if [ ! -d $(MLX_DIR)/build ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4; \
	fi

$(NAME): $(OFILES)
	@echo "$(COLOUR_BLUE)compiling $(NAME)$(COLOUR_END)"
	@make -C libft
	@$(CC) $(CFLAGS) $(OFILES)  $(HEADERS) $(LIBS) $(MLX_LIBS) $(LIBFT_DIR)/$(LIBFTNAME) -o $(NAME) 
	@echo "$(COLOUR_GREEN)$(NAME) compiled successfully$(COLOUR_END)"
	
bonus = .bonus

.bonus: $(BOFILES) $(OFILES)
	@echo "$(COLOUR_BLUE)compiling bonus $(NAME)$(COLOUR_END)"
	@make -C libft
	@$(CC) $(CFLAGS) $(OFILES) $(BOFILES) $(HEADERS) $(LIBS) $(MLX_LIBS) $(LIBFT_DIR)/$(LIBFTNAME) -o $(NAME) 
	@echo "$(COLOUR_GREEN)$(NAME)bonus compiled successfully$(COLOUR_END)"
	touch .bonus

clean:
	@echo "$(COLOUR_GREEN)cleaning $(NAME)$(COLOUR_END)"
	@rm -f $(OFILES) $(BOFILES) .bonus
	@make clean -C libft/
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@rm -f $(NAME) 
	@rm -f libft/libft.a

re: fclean all 

.PHONY: all clean fclean re libmlx bonus