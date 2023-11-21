NAME = cub3d
LIBMLX = ./MLX42
SRC = main.c error.c input_check.c
VPATH = src
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
OBJ_DIR = obj
FLAGS = -Wall -Wextra -Werror -0fastß
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -pthread -lm -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

CC = cc

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@printf "$(NAME) compiled\n"

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CC) $(FLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

PHONY: all clean fclean re