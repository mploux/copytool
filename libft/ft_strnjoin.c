/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:10:10 by mploux            #+#    #+#             */
/*   Updated: 2017/03/05 04:48:41 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strnjoin(char const *s1, char const *s2,
												size_t size)
{
	size_t	i;
	size_t	l1;
	char	*data;

	i = 0;
	if (!s2)
		return (NULL);
	l1 = ft_strlen(s1);
	if (!(data = ft_strnew(size)))
		return (NULL);
	while (i < size)
	{
		if (i < l1)
			data[i] = s1[i];
		else
			data[i] = s2[i - l1];
		i++;
	}
	data[i] = 0;
	return (data);
}

char    *ft_coffee(const char *s1, const char *s2, int n)
{
	int		i;
	int		j;
	int		l;
	char	*res;


	l = ft_strlen(s1) + ft_strlen(s2);
	if (n > 0 || l < n)
		l = n;
	if (l == 0 || !(res = (char *)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	res[l] = 0;
	i = 0;
	while (s1 && s1[i] && i < l)
	{
		res[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2 && s2[++j] && i + j < l)
		res[i + j] = s2[j];
	return (res);
}
