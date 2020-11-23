# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/11/23 20:54:34 by pani_zino     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

RED = \033[1;38;5;168m
BLU = \033[3;38;5;146m
RES = \033[0m

NAME := miniRT

SRC := main.c ./sources/bitmap/bitmap.c ./sources/colors/light.c ./sources/hooks/hooks.c		\
		./sources/intersect/intersect_cylinder.c ./sources/intersect/intersect_plane.c			\
		./sources/intersect/intersect_square.c ./sources/intersect/intersect_triangle.c			\
		./sources/intersect/intersect_sphere.c ./sources/lists/cam_list.c						\
		./sources/lists/image_list.c ./sources/lists/light_list.c ./sources/lists/object_list.c	\
		./sources/math/atod.c ./sources/math/matrix.c ./sources/math/vector_library1.c			\
		./sources/math/vector_library2.c ./sources/parser/check_scene_objects.c					\
		./sources/parser/check_scene_utils.c ./sources/parser/check_scene.c						\
		./sources/parser/get_objects.c ./sources/parser/get_scene_loop.c						\
		./sources/parser/get_scene.c ./sources/parser/read_file_utils.c							\
		./sources/parser/read_file.c ./sources/render/render_loop.c								\
		./sources/render/render.c ./sources/utils/error.c ./sources/utils/utils.c				\

INC := minirt.h

FLAGS := -Wall -Wextra -Werror -Imlx -Iinc

MFLAGS := -Lmlx/ -Lmlx -framework OpenGL -framework AppKit

MLX_PATH := ./mlx/

MLX := libmlx.dylib

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	@echo "$(RED) \n ┌──────────────────────┐\n │ \xe2\x99\xa5 compiling miniRT \xe2\x99\xa5 │\n └──────────────────────┘\n$(RES)"
	@gcc $(FLAGS) $(MFLAGS) -o $(NAME) -lpthread $(SRC) $(MLX)

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
