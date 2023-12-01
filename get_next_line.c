/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_recursive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:46:08 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/29 12:31:57 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	calculate_merged_length(char *line, char *buffer, char *end_of_line)
{
	int		len;

	len = 0;
	if (line)
		len += ft_strlen(line);
	len += ft_strlen(buffer);
	if (end_of_line)
		len -= ft_strlen(end_of_line + 1);
	return (len);
}

static char	*merge(char *line, char *buffer, char *end_of_line)
{
	int		old_len;
	int		new_len;
	char	*new_str;

	old_len = 0;
	new_len = calculate_merged_length(line, buffer, end_of_line);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (clean(line, NULL));
	if (line && *line)
	{
		old_len = ft_strlen(line);
		ft_memcpy(new_str, line, ft_strlen(line));
	}
	if (buffer && *buffer)
		ft_memcpy(new_str + old_len, buffer, new_len - old_len);
	new_str[new_len] = 0;
	return (clean(line, new_str));
}

static int	read_buffer(int fd, char *buffer, int *end_of_file)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (1);
	if (bytes_read < BUFFER_SIZE)
		*end_of_file = 1;
	buffer[bytes_read] = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			end_of_file;
	char		*end_of_line;

	line = NULL;
	end_of_file = 0;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		buffer[0] = 0;
		return (NULL);
	}
	while ("There is stuff to do")
	{
		if (*buffer == 0)
			if (read_buffer(fd, buffer, &end_of_file))
				return (clean(line, NULL));
		end_of_line = ft_strchr(buffer, '\n');
		line = merge(line, buffer, end_of_line);
		if (end_of_line)
			ft_memcpy(buffer, end_of_line + 1, ft_strlen(end_of_line + 1) + 1);
		if (!line || end_of_line || end_of_file)
			return (line);
		buffer[0] = 0;
	}
}
