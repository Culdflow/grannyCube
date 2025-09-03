# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/04 14:55:29 by mabdessm          #+#    #+#              #
#    Updated: 2025/09/01 18:28:35 by dfeve            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS_NAME = cub3D_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 -O2 -fsanitize=address
RM = rm -rf
INCLUDES = -L./lib/libft -lft -L./lib/minilibx -lmlx -L/usr/lib -Iminilibx -lreadline -lXext -lX11 -lm -lz

SRCS = 

BONUS_SRCS = srcs/cub3d_bonus/main.c \
		srcs/cub3d_bonus/map_filler.c \
\
		srcs/cub3d_bonus/leveleditor/inputs.c \
		srcs/cub3d_bonus/leveleditor/leveleditor.c \
		srcs/cub3d_bonus/leveleditor/prompts.c \
		srcs/cub3d_bonus/leveleditor/signals.c \
		srcs/cub3d_bonus/leveleditor/windows.c \
\
		srcs/cub3d_bonus/render/draw.c \
		srcs/cub3d_bonus/render/images.c \
		srcs/cub3d_bonus/render/images_utils.c \
		srcs/cub3d_bonus/render/objects.c \
		srcs/cub3d_bonus/render/view.c \
\
		srcs/cub3d_bonus/vector/vector.c \
		srcs/cub3d_bonus/vector/vector_utils.c \
\
		srcs/cub3d_bonus/parsing/parsing.c \
		srcs/cub3d_bonus/parsing/parsing_utils.c \
		srcs/cub3d_bonus/parsing/parsing_extra.c \
		srcs/cub3d_bonus/parsing/additional_utils.c \
		srcs/cub3d_bonus/parsing/more_utils.c \
		srcs/cub3d_bonus/parsing/error_parsing.c \
		srcs/cub3d_bonus/parsing/error_utils.c \
\
		srcs/cub3d_bonus/mlx/mlx.c \
\
		srcs/cub3d_bonus/map/map.c \
\
		srcs/cub3d_bonus/player/player.c \
\
		srcs/cub3d_bonus/ray/ray.c \
		srcs/cub3d_bonus/ray/ray_list.c \
\
		srcs/cub3d_bonus/utils/utils.c \
\
		srcs/cub3d_bonus/textures/textures.c \
\
		srcs/cub3d_bonus/debug/debug.c \
\
		srcs/cub3d_bonus/animation/animation_player.c \
		srcs/cub3d_bonus/animation/animation.c \

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(NAME): $(OBJS)
	@echo "\033[0;31mcompiling ${NAME}...\033[0m"
	@$(CC) $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
	@echo "\033[0;32m${NAME} compiled!\033[0m"
	@echo

bonus: $(BONUS_OBJS)
	@echo "\033[0;31mcompiling ${BONUS_NAME}...\033[0m"
	@$(CC) $(FLAGS) $(BONUS_OBJS) $(INCLUDES) -o $(BONUS_NAME)
	@echo "\033[0;32m${BONUS_NAME} compiled!\033[0m"
	@echo

.c.o:
	@$(CC) $(FLAGS) -Iminilibx -c $< -o $@
	
all: $(NAME)

clean:
	@echo "\033[0;31mdeleting objects...\033[0m"
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "\033[0;32mobjects deleted!\033[0m"
	@echo

fclean: clean
	@echo "\033[0;31mdeleting ${NAME} executable...\033[0m"
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "\033[0;32m${NAME} executable deleted!\033[0m"
	@echo

re: fclean all

.PHONY: all re clean fclean bonus