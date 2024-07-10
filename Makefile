################################################################################
##                                   COLORS                                   ##
################################################################################

DEFAULT     := \033[0;39m
GRAY        := \033[0;90m
RED         := \033[0;91m
GREEN       := \033[0;92m
YELLOW      := \033[0;93m
BLUE        := \033[0;94m
MAGENTA     := \033[0;95m
CYAN        := \033[0;96m
WHITE       := \033[0;97m
	
################################################################################
##                                   MINIRT                                   ##
################################################################################

NAME							:= miniRT
RM								:= rm -rf
	
################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR						:= obj
SRC_DIRS					:= tuples utils canvas matrices rays shapes lights materials \
										 world camera patterns bounds obj_loader texture_mapping parser
SRC_DIRS					:= $(addprefix src/, $(SRC_DIRS))
SRC_DIRS					+= src
LIB_DIR						:= lib
LIBFT_DIR					:= $(LIB_DIR)/libft
MLX_DIR						:= $(LIB_DIR)/MLX42
INC_DIRS					:= include $(LIBFT_DIR)/include $(MLX_DIR)/include

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)
vpath %.o $(OBJ_DIR)

LIBFT							:= $(LIBFT_DIR)/libft.a
MLX								:= $(MLX_DIR)/build/libmlx42.a
HEADERS						:= tuples.h utils.h canvas.h matrices.h rays.h shapes.h lights.h \
										 materials.h world.h camera.h patterns.h groups.h obj_loader.h \
                    					 parser.h parser_error.h
SOURCE						:= main.c tuple.c basic_math.c vector_math.c utils.c color.c \
										 canvas.c save.c hooks.c mx.c mx_operations.c mx_attributes.c \
										 mx_transformations.c mx_rotations.c ray.c sphere.c intersections.c \
										 shape.c light.c material.c world.c view_transform.c camera.c \
										 render.c color_at.c plane.c pattern.c stripe.c gradient.c ring.c \
										 checkers.c full_gradient.c radial_gradient.c solid_pattern.c \
										 blended.c refrac_indices.c reflec_and_refrac.c cube.c cylinder.c \
										 cone.c discriminants.c group.c group_utils.c bounds.c local_bounds.c \
										 free.c triangle.c obj_loader.c	ft_atof.c	obj_loader_utils.c \
										 set_max_values.c obj_file_parser.c triangle_bounds.c csg.c csg_utils.c \
										 shadow_calculations.c sequencer.c light_shading.c bounding_boxes.c \
										 bvh.c bvh_utils.c threads.c obj_open_read.c obj_split_file_content.c \
										 obj_lines_parser.c obj_triangles_parser.c obj_triangles_fan.c \
										 obj_parse_elements.c loader_free.c loader_free2.c mapping_helpers.c \
										 uv_at.c shapes_mapping.c cube_mapping.c cube_mapping2.c cube_align_check.c \
										 texture_mapping.c mtl_file_parser.c mtl_lines_parser.c mtl_parse_elements.c \
										 mtl_parse_elements2.c mtl_parse_elements3.c render_utils.c \
										 ray_for_pixel.c multisample.c prepare_material.c \
										 parser.c parser_utils.c element_counter.c free_print.c error_u.c\
										 init_ambient.c init_mini_rt.c error.c valid_args.c init_cylinder.c\
										 line_parser.c init_camera.c init_light.c init_sphere.c init_plane.c\
										 init_cone.c calculate_rotation.c init_cube.c material_parser.c materials.c materials_II.c
OBJECTS						:= $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

################################################################################
##                                   FLAGS                                    ##
################################################################################

CFLAGS						= -Wall -Wextra -Werror
BONUS_FLAGS				:= -D THREADS
INCLUDE						:= $(addprefix -I, $(INC_DIRS))
LDFLAGS						:= -L$(LIBFT_DIR) -L$(MLX_DIR)/build
LDLIBS						:= -lft -lmlx42 -lglfw

ifeq ($(shell uname), Darwin)
	LDLIBS				+= -framework Cocoa -framework OpenGL -framework IOKit
else
	LDLIBS				+= -ldl -pthread -lm
endif

ifdef DEBUG
	CFLAGS					 += -fsanitize=address -g3
else
	CFLAGS 					 += -O3
endif

################################################################################
##                                PROGRESS_BAR                                ##
################################################################################

NUM_SRC_FILES			:= $(words $(SOURCE))
NUM_OBJ_FILES			:= $(words $(OBJECTS))
NUM_TO_COMPILE		= $(shell expr $(NUM_SRC_FILES) - $(NUM_OBJ_FILES))

ifeq ($(shell test $(NUM_TO_COMPILE) -le 0; echo $$?), 0)
	NUM_TO_COMPILE	= $(NUM_SRC_FILES)
endif

COMPILED_FILES		= 0
COMPILATION_PCT		= $(shell expr 100 \* $(COMPILED_FILES) / $(NUM_TO_COMPILE))
	
################################################################################
##                                COMPILATION                                 ##
################################################################################

all: submodules $(NAME)

test: submodules $(NAME)
	@make $(T) -C tests -s
	@make fclean -C tests -s

ex: submodules $(NAME)
	@make $(X) -C exs -s
	@make fclean -C exs -s

bonus: submodules
bonus: CFLAGS += $(BONUS_FLAGS)
bonus: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	@printf "\n$(MAGENTA)[$(NAME)] $(DEFAULT)Linking "
	@printf "($(BLUE)$(NAME)$(DEFAULT))..."
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@
	@printf "\r%100s\r$(MAGENTA)[$(NAME)] $(GREEN)Compilation success "
	@printf "🎉!$(DEFAULT)\n"

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(eval COMPILED_FILES = $(shell expr $(COMPILED_FILES) + 1))
	@printf "$(MAGENTA)\r%100s\r[$(NAME)] $(GREEN)[ %d/%d (%d%%) ]" \
			"" $(COMPILED_FILES) $(NUM_TO_COMPILE) $(COMPILATION_PCT) 
	@printf " $(DEFAULT)Compiling ($(BLUE)$<$(DEFAULT))..."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Creating objects directory "
	@printf "($(BLUE)$(OBJ_DIR)$(DEFAULT))..."
	@mkdir -p $@
	@printf "\r%100s\r$(MAGENTA)[$(NAME)] $(DEFAULT)($(BLUE)$(OBJ_DIR)/$(DEFAULT)) "
	@printf "Created successfully!\n"

$(LIBFT):
	@make -C $(LIBFT_DIR) -s

$(MLX):
	@cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	@cmake --build $(MLX_DIR)/build -j4

clean:
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Cleaning up objects files in "
	@printf "($(RED)$(OBJ_DIR)$(DEFAULT))..."
	@$(RM) $(OBJ_DIR)
	@printf "\r%100s\r$(MAGENTA)[$(NAME)] $(YELLOW)Objects clean success "
	@printf "🧹🧹$(DEFAULT)\n"

fclean: clean
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Cleaning up "
	@printf "($(RED)$(NAME)$(DEFAULT))..."
	@$(RM) $(NAME)
	@printf "\r%100s\r$(MAGENTA)[$(NAME)] $(YELLOW)Full clean success "
	@printf "🧹🧹$(DEFAULT)\n"
	@make fclean -C $(LIBFT_DIR) -s
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Cleaning up "
	@printf "($(RED)$(MLX_DIR)/build $(DEFAULT))..."
	@$(RM) $(MLX_DIR)/build
	@printf "\r%100s\r$(MAGENTA)[$(MLX_DIR)] $(YELLOW)Full clean success "
	@printf "🧹🧹$(DEFAULT)\n"

re: fclean all

submodules:
	@git submodule update --init --remote --recursive -q

.PHONY: all clean fclean re test ex submodules
