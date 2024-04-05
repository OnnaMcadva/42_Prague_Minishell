#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_data
{
	char *string_one;
	char *string_two;
}				t_data;

void andagain(char * const str)
{
	str[0] = 'C';
	// str++; is illegal here
	printf("%s", str);
}

void sendagain(const char *str)
{
	str++;
	// str[0] = 'C'; is illegal here
	printf("%s", str);
}

void sendme(t_data *data)
{
	printf("%s", data->string_one);
	sendagain(data->string_one);
	andagain(data->string_one);
}

int main()
{
	t_data	data;

	data.string_one = strdup("check, check\n");
	printf("%s", data.string_one);
	sendme(&data);
	printf("%s", data.string_one);
	free(data.string_one);
}
