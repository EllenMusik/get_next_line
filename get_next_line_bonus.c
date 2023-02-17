/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteiner <esteiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:56:06 by esteiner          #+#    #+#             */
/*   Updated: 2023/02/16 20:18:24 by esteiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		return (free(buffer), NULL);
	if (nbr == 0)
		*check = 1;
	buffer[nbr] = '\0';
	return (buffer);
}

char	*get_the_line(char **remainder, char *nl)
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
	free(*remainder);
	*remainder = temp;
	return (line);
}

char	*get_last_line(char **remainder)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(*remainder) + 1);
	while ((*remainder)[i] != '\0')
	{
		str[i] = (*remainder)[i];
		i++;
	}
	str[i] = '\0';
	free(*remainder);
	*remainder = NULL;
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*check_for_nl(char **remainder, int fd, int *check)
{
	char	*nl_char;
	char	*str;
	char	*temp;

	nl_char = NULL;
	if (ft_strchr(*remainder, '\n'))
		nl_char = ft_strchr(*remainder, '\n');
	else if ((!ft_strchr(*remainder, '\n')) && *check == 0)
	{
		str = read_line(fd, check);
		if (!str)
			return (NULL);
		temp = ft_strjoin((*remainder), str);
		free(str);
		if (!temp)
			return (NULL);
		free(*remainder);
		*remainder = temp;
		str = check_for_nl(remainder, fd, check);
	}
	if (nl_char && *remainder)
		str = get_the_line(remainder, nl_char);
	else if (*check == 1 && !nl_char && *remainder)
		str = get_last_line(remainder);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder[1042];
	int			check;

	check = 0;
	line = NULL;
	if (!remainder[fd])
		remainder[fd] = read_line(fd, &check);
	if (!remainder[fd])
		return (NULL);
	if (remainder[fd][0] == '\0' && check == 1)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	if (remainder[fd])
		line = check_for_nl(&remainder[fd], fd, &check);
	if (!line)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	char *mist = NULL;
// 	fd = open ("text", O_RDONLY);
// 	//printf("\033[0;31mhallo\e[0m\n");
// 	printf("fd: %i\n", fd);
// 	mist = get_next_line(fd);
// 	printf("\033[0;31mRETURN1:\e[0m %s\n______________\n", mist);
// 	if (mist)
// 		free(mist);
// 	mist = get_next_line(fd);
// 	printf("\033[0;31mRETURN2:\e[0m %s\n______________\n", mist);
// 	if (mist)
// 		free(mist);
// 	// mist = get_next_line(fd);
// 	// printf("\033[0;31mRETURN4:\e[0m %s\n______________\n", mist);
// 	// if (mist)
// 	// 	free(mist);
// 	// mist = get_next_line(fd);
// 	// printf("\033[0;31mRETURN1:\e[0m %s\n", mist);
// 	// if (mist)
// 	// 	free(mist);
// 	// mist = get_next_line(fd);
// 	// printf("\033[0;31mRETURN1:\e[0m %s\n", mist);
// 	// if (mist)
// 	// 	free(mist);
// 	// printf("\033[0;31mRETURN4:\e[0m %s\n", get_next_line(fd));
// 	// printf("\033[0;31mRETURN5:\e[0m %s\n", get_next_line(fd));
// 	// printf("\033[0;31mRETURN6:\e[0m %s\n", get_next_line(fd));
// 	close (fd);
// 	return (0);
// }
