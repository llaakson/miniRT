/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:38:05 by llaakson          #+#    #+#             */
/*   Updated: 2025/04/25 10:29:41 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
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
		if (prev / 10 != result && sign == -1)
			return (0);
		if (prev / 10 != result && sign == 1)
			return (-1);
		result = prev;
	}
	return (result * sign);
}
