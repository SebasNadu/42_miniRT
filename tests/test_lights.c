#include "test.h"

Test(lights, point_light_has_position_and_intensity)
{
	t_color	intensity;
	t_point	position;
	t_light	light;

	new_color(1.0, 1.0, 1.0, &intensity);
	new_point(0.0, 0.0, 0.0, &position);
	new_light(&position, &intensity, &light);
	cr_assert(tuple_eq(light.position, position));
	cr_assert(color_eq(light.intensity, intensity));
}
