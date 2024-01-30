/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:57:12 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 18:14:34 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*make_leftover_line(char *return_line)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	j = 0;
	while (return_line[i] != '\n')
	{
		if (return_line[i] == '\0')
			return (free(return_line), NULL);
		i++;
	}
	new_str = (char *)malloc((ft_strlen(return_line) - i + 1) * sizeof(char));
	if (!new_str)
		return (free(return_line), NULL);
	i++;
	while (return_line[i])
	{
		new_str[j] = return_line[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (free(return_line), new_str);
}

char	*make_output_line(char *raw_line)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!raw_line[0])
		return (NULL);
	while (raw_line[i] != '\n' && raw_line[i])
		i++;
	if (raw_line[i] == '\0')
		i--;
	new_line = (char *)malloc((i + 2) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (raw_line[i] && raw_line[i] != '\n')
	{
		new_line[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*make_raw_line(char *line, char *buffer, int fd)
{
	int	total_bytes_read;

	total_bytes_read = 42;
	while (!ft_strchr(line, '\n') && total_bytes_read)
	{
		total_bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (total_bytes_read == -1)
			return (free(line), NULL);
		buffer[total_bytes_read] = 0;
		if (!line)
		{
			line = (char *)malloc(1 * sizeof(char));
			if (!line)
				return (NULL);
			line[0] = '\0';
		}
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*output_line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&line), NULL);
	line = make_raw_line(line, buffer, fd);
	free(buffer);
	if (!line)
		return (NULL);
	output_line = make_output_line(line);
	if (!output_line)
		return (ft_free(&line), NULL);
	line = make_leftover_line(line);
	return (output_line);
}
