/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:01:55 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/24 15:22:42 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*	
	DESCRIPTION
		A to interger. 
		Convert character(string) to integer.
	RETUTRN VALUE
		returns converted integral number.
*/

int	ft_atoi(const char *str)
{
	int			i;
	long long	num;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (num * sign > 2147483647)
			return (-1);
		else if (num * sign < -2147483648)
			return (0);
		else
			num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}
