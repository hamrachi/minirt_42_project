/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:31:26 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/08 22:06:36 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

char *append_char_to_string(char *original, char new_char)
{
    char *new_str;  
    size_t  i;        // Pointer for the resulting string.
    size_t original_len; // Length of the original string.

    original_len = 0;
    // Calculate the length of the original string.
    if (original)
        while (original[original_len])
            original_len++;
    // Allocate memory for the new string (1 for the new char and 1 for the null terminator).
    new_str = malloc((original_len + 2) * sizeof(char));
    if (!new_str)
        return (NULL);
    // Copy the original string into the new string.
    for (i = 0; i < original_len; i++)
        new_str[i] = original[i];
    // Add the new character and null terminator.
    new_str[original_len] = new_char;
    new_str[original_len + 1] = '\0';
    // Free the old string and return the new one.
    free(original);
    return (new_str);
}


// Helper function to handle the reading of characters and building the line
static char *read_line(int fd, char *line)
{
    char c;

    while (read(fd, &c, 1))
    {
        // Skip over newline characters if `line` is still NULL.
        if (c == '\n' && line == NULL)
            continue;

        // Stop reading upon encountering a newline (excluding the first one).
        if (c == '\n')
        {
            if (line && line[0] == '#')
            {
                free(line);
                line = NULL;
                continue;
            }
            break;
        }

        // Append the character to the line.
        line = append_char_to_string(line, c);
        if (!line) // Handle memory allocation failure.
            close(fd),report_error("line allocation error"),exit(2); 
    }

    return (line);
}

// Main line function
char *line(int fd)
{
    static char *line = NULL;

    // Free the previous line if it exists.
    if (line)
    {
        free(line);
        line = NULL;
    }

    // Read characters and build the line.
    line = read_line(fd, line);

    // Return the constructed line (or NULL if nothing was read).
    return (line);
}

// char *line(int fd)
// {
//     char c;                    // Temporary storage for the character read.
//     static char *line;  // Static to preserve the line between function calls.

//     line = NULL;
//     // Free the previous line if it exists.
//     if (line)
//     {
//         free(line);
//         line = NULL;
//     }
//     // Read characters one by one from the file descriptor.
//     while (read(fd, &c, 1))
//     {
//         // Skip over newline characters if `line` is still NULL.
//         if (c == '\n' && line == NULL)
//             continue;
//         // Stop reading upon encountering a newline (excluding the first one).
//         if (c == '\n')
//         {
//             if (line && line[0] == '#')
//             {
//                 free(line);
//                 line = NULL;
//                 continue;
//             }
//             break;
//         }
//         // Append the character to the line.
//         line = append_char_to_string(line, c);
//         if (!line) // Handle memory allocation failure.
//             return (NULL);
//     }
//     // Return the constructed line (or NULL if nothing was read).
//     return (line);
// }
