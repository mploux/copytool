/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 22:16:25 by mploux            #+#    #+#             */
/*   Updated: 2016/12/30 19:49:47 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_mapadd(t_map **map, t_map *new)
{
	if (!map)
		return ;
	new->next = *map;
	*map = new;
}