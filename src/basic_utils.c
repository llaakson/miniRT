/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:18:04 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/30 11:32:40 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	is_whitespace(char c)
{
	if ((c == 32) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (1);
	}
	return (0);
}

static void	atof_decimal(char *str, int i, double *res_as_double)
{
	double	decimal_place;

	decimal_place = 0.1;
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*res_as_double += (str[i] - '0') * decimal_place;
		decimal_place *= 0.1;
		i++;
	}
	if (str[i] == '.')
		error_exit("Extraneous decimal point found in number");
}

double	ft_atof(char *str, double *result)
{
	int		i;
	double	sign;
	double	res_as_double;

	i = 0;
	sign = 1;
	res_as_double = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	no_extra_minus_in_str(str, i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res_as_double = res_as_double * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		atof_decimal(str, i, &res_as_double);
	if (res_as_double > DBL_MAX || res_as_double < -DBL_MAX)
		error_exit("double overflow detected");
	*result = (double)res_as_double * sign;
	return (0);
}

int	ft_atoi_overflow_checked(const char *str)
{
	int				sign;
	long long int	result;
	long long int	prev;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+' )
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		prev = result * 10 + *str++ - 48;
		result = prev;
	}
	if (result > INT_MAX || result < INT_MIN)
		error_exit("Integer overflow detected");
	return (result * sign);
}
