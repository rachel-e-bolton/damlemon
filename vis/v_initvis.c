#include "../includes/visualiser.h"

void		init_vis(t_vis *vis)
{

	vis->window = NULL;
	vis->rend = NULL;
	vis->bg = NULL;
	vis->room = NULL;
	vis->ant  = malloc(11 * sizeof(SDL_Texture *));
	vis->mirror = malloc(11 * sizeof(SDL_Texture *));
	vis->close = 0;
	vis->active = 0;
	vis->percent = 0;

}

void	init_window(t_vis *vis)
{
	
	if (!(vis->window = SDL_CreateWindow("Lem-in Visualizer",
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT, 0)))
		vis_error_free(vis, SDL_GetError());
}

void	init_renderer(t_vis *vis)
{

	int				flags;

	flags = SDL_RENDERER_ACCELERATED;
	if (!(vis->rend = SDL_CreateRenderer(vis->window, -1, flags)))
		vis_error_free(vis, SDL_GetError());
}

void	init_loop(t_vis *visualiser, t_heart *heart)
{
	t_input		*movelist;
	t_ant		*ants;

	movelist = heart->input;
	while(movelist->line[0] != 'L'){
		movelist = movelist->next;
	}
	ants = v_initants(heart->ants);
	ants = setstart(ants, heart->input);
	vis_loop(visualiser, heart, ants, movelist);
	free_ants(ants);

}

void	vis_loop(t_vis *visualiser, t_heart *heart, t_ant *ants, t_input *movelist)
{
	t_ant	*tmp;
	t_input *tmpmove;
	int		check;

	tmp = ants;
	tmpmove = movelist;
	while(!(visualiser->close))
	{
		SDL_RenderClear(visualiser->rend);
		drawall(visualiser, heart, ants);
		SDL_RenderPresent(visualiser->rend);
		SDL_Delay(1000 / 60);
		if(visualiser->active && visualiser->percent < 1)
			visualiser->percent += 0.01;
		else if (visualiser->active)
		{
			visualiser->percent = 0.01;
			visualiser->active = 0;
		}
		check = eventcheck(visualiser, heart, tmp, tmpmove);
		if (check == 1)
		{
			if (tmpmove)
				tmpmove = tmpmove->next;
		}
		else if (check == 2)
		{
			setstart(ants, heart->input);
			tmpmove = movelist;
		}
	}
}