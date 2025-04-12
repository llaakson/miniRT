/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:38:57 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/12 19:29:18 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void free_2d_array(char ***arr)
{
	int i;

	if (!arr || !*arr)
		return;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void error_exit(char *error)
{

	printf("Error: %s\n", error);
	tracked_free_all();
	exit(1);
}

void free_and_set_to_null(char **str)
{
	if (str && *str)
		free(*str);
	*str = NULL;
}