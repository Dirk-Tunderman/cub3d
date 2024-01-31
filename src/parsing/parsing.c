#include "../../inc/cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>



char *str_n_copy(const char *src, int start)
{
    int i = 0;
    char *dest = NULL;

    dest = malloc(sizeof(char) * (ft_strlen(src) - start + 1));
    if (dest == NULL)
        return NULL;
    while (src[start] != '\0')
    {
        dest[i] = src[start];
        i++;
        start++;
    }
    dest[i] = '\0';
    return dest;


}

int check_position(char *line, char *dir)
{
    // check if the string dir is on the first occurence in the string
    // skip spaces and tabs
    printf("line: %s\n", line);
    printf("dir=  %s\n", dir);
    int i = 0;
    int j = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    //now dir has to be at position i
    while (dir[j] != '\0')
    {
        if (line[i] != dir[j])
            return 1;
        i++;
        j++;
    }
    //check here if file after dir is a image file, try to open it
    //if it is not an image file, return 1
    //if it is an image file, return 0
    //first skip white spaces
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    //now take string until end of line and check if you can open this string
    int fd = 0;
    char *str = NULL;
    str = str_n_copy(line, i);

    // fd = open(str, O_RDONLY);
    // if (fd == -1)
    // {
    //     printf("e")
    //     free(str);
    //     return 1;
    // }
    free(str);
    return 0;
}




int check_three_variables(char *line) // check ook max 255 and min 0
{
    int i = 0;
    int count = 0;
    int count_lenght = 0;

    while (line[i] != '\0')
    {
        //if line[i] is a number
        if (line[i] >= '0' && line[i] <= '9')
        {
            count++;
            while (line[i] >= '0' && line[i] <= '9')
            {
                i++;
                count_lenght++;
            }
            if (count_lenght > 3)
                return 2;
            count_lenght = 0;
        }
        else
            i++;
    }
    if (count != 3)
    {
        printf("count = %d\n", count);
        return 2;
    }
    return 0;
}

int is_valid_format(const char *str) {
    if (str == NULL) return false;

    // Start parsing from the first digit or comma
    while (*str && !ft_isdigit(*str) && *str != ',') str++;

    while (*str) {
        // Check for leading zeros in a number (excluding standalone zero)
        if (*str == '0' && ft_isdigit(*(str + 1))) {
            return 3;  // Found a leading zero followed by another digit
        }

        // Move to the next comma, skipping current number
        while (*str && *str != ',') str++;

        // If comma is found, move to the next character and check again
        if (*str == ',') {
            str++;  // Skip the comma
            // Skip any white spaces after comma
            while (*str && ft_isspace(*str)) str++;

            // Check again for leading zero in the next number
            if (*str == '0' && ft_isdigit(*(str + 1))) {
                return 3;
            }
        }
    }

    return 0;
}


int ft_isspace(int c) {
    return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v');
}

int check_position_c(char *line, char *dir)
{
    // check if the string dir is on the first occurence in the string
    // skip spaces and tabs

    int i = 0;
    int j = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    //now dir has to be at position i
    while (dir[j] != '\0')
    {
        if (line[i] != dir[j])
        {
            printf("return here");
            return 1;
        }
        i++;
        j++;
    }

    //next character is between 0 and 9
    if (line[i] < '0' || line[i] > '9')
        return 1;

    while (line[i] == ' ' || line[i] == '\t')
        i++;

    return 0;
}



int validate_numbers_in_range(const char *str) {
    if (str == NULL) return 4;

    while (*str) {
        // Skip non-digit characters
        while (*str && !ft_isdigit(*str) && *str != '-') str++;

        // If end of string is reached, break
        if (!*str) break;

        // Extract number
        char *next;
        long num = strtol(str, &next, 10);

        // Check range
        if (num < 0 || num > 255) {
            return 4;
        }

        // Move to next part of the string
        str = next;
    }

    return 0;  // Return 0 if all numbers are valid
}


int check_top_map(char **cub, int f_l)
{
    int i = 0;
    int error = 0;
    int count = 0;

    while (i < f_l)
    {
        if (ft_strnstr(cub[i], "NO ", ft_strlen(cub[i])))
        {
            printf("NO\n");
            error = check_position(cub[i], "NO ");
            if (error == 1)
                return -1;
            count++;
        }
        if (ft_strnstr(cub[i], "SO ", ft_strlen(cub[i])))
        {
            error = check_position(cub[i], "SO ");
            if (error == 1)
                return -1;
            count++;
        }
        if (ft_strnstr(cub[i], "WE ", ft_strlen(cub[i])))
        {
            printf("WE\n");
            printf("cub[i] = %s", cub[i]);
            error = check_position(cub[i], "WE ");
            if (error == 1)
                return -1;
            count++;
        }
        if (ft_strnstr(cub[i], "EA ", ft_strlen(cub[i])))
        {
            error = check_position(cub[i], "EA ");
            if (error == 1)
                return -1;
            count++;
        }
        if (ft_strnstr(cub[i], "C ", ft_strlen(cub[i])))
        {
            error = check_position_c(cub[i], "C ");
            if (error != 0)
                return -1;
            error = check_three_variables(cub[i]);
            if (error != 0)
                return -1;
            error = is_valid_format(cub[i]);
            if (error != 0)
                return -1;
            error = validate_numbers_in_range(cub[i]);
            if (error != 0)
                return -1;

            count++;
        }
        if (ft_strnstr(cub[i], "F ", ft_strlen(cub[i])))
        {
            error = check_position_c(cub[i], "F ");
            if (error != 0)
                return -1;
            error = check_three_variables(cub[i]);
            if (error != 0)
                return -1;
            error = is_valid_format(cub[i]);
            if (error != 0)
                return -1;
            error = validate_numbers_in_range(cub[i]);
            if (error != 0)
                return -1;

            count++;
        }
        i++;
    }
    if (count != 6)
        return -1;
    return 1;

}


int check_first_line_map(char *line)
{
    int i = 0;

    //skip white spaces
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    while(line[i] == '1')
        i++;
    //skip white spaces
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '\0')
        return -1;
    printf("finshed first line\n");
    return 1;
    
}


int check_up_and_main(char *main, char *up)
{
    //get string length of cub[i]
    //get string length of cub[i + 1]

    int len_up = ft_strlen(up);
    printf("len_up = %d\n", len_up);
    printf("up = %s\n", up);

    int len_main = ft_strlen(main);
    printf("len_main = %d\n", len_main);
    printf("main = %s\n", main);

    int i = 0;

    while (i < len_main)
    {
       if (main[i] == '0' || main[i] == 'N' || main[i] == 'S' || main[i] == 'E' || main[i] == 'W')
        {
            if (i >= len_up || up[i] == ' ' || main[i + 1] == ' ' || main[i - 1] == ' ')
            {
                printf("i = %d\n", i);
                return -1;
            }
        }
        if (main[i] == ' ')
        {
            if (up[i] == '0' || up[i] == 'N' || up[i] == 'S' || up[i] == 'E' || up[i] == 'W')
            {
                printf("i = %d\n", i);
                return -1;
            }
        }
        i++;
    }
    printf("finished check up and main\n");
    return 1;
}

int check_map_loop(char **cub, int f_l)
{
    int i = f_l;

    int error = 0;
    i++;
    while (cub[i] != NULL)
    {
        error = check_up_and_main(cub[i], cub[i - 1]); // check if the line above is a wall
        printf("errorin main loop = %d\n", error);
        if (error == -1)
            return -1;
        i++;
    }
    return 1;
}


int check_ends_line(char *line, int start)
{
    int i = 0;

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '1')
    {
        printf("begiiining not 1\n");
        return -1;
    }
    while (line[i] == '1' || line[i] == '0' || 
            line[i] == 'N' || line[i] == 'S' || 
                line[i] == 'E' || line[i] == 'W' || line[i] == ' ') // as long as it is a wall, open space or player
    {
        i++;
    }
    if (line[i - 1] != '1') // if the last character is not a wall
    {
        printf("line[i] = %c\n", line[i]);
        printf("end not 1\n");
        return -1;
    }
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '\0')
    {
        printf("end not \\0\n");
        return -1;
    }
    
    return 1;
}

int check_last_line(char *line)
{
    int i = 0;

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '1')
        return -1;
    while (line[i] == '1' || line[i] == ' ')
        i++;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '\0')
        return -1;
    return 1;
}

int check_endings_map(char **cub, int start)
{
    int error = 0;

    start++; // skip firstline
    while (cub[start] != NULL)
    {
        error = check_ends_line(cub[start], start);
        printf("cub[start] = %s\n", cub[start]);
        printf("error in endings = %d\n", error);
        if (error == -1)
        {
            printf("error in endingzzzz\n");
            return -1;
        }
        start++;
    }
    error = check_last_line(cub[start - 1]);
    if (error == -1)
    {
        printf("error in last line\n");
        return -1;
    }
    printf("finished check endings\n");
    return 1;
}


void    get_start_direction(char c, t_data *data)
{
    if (c == 'N')
        data->start_direction = NORTH;
    if (c == 'S')
        data->start_direction = SOUTH;
    if (c == 'E')
        data->start_direction = EAST;
    if (c == 'W')
        data->start_direction = WEST;

}

int check_player(char **cub, int start, t_data *data)
{
    //loop though the whole map
    int i = 0;
    int p = 0;


    while (cub[start] != NULL)
    {
        while (cub[start][i] != '\0')
        {
            if (cub[start][i] == 'E' || cub[start][i] == 'W' || cub[start][i] == 'N' || cub[start][i] == 'S')
            {
                printf("i = %d\n", i);
                data->x_player = i;
                printf("data.x_player = %d\n", data->x_player);
                printf("start = %d\n", start);
                data->y_player = start;
                printf("cube[start][i] = %c\n", cub[start][i]);
                cub[start][i] = '0';
                get_start_direction(cub[start][i], data);
                printf("start direction = %d", data->start_direction);
                p++;
            }
            i++;
        }
        i = 0;
        start++;
    }
    if (p != 1)
    {
        printf("p = %d\n", p);
        return -1;
    }
    return 1;
}


int check_map(char **cub, int f_l, t_data *data)
{
    int error = 0;

    printf("cub[f_l] = %s\n", cub[f_l]);
    error = check_first_line_map(cub[f_l]);
    if (error == -1)
        return -1;
    error = check_map_loop(cub, f_l);
    if (error == -1)
        return -1;
    printf("error after main loop = %d\n", error);
    error = check_endings_map(cub, f_l);
    if (error == -1)
        return -1;
    error = check_player(cub, f_l, data);
    if (error == -1)
        return -1;
    return error;


}


int find_first_line_mapp(char **original_array) // does not take into consideration map error
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


int    parsing(char **twod, t_data *data) {

    int error = 0;
    int f_l = 0;
    //find beginning map
    f_l = find_first_line_map(twod); // 
    printf("f_l = %d\n", f_l);
    //check above map
    error = check_top_map(twod, f_l);
    if (error == -1)
    {
        printf("error top map");
        return -1;
    }


    error = check_map(twod, f_l, data);
    if (error == -1)
    {
        printf("error low map");
        return -1;
    }

    printf("error = %d\n", error);

    //check map
    
    return 1;
}

