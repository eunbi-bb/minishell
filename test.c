#include <stdio.h>
#include "libft/libft.h"

int	main(void)
{
	char	*str1 = "abc";
	char	*str2 = "def";

	char	*dst = "";

	dst = ft_strjoin(dst, str1);
	dst = ft_strjoin(dst, str2);
	printf("%s\n", dst);

	return (0);
}