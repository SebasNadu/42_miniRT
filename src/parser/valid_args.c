/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:24 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/29 08:20:43 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	triplets(char **triple, double min, double max, t_line_parse_env *env)
{
	if (ft_strarr_len(triple) != 3)
	{
		free_s(triple);
		triple = NULL;
		return (file_error(env, find_error(env->error_type)));
	}
	env->error_type++;
	if (!str_valid_numbers(triple))
	{
		free_s(triple);
		triple = NULL;
		return (file_error(env, find_error(env->error_type)));
	}
	env->error_type++;
	if (!are_in_range(triple, min, max))
	{
		free_s(triple);
		triple = NULL;
		return (file_error(env, find_error(env->error_type)));
	}
	return (0);
}

int	solo(char *number, double min, double max, t_line_parse_env *env)
{
	double	ratio;

	if (!is_valid_number(number))
		return (file_error(env, find_error(env->error_type)));
	ratio = ft_atof(number);
	env->error_type++;
	if (!is_in_range(ratio, min, max))
		return (file_error(env, find_error(env->error_type)));
	return (0);
}
