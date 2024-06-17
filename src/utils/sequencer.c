#include "utils.h"

void	new_sequencer(t_sequencer *gen)
{
	static int	base = 1;

	gen->base = ++base;
	gen->index = 0;
}

double	halton_sequence(t_sequencer *gen)
{
	double	result;
	double	f;
	int		i;

	result = 0.0;
	f = 1.0 / gen->base;
	i = ++gen->index;
	while (i > 0)
	{
		result += f * (i % gen->base);
		i /= gen->base;
		f /= gen->base;
	}
	return (result);
}

double	next_sequence(t_sequencer *gen)
{
	static double	sequence[] = {0.0, 0.5, 0.25, 0.75, 0.125, 0.625, 0.375,
		0.875, 0.0625, 0.5625, 0.3125, 0.8125, 0.1875, 0.6875, 0.4375, 0.9375,
		0.03125, 0.53125, 0.28125, 0.78125, 0.15625, 0.65625, 0.40625, 0.90625,
		0.09375, 0.59375, 0.34375, 0.84375, 0.21875, 0.71875, 0.46875, 0.96875,
		0.015625, 0.515625, 0.265625, 0.765625, 0.140625, 0.640625, 0.390625,
		0.890625, 0.078125, 0.578125, 0.328125, 0.828125, 0.203125, 0.703125,
		0.453125, 0.953125};

	if (gen->index >= 48)
		gen->index = gen->base;
	return (sequence[gen->index++]);
}
