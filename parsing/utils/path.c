/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:30:50 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 19:42:59 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char	*get_path(t_myshell *tshell)
{
	int		i;
	char	*envp_path;

	i = 0;
	envp_path = NULL;
	while (tshell->environ && tshell->environ[i])
	{
		if (ft_strncmp("PATH", tshell->environ[i], 4) == 0)
		{
			envp_path = tshell->environ[i];
			return (envp_path);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *path, char *cmd)
{
	char	**possible_path;
	char	*cmd_route;
	char	*aux;
	int		i;

	i = 0;
	if (!path || !cmd)
		return (NULL);
	aux = ft_strtrim(path, "PATH=");
	possible_path = ft_split(aux, ':');
	ft_free(aux);
	if (access(cmd, F_OK | X_OK) == 0)
	{	
		free_arr(possible_path);
		return (cmd);
	}
	while (possible_path[++i])
	{
		aux = ft_strjoin(possible_path[i], "/");
		cmd_route = ft_strjoin(aux, cmd);
		if (access(cmd_route, F_OK | X_OK) == 0)
			break ;
		else
		{
			ft_free2(aux, cmd_route);
			cmd_route = NULL;
			aux = NULL;
		}
	}
	free_arr(possible_path);
	if (aux)
		ft_free(aux);
	return (cmd_route);
}

int	ft_path(t_myshell *ms)
{
	char 	*path;
	t_com	*caux;

	if (ms->exit_status != EXIT_SUCCESS)
		return (ms->exit_status);
	path = get_path(ms);
	if (!path)
	{
		// ns si habra que haecr algo
		return (1);
	}
	caux = ms->t_com;
	while (caux)
	{
		caux->env_path = get_cmd_path(path, caux->args[0]);
		caux = caux->next;
	}
	return (0);
}
