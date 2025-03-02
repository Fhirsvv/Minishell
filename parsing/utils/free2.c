/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:11:57 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 18:51:10 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void free_tcoms(t_myshell *ms)
{
	t_com *caux;
	t_com *cauxnext;
	t_files *faux;
	t_files *fauxnext;

	caux = ms->t_com;
	fauxnext = NULL;
	cauxnext = NULL;
	while (caux)
	{
		cauxnext = caux->next;
		faux = caux->files;
		while (faux)
		{
			fauxnext = faux->next;
			free(faux);
			faux = fauxnext;
		}
		faux = NULL;
		free_arr(caux->args);
		ft_free(caux->env_path);
		free(caux);
		caux = cauxnext;
	}
	ms->t_com = NULL;
}
