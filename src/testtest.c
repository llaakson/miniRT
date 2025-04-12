#include "../include/miniRT.h"

int main(void)
{
	char *str = "-40.0,50.0,0.0";
	char **splitt;
	splitt = ft_split(str, ',');
	int i = 0;
	while (splitt[i])
	{
		printf("%s\n", splitt[i]);
		i++;
	}
	if (i - 1 != 2 || !splitt[2])
		error_exit("RGB colors must be three");
}