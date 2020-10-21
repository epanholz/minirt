# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/10/21 16:29:45 by epanholz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

RED = \033[1;38;5;168m
BLU = \033[3;38;5;146m
RES = \033[0m
NAME := miniRT

SRC := main.c read_file.c read_file_utils.c get_scene.c			\
	check_scene.c check_scene_utils.c cam_list.c utils.c		\
	matrix.c atod.c object_list.c intersect_triangle.c			\
	intersect_sphere.c image_list.c hooks.c light.c				\
	bitmap.c check_scene_objects.c get_objects.c error.c		\
	get_scene_loop.c light_list.c render.c render_loop.c		\
	intersect_plane.c intersect_cylinder.c intersect_square.c	\
	vector_library1.c vector_library2.c							\

INC := minirt.h

FLAGS := -Wall -Wextra -Werror -I mlx

MFLAGS := -Lmlx/ -Lmlx -framework OpenGL -framework AppKit

MLX_PATH := ./mlx/

MLX := libmlx.dylib

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	@echo "$(RED) \n ┌──────────────────────┐\n │ \xe2\x99\xa5 compiling miniRT \xe2\x99\xa5 │\n └──────────────────────┘\n$(RES)"
	@gcc $(FLAGS) $(MFLAGS) -o $(NAME) $(SRC) $(MLX)

$(MLX):
	@echo "$(RED) \n ┌──────────────────────┐\n │   \xe2\x99\xa5 compiling mlx \xe2\x99\xa5  │\n └──────────────────────┘\n$(RES)$(BLU)"
	@$(MAKE) -C $(MLX_PATH)
	@echo "$(RES)$(RED) \n ┌──────────────────────┐\n │   \xe2\x99\xa5 moving dylib \xe2\x99\xa5   │\n └──────────────────────┘\n$(RES)"
	@mv mlx/$(MLX) .

%.o: %.c
	@echo "$(BLU) compiling objects $(RES)"
	@gcc $(FLAGS) -c $< -o $@

clean:
	@echo "$(RED) \n ┌──────────────────────┐\n │     \xe2\x99\xa5 make clean \xe2\x99\xa5   │\n └──────────────────────┘\n$(RES)$(BLU)"
	@$(RM) $(OBJ)
	@$(MAKE) -C $(MLX_PATH) clean
	@echo "$(RES)"

fclean: clean
	@echo "$(RED) \n ┌──────────────────────┐\n │    \xe2\x99\xa5 make fclean \xe2\x99\xa5   │\n └──────────────────────┘\n$(RES)"
	@$(RM) $(NAME) $(MLX)

re: fclean all
