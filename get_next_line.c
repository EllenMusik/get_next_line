/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteiner <esteiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:56:06 by esteiner          #+#    #+#             */
/*   Updated: 2023/02/15 20:24:49 by esteiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
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

	// printf("remainders1: %s \n", s1);
	// printf("buffers2: %s\n", s2);
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

char	*read_line(int fd, int *check)
{
	char	*buffer;
	int		nbr;

	nbr = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	nbr = read(fd, buffer, BUFFER_SIZE);
	if (nbr == -1)
	{
		return (free(buffer), NULL);
	}
	if (nbr == 0)
		*check = 1;
	buffer[nbr] = '\0';
return (buffer);
}

char	*get_line(char **remainder, char *nl)
{
	char	*line;
	char	*temp;
	int		i;

	i = -1;
	temp = NULL;
	line = malloc(sizeof(char) * (ft_strlen(*remainder) - ft_strlen(nl) + 1));
	if (!line)
		return (NULL);
	while ((*remainder)[++i] != '\n')
		line[i] = (*remainder)[i];
	line[i] = (*remainder)[i];
	line[i + 1] = '\0';
	i = -1;
	temp = malloc(sizeof(char) * (ft_strlen(nl) + 1));
	if (!temp)
		return (NULL);
	while (nl[++i] != '\0')
		temp[i] = nl[i];
	temp[i] = '\0';
	*remainder = temp;
	return (line);
}

char	*get_last_line(char **remainder)
{
	int		i;
	char	*str;

	//printf("wh oh why\n");
	i = 0;
	str = malloc(sizeof(char) * ft_strlen(*remainder));
	while ((*remainder)[i] != '\0')
	{
		str[i] = (*remainder)[i];
		i++;
	}
	str[i] = '\0';
	free(*remainder);
	*remainder = NULL;
	//printf("remainder: %s \n", *remainder);
	return (str);
}

char	*check_for_nl(char **remainder, int fd, int *check)
{
	char	*nl_char;
	char	*str;
	char	*temp;

	str = NULL;
	nl_char = NULL;
	temp = NULL;
	//printf("remainder??: %s", *remainder);
	if (ft_strchr(*remainder, '\n'))
		nl_char = ft_strchr(*remainder, '\n');
	if ((!ft_strchr(*remainder, '\n')) && *check == 0)
	{
		str = read_line(fd, check);
		if (!str)
			return (NULL);
		//printf("remainder2: %s", *remainder);
		temp = ft_strjoin((*remainder), str);
		free(str);
		if (!temp)
			return (NULL);
		*remainder = temp;
		str = check_for_nl(remainder, fd, check);
	}
	else if (*check == 0)
		str = get_line(remainder, nl_char);
	else if (*check == 1)
		str = get_last_line(remainder);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;
	int			check;

	//printf("remainder: %s \n", remainder);
	check = 0;
	line = NULL;
	if (fd < 0)
		return (NULL);
	if (!remainder)
		remainder = read_line(fd, &check);
	if (remainder)
		line = check_for_nl(&remainder, fd, &check);
	if (!line)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open ("text", O_RDONLY);
	//printf("\033[0;31mhallo\e[0m\n");
	printf("fd: %i\n", fd);
	printf("\033[0;31mRETURN1:\e[0m %s\n", get_next_line(fd));
	printf("\033[0;31mRETURN2:\e[0m %s\n", get_next_line(fd));
	printf("\033[0;31mRETURN3:\e[0m %s\n", get_next_line(fd));
	printf("\033[0;31mRETURN4:\e[0m %s\n", get_next_line(fd));
	// printf("\033[0;31mRETURN5:\e[0m %s\n", get_next_line(fd));
	// printf("\033[0;31mRETURN6:\e[0m %s\n", get_next_line(fd));
	close (fd);
	return (0);
}
