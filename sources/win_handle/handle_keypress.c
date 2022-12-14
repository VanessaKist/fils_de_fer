/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkist-si <vkist-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:06:30 by vkist-si          #+#    #+#             */
/*   Updated: 2022/09/17 21:06:34 by vkist-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf_header.h"

static int	handle_arrows(int keymask, t_key *key)
{
	if (keymask == XK_Left)
	{
		key->travelx -= 30;
		key->press = 1;
	}
	else if (keymask == XK_Right)
	{
		key->travelx += 30;
		key->press = 1;
	}
	else if (keymask == XK_Up)
	{
		key->travely -= 30;
		key->press = 1;
	}
	else if (keymask == XK_Down)
	{
		key->travely += 30;
		key->press = 1;
	}
	return (0);
}

int	handle_keypress(int keymask, t_data *data)
{
	if (keymask == XK_Escape)
	{
		free_data(data);
		exit (0);
	}
	else
		handle_arrows(keymask, &data->key);
	return (0);
}
