/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwebb <bwebb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:26:04 by bwebb             #+#    #+#             */
/*   Updated: 2020/01/14 16:16:30 by bwebb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemon.h"

char	*test(char *str)
{
	str = "test";
	return (str);
}

int	main(void)
{
	char	*buff;
	t_input	*inputHead;

	char *mainstrinit = "main";
	char *newmain = test(mainstrinit);
	while (get_next_line(0, &buff)) {
		addInputNode(&inputHead, buff);
		 }
	// while (input) {
	// 	printf("%s\n", input->line);
	// 	input = input->next;
	// }
	// if (!validateInput(input))
	// 	erexit("Bad map file");
	return (0);
}