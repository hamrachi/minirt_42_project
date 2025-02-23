NAME = miniRT

NAME_B = miniRT_BONUS

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = mandatory

SRC_B_DIR = bonus

OBJ_DIR = objects

OBJ_B_DIR = objects_bonus


DEPS = main.c \
		$(SRC_DIR)/parsing/parsing.c $(SRC_DIR)/parsing/parsing_utils.c $(SRC_DIR)/parsing/parsing2.c $(SRC_DIR)/parsing/parsing3.c \
		$(SRC_DIR)/parsing/parsing_utils1.c $(SRC_DIR)/parsing/parsing_utils2.c $(SRC_DIR)/parsing/parsing_utils3.c \
		$(SRC_DIR)/vectors/vec2r.c $(SRC_DIR)/vectors/vec_magnitude.c $(SRC_DIR)/vectors/vec2r1.c \
		$(SRC_DIR)/objects_intersections/plane.c $(SRC_DIR)/objects_intersections/sphere.c \
		$(SRC_DIR)/colors/colors.c $(SRC_DIR)/mlx/mlx_function.c $(SRC_DIR)/objects_intersections/intersection.c \
		$(SRC_DIR)/objects_intersections/cylinder.c $(SRC_DIR)/camera/camera.c $(SRC_DIR)/raytracing/ft_render.c $(SRC_DIR)/libft/libft_helper3.c\
		$(SRC_DIR)/shadow/shadow.c $(SRC_DIR)/libft/libft_helper.c $(SRC_DIR)/libft/libft_helper1.c $(SRC_DIR)/libft/libft_helper2.c \
		$(SRC_DIR)/garbedge_collector/allocation.c $(SRC_DIR)/garbedge_collector/garbedge.c $(SRC_DIR)/gnl/line.c \

DEPS_B = main_bonus.c \
		$(SRC_B_DIR)/parsing/parsing.c $(SRC_B_DIR)/parsing/parsing_utils.c $(SRC_B_DIR)/parsing/parsing1.c \
		$(SRC_B_DIR)/parsing/parsing_utils1.c $(SRC_B_DIR)/parsing/parsing_utils2.c $(SRC_B_DIR)/parsing/parsing_utils3.c \
		$(SRC_B_DIR)/vectors/vec2r.c $(SRC_B_DIR)/vectors/vec_magnitude.c $(SRC_B_DIR)/vectors/vec2r1.c \
		$(SRC_B_DIR)/objects_intersections/plane.c $(SRC_B_DIR)/objects_intersections/sphere.c \
		$(SRC_B_DIR)/colors/colors.c $(SRC_B_DIR)/mlx/mlx_function.c $(SRC_B_DIR)/objects_intersections/intersection.c \
		$(SRC_B_DIR)/objects_intersections/cylinder.c $(SRC_B_DIR)/camera/camera.c $(SRC_B_DIR)/raytracing/threads.c \
		$(SRC_B_DIR)/raytracing/ft_render.c $(SRC_B_DIR)/raytracing/supersimpler.c $(SRC_B_DIR)/raytracing/supersimpler1.c \
		$(SRC_B_DIR)/shadow/shadow.c $(SRC_B_DIR)/libft/libft_helper.c $(SRC_B_DIR)/libft/libft_helper1.c $(SRC_B_DIR)/libft/libft_helper2.c \
		$(SRC_B_DIR)/garbedge_collector/allocation.c $(SRC_B_DIR)/garbedge_collector/garbedge.c $(SRC_B_DIR)/gnl/line.c \
		$(SRC_B_DIR)/colors/checker_board.c $(SRC_B_DIR)/colors/specular.c \
		
HEADERS = miniRT.h

HEADERS_B = miniRT_bonus.h

OBJ = $(DEPS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_B = $(DEPS_B:$(SRC_B_DIR)/%.c=$(OBJ_B_DIR)/%.o)


all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)  -lmlx \
		-framework Cocoa -framework OpenGL -framework AppKit libmlx.a

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) -o $@ $(OBJ_B)  -lmlx \
		-framework Cocoa -framework OpenGL -framework AppKit libmlx.a


$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c	$(HEADERS)	|	$(OBJ_DIR)
	$(CC)	$(CFLAGS)	-o	$@	-c	$<

$(OBJ_B_DIR)/%.o:	$(SRC_B_DIR)/%.c	$(HEADERS_B)	|	$(OBJ_B_DIR)
	$(CC)	$(CFLAGS)	-o	$@	-c	$<

$(OBJ_DIR):
	mkdir $@

$(OBJ_B_DIR):
	mkdir $@

clean:
	find $(OBJ_DIR) $(OBJ_B_DIR) -type f -name '*.o' -delete

fclean: clean
	rm -f $(NAME) $(NAME_B)

bonus: $(NAME_B)

re: fclean all
