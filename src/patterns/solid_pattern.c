/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:12:30 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:12:31 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"
#include <stdio.h>

static t_color	*solid_at(t_pattern *pattern, t_point *shape_point,
					t_color *out);

t_pattern	*new_solid_pattern(t_color *color, t_pattern *solid)
{
	new_pattern(solid);
	solid->color = *color;
	solid->pattern_at = solid_at;
	solid->has_pattern = true;
	return (solid);
}

static t_color	*solid_at(t_pattern *pattern, t_point *shape_point,
					t_color *out)
{
	(void)shape_point;
	*out = pattern->color;
	return (out);
}
