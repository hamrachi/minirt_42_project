/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:03:52 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 17:12:53 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

static int	count_words_b(const char *input_text, char delimiter)
{
	int	word_count;

	word_count = 0;
	while (*input_text)
	{
		while (*input_text && *input_text != delimiter)
			input_text++;
		while (delimiter && *input_text && *input_text == delimiter)
			input_text++;
		word_count++;
	}
	return (word_count);
}

static char	*allocate_word_b(const char *input_text, char delimiter, \
	t_heap_track **g_garbage_collector)
{
	char	*word_buffer;
	int		char_count;

	char_count = 0;
	while (input_text[char_count] && input_text[char_count] != delimiter)
		char_count++;
	word_buffer = gc_malloc_b(g_garbage_collector, \
		sizeof(char) * (char_count + 1));
	if (word_buffer == 0)
		return (0);
	ft_strlcpy_b(word_buffer, input_text, char_count + 1);
	return (word_buffer);
}

char	**process_tokens_b(char **result_array, const char *input_string, \
	char delimiter, t_heap_track **g_garbage_collector)
{
	int	array_index;

	array_index = 0;
	while (*input_string)
	{
		result_array[array_index] = \
			allocate_word_b(input_string, delimiter, g_garbage_collector);
		if (result_array[array_index] == NULL)
			return (NULL);
		while (*input_string && *input_string != delimiter)
			input_string++;
		while (*input_string && *input_string == delimiter)
			input_string++;
		array_index++;
	}
	result_array[array_index] = 0;
	return (result_array);
}

char	**ft_split_b(const char *input_string, char delimiter, \
	t_heap_track **g_garbage_collector)
{
	char	**result_array;
	int		word_count;

	if (input_string == 0)
		return (0);
	while (*input_string && *input_string == delimiter)
		input_string++;
	word_count = count_words_b(input_string, delimiter);
	result_array = gc_malloc_b(g_garbage_collector, \
		sizeof(char *) * (word_count + 1));
	if (result_array == 0)
		return (0);
	return (process_tokens_b(result_array, input_string, \
		delimiter, g_garbage_collector));
}
