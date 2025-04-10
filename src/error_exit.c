/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:38:57 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/10 20:33:00 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void error_exit(char *error, t_minirt **data)
{
	static t_minirt *ptr = NULL;
	if (data && *data)
	{
		ptr = *data;
		return ;
	}
	printf("Error: %s\n", error);
	if (ptr)
		free(ptr);
	//free data if data
	exit(1);
}

void free_and_set_to_null(char **str)
{
	if (str && *str)
		free(*str);
	*str = NULL;
}