/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:30:03 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/26 14:57:59 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	transform_tt(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char		**triple;
	t_matrix	translate_m;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_PAT));
	env->error_type = E_TRIPPLE;
	triple = ft_subsplit(env->line[*index], ",\n");
	if (triplets(triple, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	multiply_matrices(&pattern->transform, translation(ft_atof(triple[0]),
			ft_atof(triple[1]), ft_atof(triple[2]), &translate_m),
		&translate_m);
	set_pattern_transform(pattern, &translate_m);
	return (free_s(triple), 0);
}

int	transform_ts(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char		**triple;
	t_matrix	scaling_t;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_PAT));
	env->error_type = E_TRIPPLE;
	triple = ft_subsplit(env->line[*index], ",\n");
	if (triplets(triple, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	multiply_matrices(&pattern->transform, scaling(ft_atof(triple[0]),
			ft_atof(triple[1]), ft_atof(triple[2]), &scaling_t), &scaling_t);
	set_pattern_transform(pattern, &scaling_t);
	return (free_s(triple), 0);
}

int	transform_trx(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	t_matrix	rotation_t;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_PAT));
	env->error_type = E_DOUBLE_I;
	if (solo(env->line[*index], (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	multiply_matrices(&pattern->transform,
		rotation_x(cos(ft_atof(env->line[*index])),
			sin(ft_atof(env->line[*index])), &rotation_t), &rotation_t);
	set_pattern_transform(pattern, &rotation_t);
	return (0);
}

int	transform_try(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	t_matrix	rotation_t;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_PAT));
	env->error_type = E_DOUBLE_I;
	if (solo(env->line[*index], (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	multiply_matrices(&pattern->transform,
		rotation_y(cos(ft_atof(env->line[*index])),
			sin(ft_atof(env->line[*index])), &rotation_t), &rotation_t);
	set_pattern_transform(pattern, &rotation_t);
	return (0);
}

int	transform_trz(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	t_matrix	rotation_t;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_PAT));
	env->error_type = E_DOUBLE_I;
	if (solo(env->line[*index], (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	multiply_matrices(&pattern->transform,
		rotation_z(cos(ft_atof(env->line[*index])),
			sin(ft_atof(env->line[*index])), &rotation_t), &rotation_t);
	set_pattern_transform(pattern, &rotation_t);
	return (0);
}
