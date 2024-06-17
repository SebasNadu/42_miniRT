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

TESTS							:= tuples colors canvas matrices transformations rays spheres \
										 lights materials world view_transform camera shapes planes \
										 patterns reflec_refrac cubes cones groups triangles obj_loader \
										 csg features bvh texture_mapping
RM								:= rm -rf
	
################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR						:= ../obj
SRC_DIR						:= ../src
LIB_DIR						:= ../lib
LIBFT_DIR					:= $(LIB_DIR)/libft
MLX_DIR						:= $(LIB_DIR)/MLX42
INC_DIRS					:= ./ ../include $(LIBFT_DIR)/include $(MLX_DIR)/include
SRC_DIRS  				:= $(shell find $(SRC_DIR) -type d)

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)
vpath %.o $(OBJ_DIR)

SOURCE						:= $(shell find $(SRC_DIR) -name '*.c' -exec basename {} \;)
SOURCE						:= $(filter-out main.c, $(SOURCE))
OBJECTS						:= $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))
	
################################################################################
##                                   FLAGS                                    ##
################################################################################

CFLAGS						:= -Wall -Wextra -Werror -O3
INCLUDE						:= $(addprefix -I, $(INC_DIRS))
LDFLAGS						:= -L$(LIBFT_DIR) -L$(MLX_DIR)/build
LDLIBS						:= -lft -lmlx42 -lglfw -lcriterion

ifeq ($(shell uname), Darwin)
	LDLIBS					+= -framework Cocoa -framework OpenGL -framework IOKit
else
	LDFLAGS					+= -L$(HOME)/libs/Criterion/builddir/src
	LDLIBS					+= -ldl -pthread -lm
endif

define run
	$(CC) $(CFLAGS) $(INCLUDE) $^ $(LDFLAGS) $(LDLIBS) -o $@ && ./$@ --verbose
endef

################################################################################
##                                COMPILATION                                 ##
################################################################################

all: $(TESTS) clean

.PHONY: tuples
tuples: $(OBJECTS) test_tuples.c
	@$(call run, "$^")

.PHONY: colors
colors: $(OBJECTS) test_colors.c
	@$(call run, "$^")

.PHONY: canvas
canvas: $(OBJECTS) test_canvas.c
	@$(call run, "$^")

.PHONY: matrices
matrices: $(OBJECTS) test_matrices.c
	@$(call run, "$^")

.PHONY: transformations
transformations: $(OBJECTS) test_transformations.c
	@$(call run, "$^")

.PHONY: rays
rays: $(OBJECTS) test_rays.c
	@$(call run, "$^")

.PHONY: spheres
spheres: $(OBJECTS) test.c test_spheres.c
	@$(call run, "$^")

.PHONY: lights
lights: $(OBJECTS) test.c test_lights.c
	@$(call run, "$^")

.PHONY: materials
materials: $(OBJECTS) test.c test_materials.c
	@$(call run, "$^")

.PHONY: world
world: $(OBJECTS) test.c test_world.c
	@$(call run, "$^")

.PHONY: view_transform
view_transform: $(OBJECTS) test.c test_view_transform.c
	@$(call run, "$^")

.PHONY: camera
camera: $(OBJECTS) test.c test_camera.c
	@$(call run, "$^")

.PHONY: shapes
shapes: $(OBJECTS) test.c test_shapes.c
	@$(call run, "$^")

.PHONY: planes
planes: $(OBJECTS) test.c test_planes.c
	@$(call run, "$^")

.PHONY: patterns
patterns: $(OBJECTS) test_patterns.c
	@$(call run, "$^")

.PHONY: reflec_refrac
reflec_refrac: $(OBJECTS) test.c test_reflec_refrac.c
	@$(call run, "$^")

.PHONY: cubes
cubes: $(OBJECTS) test.c test_cubes.c
	@$(call run, "$^")

.PHONY: cylinders
cylinders: $(OBJECTS) test.c test_cylinders.c
	@$(call run, "$^")

.PHONY: cones
cones: $(OBJECTS) test.c test_cones.c
	@$(call run, "$^")

.PHONY: groups
groups: $(OBJECTS) test.c test_groups.c
	@$(call run, "$^")

.PHONY: triangles
triangles: $(OBJECTS) test.c test_triangles.c
	@$(call run, "$^")

.PHONY: obj_loader
obj_loader: $(OBJECTS) test.c test_obj_loader.c
	@$(call run, "$^")

.PHONY: csg
csg: $(OBJECTS) test.c test_csg.c
	@$(call run, "$^")

.PHONY: features
features: $(OBJECTS) test.c test_features.c
	@$(call run, "$^")

.PHONY: bvh
bvh: $(OBJECTS) test.c test_bvh.c
	@$(call run, "$^")

.PHONY: texture_mapping
texture_mapping: $(OBJECTS) test.c test_texture_mapping.c
	@$(call run, "$^")

$(OBJECTS):
	@make -C .. -s

clean:
	@printf "$(MAGENTA)[tests] $(DEFAULT)Cleaning up tests..."
	@$(RM) $(TESTS)
	@printf "\r%100s\r$(MAGENTA)[tests] $(YELLOW)Full clean success "
	@printf "🧹🧹$(DEFAULT)\n"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
