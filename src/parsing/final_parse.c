#include "../../inc/cub3d.h"


void print_map(int **map, int rows, int cols) {
    printf("Map:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

void print_player_coordinates(int x, int y) {
    printf("Player Coordinates: X = %d, Y = %d\n", x, y);
}

void calculate_map_dimensions(char **cub, int *rows, int *cols) {
    *rows = 0;
    *cols = 0;

    // Find the start of the map in the cub array
    int i;
    for (i = 0; cub[i] != NULL && strncmp(cub[i], "111", 3) != 0; i++);
    //int map_start = i;

    // Calculate rows and columns
    for (; cub[i] != NULL; i++) {
        (*rows)++;
        int len = strlen(cub[i]);
        if (len > *cols) {
            *cols = len;
        }
    }
}


void final_parse(t_data *data, char **cub) {
    process_wall_textures(data, cub);
    process_floor_ceiling_colors(data, cub);

    // Print F and C colors
    if (data->F) {
        printf("F: %u, %u, %u\n", data->F[0], data->F[1], data->F[2]);
    } else {
        printf("F data not available\n");
    }

    if (data->C) {
        printf("C: %u, %u, %u\n", data->C[0], data->C[1], data->C[2]);
    } else {
        printf("C data not available\n");
    }

    process_map(data, cub);

    // Calculate the dimensions of the map
    int rows, cols;
    calculate_map_dimensions(cub, &rows, &cols);

    // Print the map and player coordinates
    print_map(data->map, rows, cols);
    print_player_coordinates(data->x_player, data->y_player);
}

void parse_rgb_values(uint32_t *color_array, const char *rgb_str) {
    for (int i = 0; i < 3; i++) {
        // Skip non-digits and commas
        while (*rgb_str && (*rgb_str < '0' || *rgb_str > '9')) {
            rgb_str++;
        }

        color_array[i] = parse_int(&rgb_str);

        // Move past the current number
        while (*rgb_str && (*rgb_str >= '0' && *rgb_str <= '9')) {
            rgb_str++;
        }
    }
}

// Helper function to parse a single integer from a string
int parse_int(const char **str) {
    int num = 0;
    while (**str && **str >= '0' && **str <= '9') {
        num = num * 10 + (**str - '0');
        (*str)++;
    }
    return num;
}

// Function to convert RGB strings to uint32_t
uint32_t rgb_to_uint32(const char *rgb_str) {
    int r, g, b;

    r = parse_int(&rgb_str);
    if (*rgb_str == ',') rgb_str++; // Skip comma
    g = parse_int(&rgb_str);
    if (*rgb_str == ',') rgb_str++; // Skip comma
    b = parse_int(&rgb_str);

    // Check for valid range
    if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) {
        return (r << 16) | (g << 8) | b; // Combining the values into a single uint32_t
    }

    return 0; // Return 0 on failure
}

void process_floor_ceiling_colors(t_data *data, char **cub) {
    for (int i = 0; cub[i] != NULL; i++) {
        if (strncmp(cub[i], "F ", 2) == 0) {
            data->F = malloc(3 * sizeof(uint32_t));
            parse_rgb_values(data->F, cub[i] + 2);
        } else if (strncmp(cub[i], "C ", 2) == 0) {
            data->C = malloc(3 * sizeof(uint32_t));
            parse_rgb_values(data->C, cub[i] + 2);
        }
    }
}
// Custom function to copy strings
char *ft_strdup(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (copy != NULL) {
        strcpy(copy, s);
    }
    return copy;
}

// Function to process the wall texture lines and store them in the data struct
void process_wall_textures(t_data *data, char **cub) {
    for (int i = 0; cub[i] != NULL; i++) {
        if (ft_strncmp(cub[i], "NO ", 3) == 0) {
            data->NO = ft_strdup(cub[i] + 3);
        } else if (ft_strncmp(cub[i], "SO ", 3) == 0) {
            data->SO = ft_strdup(cub[i] + 3);
        } else if (ft_strncmp(cub[i], "WE ", 3) == 0) {
            data->WE = ft_strdup(cub[i] + 3);
        } else if (ft_strncmp(cub[i], "EA ", 3) == 0) {
            data->EA = ft_strdup(cub[i] + 3);
        }
    }
}




int char_to_int(char c) {
    if (c == '1') return 1;
    if (c == '0' || c == ' ' || c == 'P') return 0;
    return -1; // For any unexpected character
}

void process_map(t_data *data, char **cub) {
    int rows = 0, cols = 0, i, j;

    // Find the start of the map in the cub array
    for (i = 0; cub[i] != NULL && strncmp(cub[i], "111", 3) != 0; i++);
    int map_start = i;

    // Count rows and columns
    for (; cub[i] != NULL; i++) {
        int len = strlen(cub[i]);
        if (len > cols) cols = len;
        rows++;
    }

    // Allocate memory for the map
    data->map = malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        data->map[i] = malloc(cols * sizeof(int));
    }

    // Process the map and save player position
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            // Using map_start in the logic
            char c = j < (int)strlen(cub[map_start + i]) ? cub[map_start + i][j] : ' ';
            data->map[i][j] = char_to_int(c);

            if (c == 'P') {
                data->x_player = j;
                data->y_player = i;
            }
        }
    }
}