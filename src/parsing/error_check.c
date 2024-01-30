#include "../../inc/cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int find_first_line_map(char **original_array)
{
    int index = 0;
    int i = 0;

    while (original_array[index] != NULL) 
    {
        while (original_array[index][i] == ' ' || original_array[index][i] == '\t')
            i++;
        if (original_array[index][i] == '1' || original_array[index][i] == '0') 
            return index;
        else
            index++;
    }
    return -1;
}

bool is_boundary_line(const char *line) {
    while (*line != '\0') {
        if (*line != '*') {
            return false;
        }
        line++;
    }
    return true;
}

char **extract_map(char **original_array, int original_height) 
{
    int index_first_map_line = find_first_line_map(original_array);
    if (index_first_map_line == -1) 
        exit(1);
    char **map = malloc(sizeof(char *) * (original_height - (original_height - index_first_map_line) + 1 + 1));
    if (map == NULL) {
        printf("Error: Failed to allocate memory for map.\n");
        return NULL;
    }
    int i = 1;
    printf("until here\n");
    int longest_line = get_l_line(original_array);
    printf("longest_line = %d\n", longest_line);
    map[0] = malloc(sizeof(char) * (longest_line + 1));
    int j = 0;
    while (j < longest_line) {
        map[0][j] = '*';
        j++;
    }
    map[0][j] = '\0';
    while (i < original_height - (original_height - index_first_map_line) + 1) {
        map[i] = original_array[index_first_map_line + i - 1];
        i++;
    }
    map[i] = malloc(sizeof(char) * (longest_line + 1));
    j = 0;
    while (j < longest_line) {
        map[i][j] = '*';
        j++;
    }
    map[i][j] = '\0';
    i++;
    map[i] = NULL;
    return map;
}

int get_l_line(char **array) 
{
    int i = 0;
    int longest_line = 0;
    int current_line_length = 0;

    while (array[i] != NULL) {
        current_line_length = ft_strlen(array[i]);
        printf("array: %s\n", array[i]);
        if (current_line_length > longest_line) {
            longest_line = current_line_length;
        }
        i++;
    }
    printf("longest_line = %d\n", longest_line);
    return longest_line;
}

void 	error_check(char **old_map, int original_height)
{

    printf("original_height = %d\n", original_height);
    char **new_map = extract_map(old_map, original_height);

    printf("mapfirsline: %s\n", new_map[0]);
    // if (map == NULL) {
    //     printf("Error: No valid map found.\n");
    //     return;
    // }

    // Perform error checks on the map
    // ...

    // Free the map array after checking
//     for (int i = 0; i < map_height; i++) {
//         free(map[i]);
//     }
//     free(map);
}