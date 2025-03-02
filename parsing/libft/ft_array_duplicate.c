/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_duplicate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:58:48 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 18:55:53 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	if (!split_arr)
		return ;
	while (split_arr[i])
	{
		free(split_arr[i]);
		split_arr[i] = NULL;
		i++;
	}
	free(split_arr);
	split_arr = NULL;
}

char	**ft_array_duplicate(char **arr)
{
	char	**aux;
	size_t	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
		i++;
	aux = ft_calloc(sizeof(char *), i + 1);
	if (!aux)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		aux[i] = ft_strdup(arr[i]);
		if (aux[i] == NULL)
		{
			free_arr(aux);
			return (aux);
		}
		i++;
	}
	return (aux);
}
