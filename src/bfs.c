/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:28:33 by bwebb             #+#    #+#             */
/*   Updated: 2020/05/02 17:54:11 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemon.h"

void	cutedge(t_inputchecks *inchecks)
{
	int			count;
	int			cutedge;
	t_network	**links;

	count = -1;
	links = (*inchecks->start)->links;
	while(links[++count])
		if (links[count]->id == (*inchecks->end)->id)
			cutedge = count;
	if (count != cutedge)
		links[cutedge] = links[count];
	links[count] = NULL;
}

int		search(t_heart *heart, t_artery *artery)
{
	t_queue		*q;
	int			i;

	q = NULL;
	pushq(&q, NULL, heart->network);
	while (1)//this is ew but idk what do do about it
	{
		i = -1;
		while (q->node->links[++i])
			if (!(q->node->links[i]->visited))
				pushq(&q, q, q->node->links[i]);
		q->node->visited = 1;
		if ((q->next == NULL) || (q->node->end))
			break ;
		q = q->next;
	}
	i = (q->node->end) ? 1 : 0;
	while ((i && addveinnode(&(artery->vein), q->node)) || (!q->node->start))
		q = q->parent;//unescessary memory saving
	freeq(q);
	if (i && artery->vein->next->node->end)
		cutedge(heart->inputchecks);
	return (i);
}

int		bfs(t_heart *heart)
{
	int	i;
	t_artery	*artery;

	i = 0;
	while (search(heart, artery = addarterynode(&heart->artery, ++i)))
		artery->ants = veinlen(artery->vein);
	popart(heart->artery);
	return(heart->artery ? 1 : 0);
}