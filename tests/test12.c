#include <stdio.h>

char	*ft_strcpy(char *dest, const char *src)
{
	char	*new_dest;

	if (!dest || !src)
		return (NULL);
	new_dest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (new_dest);
}


int main()
{
	char *str;

	printf ("%s\n", ft_strcpy(str, "hello"));
}
