/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_free2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:09:26 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/26 17:18:45 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_loader.h"

void	destroy_mutex(t_obj_loader *loader)
{
	if (!loader)
		return ;
	if (loader->lines)
		free_matrix(&loader->lines);
	pthread_mutex_destroy(&loader->v_mutex);
	pthread_mutex_destroy(&loader->n_mutex);
	pthread_mutex_destroy(&loader->t_mutex);
	pthread_mutex_destroy(&loader->gp_mutex);
	pthread_mutex_destroy(&loader->ig_lines_mutex);
	pthread_mutex_destroy(&loader->mtl_mutex);
	pthread_mutex_destroy(&loader->uv_mutex);
}

void	free_loader_last(t_obj_loader *loader)
{
	if (!loader)
		return ;
	if (loader->triangles)
	{
		free(loader->triangles);
		loader->triangles = NULL;
	}
	if (loader->groups)
	{
		free(loader->groups);
		loader->groups = NULL;
	}
	loader->default_group->group.count = 0;
	loader->default_group->group.root = NULL;
	if (loader->mtl_loader)
	{
		free_mtl_loader_textures(loader);
		free_mtl_loader(loader, true);
	}
}

void	free_mtl_loader_textures(t_obj_loader *loader)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	if (!loader)
		return ;
	while (++i < loader->mtl_count)
	{
		j = -1;
		while (++j < loader->mtl_loader[i].m_count)
		{
			k = -1;
			while (++k < 8)
			{
				if (loader->mtl_loader[i].materials[j].pattern.texture[k])
				{
					mlx_delete_texture(loader->mtl_loader[i].materials[j]
						.pattern.texture[k]);
					loader->mtl_loader[i].materials[j]
						.pattern.texture[k] = NULL;
				}
			}
		}
	}
}
