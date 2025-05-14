#include "get_next_line.h"

char *ft_strdup(char *str)
{
	int i;
	char *save;

	i = 0;
	while (str[i] != 0)
		i++;
	save = malloc(sizeof(char) * (i + 1));
/* 	if (!save)
		return (NULL); */
	i = 0;
	while (str[i])
	{
		save[i] = str[i];
		i++;
	}
	save[i] = '\0';
	return (save);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_read;
	static int	buffer_pos;
	int i;
	char		line[70000];

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break;
		}
		line[i] = buffer[buffer_pos++];
		i++;
		if (buffer[buffer_pos] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int main()
{
	int fd = open("t.txt", O_RDONLY);

	printf("%s\n", get_next_line(fd));
}
