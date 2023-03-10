/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteiner <esteiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:34:09 by esteiner          #+#    #+#             */
/*   Updated: 2023/02/16 20:18:31 by esteiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	if (!s)
		return (0);
	while (s[x])
		x++;
	return (x);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i + 1]);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		k;

	i = ft_strlen(s1) + 1;
	k = ft_strlen(s2) + 1;
	s3 = malloc(sizeof(char) * (i + k));
	if (!s3)
		return (NULL);
	i = -1;
	k = 0;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[k])
		s3[i++] = s2[k++];
	s3[i] = '\0';
	return (s3);
}
