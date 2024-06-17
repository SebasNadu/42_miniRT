#include "world.h"
#include "groups.h"

t_world	*new_world(t_world *world)
{
	world->xs = NULL;
	world->objs_count = 0;
	world->objs = NULL;
	world->objs_inside_count = 0;
	world->objs_inside = NULL;
	world->objs_ext_count = 0;
	world->lights_count = 0;
	world->lights = NULL;
	world->ambient = new_color(0.1, 0.1, 0.1);
	world->remaining_recursion = MAX_RECURSION;
	return (world);
}
