#include "tuples.h"
#include "utils.h"
#include <stdio.h>

typedef struct s_projectile {
	t_point		position;
	t_vector	velocity;
}	t_projectile;

typedef struct s_environment {
	t_vector	gravity;
	t_vector	wind;
}	t_environment;

t_projectile	tick(t_environment env, t_projectile proj)
{
	t_point		pos;
	t_vector	vel;

	add(&proj.position, &proj.velocity, &pos);
	add(&proj.velocity, &env.gravity, &vel);
	add(&vel, &env.wind, &vel);
	return ((t_projectile){pos, vel});
}

int	main(void)
{
	t_projectile	p;
	t_environment	e;

	new_point(0, 1, 0, &p.position);
	normalize(new_vector(1, 1, 0, &p.velocity), &p.velocity);
	new_vector(0, -0.1, 0, &e.gravity);
	new_vector(-0.01, 0, 0, &e.wind);
	while (!eq_dbl(p.position.y, 0.0) && p.position.y > 0.0)
	{
		printf("(%f, %f, %f)\n", p.position.x, p.position.y, p.position.z);
		p = tick(e, p);
	}
	printf("Final position >> (%f, %f, %f)\n", p.position.x, p.position.y,
		p.position.z);
	return (0);
}
