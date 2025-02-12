/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:34:24 by ecortes-          #+#    #+#             */
/*   Updated: 2025/02/02 12:16:10 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	count_quotes(const char *prompt)
{
	char	quote_char;
	int		quotes;
	int		i;

	quote_char = '\0';
	quotes = 0;
	i = 0;
	while (prompt[i] != '\0')
	{
		if ((prompt[i] == '\'' || prompt[i] == '"') && quote_char == '\0')
		{
			quote_char = prompt[i];
			quotes++;
		}
		else if ((prompt[i] == '\'' || prompt[i] == '"') &&
				quote_char == prompt[i])
		{
			quote_char = '\0';
			quotes++;
		}
		i++;
	}
	//printf("este es el number of quotes: %i\n", quotes);
	if (quotes % 2 != 0 || quotes == 1)
		return (1);
	return (0);
}

char	*get_path(t_myshell *tshell)
{
	int		i;
	char	*envp_path;

	i = 0;
	envp_path = NULL;
	while (tshell->environ[i])
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
	char	*aux_route;
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strtrim(path, "PATH=");
	possible_path = ft_split(aux, ':');
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (possible_path[++i])
	{
		aux_route = ft_strjoin(possible_path[i], "/");
		cmd_route = ft_strjoin(aux_route, cmd);
		if (access(cmd_route, F_OK) != -1 && access(cmd_route, X_OK) != -1)
			break ;
		else
		{
			ft_free2(aux_route, cmd_route);
			cmd_route = NULL;
		}
	}
	free (aux);
	return (cmd_route);
}

int	how_many_finds(char *str, int c)
{
	char	*aux;
	int		count;

	count = 0;
	aux = str;
	while (1)
	{
		aux = ft_strchr(aux, c);
		if (!aux)
			return (count);
		aux++;
		count++;
	}
	return (count);
}
