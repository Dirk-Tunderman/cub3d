/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:43:17 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 18:35:14 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>   // For open


#define INITIAL_CAPACITY 10



static char **process_line(char **array, char *line, int *num_rows)
{
    size_t read = strlen(line);  // Calculate the length of the line
    if (line[read - 1] == '\n')
        line[read - 1] = '\0';
    array[*num_rows] = malloc((read + 1) * sizeof(char));
    if (!array[*num_rows])
        return (NULL);
    strcpy(array[*num_rows], line);
    (*num_rows)++;
    return (array);
}



static char **resize_array(char **array, int *capacity, int num_rows)
{
    *capacity *= 2;
    char **temp = realloc(array, (*capacity + 1) * sizeof(char *)); // +1 for null termination
    if (!temp)
    {
        for (int i = 0; i < num_rows; i++)
            free(array[i]);
        free(array);
        return (NULL);
    }
    return (temp);
}



static char **initialize_array(int *capacity)
{
    char **array = malloc((*capacity + 1) * sizeof(char *)); // +1 for null termination
    if (!array)
        return (NULL);
    return (array);
}

static char **read_and_store_lines(int fd, char **array, int *num_rows, int *capacity) {

    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        if (*num_rows == *capacity) {
            array = resize_array(array, capacity, *num_rows);
            if (!array) {
                free(line);
                return (NULL);
            }
        }
        array = process_line(array, line, num_rows);
        free(line);
        if (!array)
            break;
    }
    return array;
}


char **read_cub_file_to_2d_array(const char *filename, int *num_rows) {
    int fd;
    char **array;
    int capacity = INITIAL_CAPACITY;  // Declare capacity

    *num_rows = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (NULL);
    array = initialize_array(&capacity);
    if (!array) {
        close(fd);
        return (NULL);
    }

    array = read_and_store_lines(fd, array, num_rows, &capacity);
    if (array)
        array[*num_rows] = NULL;  // Null-terminate the array
    close(fd);
    return array;
}



int count_rows_in_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    int num_rows = 0;
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        num_rows++;
        free(line);
    }

    close(fd);
    return num_rows;
}

