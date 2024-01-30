/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:57:18 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 18:14:26 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../inc/get_next_line.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char *line, char *buff)
// {
// 	char	*new_str;
// 	size_t	new_str_length;
// 	size_t	i;
// 	size_t	j;

// 	new_str_length = ft_strlen(line) + ft_strlen(buff);
// 	new_str = (char *)malloc((new_str_length + 1) * sizeof(char));
// 	if (!new_str)
// 		return (free(line), NULL);
// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		new_str[i] = line[i];
// 		i++;
// 	}
// 	while (buff[j])
// 	{
// 		new_str[i] = buff[j];
// 		i++;
// 		j++;
// 	}
// 	new_str[new_str_length] = '\0';
// 	return (free(line), new_str);
// }

// size_t	ft_strchr(char *s, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

char	*ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}
