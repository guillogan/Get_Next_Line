#include <stdio.h>

char *read_line(int fd, char *buffer)
{
	printf("Yes\n");
	return "";
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*str;

	buffer = read_line(fd, buffer);
	printf("Fin de GNL\n");
	return (str);
}

int main(void)
{
	get_next_line(0);
	return (0);
}