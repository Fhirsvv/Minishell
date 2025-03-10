/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:32:49 by ecortes-          #+#    #+#             */
/*   Updated: 2025/02/01 19:05:33 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	if (!s1)
		return (NULL);
	result = malloc(ft_strlen(s1) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
