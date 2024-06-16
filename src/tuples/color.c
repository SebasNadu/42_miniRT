#include "tuples.h"

t_color	*new_color(double r, double g, double b, t_color *out)
{
	*out = (t_color){r, g, b};
	return (out);
}

t_color	*add_color(t_color *c1, t_color *c2, t_color *out)
{
	*out = (t_color){
		c1->r + c2->r,
		c1->g + c2->g,
		c1->b + c2->b,
	};
	return (out);
}

t_color	*subtract_color(t_color *c1, t_color *c2, t_color *out)
{
	*out = (t_color){
		c1->r - c2->r,
		c1->g - c2->g,
		c1->b - c2->b,
	};
	return (out);
}

t_color	*multiply_color(t_color *c, double scalar, t_color *out)
{
	if (scalar == 0.0)
		*out = (t_color){0.0, 0.0, 0.0};
	else if (scalar == 1.0)
		*out = *c;
	else
		*out = (t_color){
			c->r * scalar,
			c->g * scalar,
			c->b * scalar,
		};
	return (out);
}

t_color	*hadamard_product(t_color *c1, t_color *c2, t_color *out)
{
	*out = (t_color){
		c1->r * c2->r,
		c1->g * c2->g,
		c1->b * c2->b,
	};
	return (out);
}
