/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:03:34 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/22 02:07:13 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int get_image_texture(t_data *data, t_texture *tex)
{
    while (tex)
    {
        if (tex->identifier == 0)
            data->image[0].image = mlx_xpm_file_to_image(data->mlx, tex->Path, 
                                &data->image[0].whith, &data->image[0].height);
        if (tex->identifier == 1)
            data->image[1].image = mlx_xpm_file_to_image(data->mlx, tex->Path, 
                                &data->image[1].whith, &data->image[1].height);
        if (tex->identifier == 2)
            data->image[2].image = mlx_xpm_file_to_image(data->mlx, tex->Path, 
                        &data->image[2].whith, &data->image[2].height);
        if (tex->identifier == 3)
            data->image[3].image = mlx_xpm_file_to_image(data->mlx, tex->Path, &data->image[3].whith, &data->image[3].height);
        tex = tex->next;
    }
    if (data->image[0].image == NULL || data->image[1].image == NULL || data->image[2].image == NULL || data->image[3].image == NULL)
    {
            return (1);
    }
    return (0); 
}

int get_addr_texture(t_data *data)
{
    int i = 0;
    while (i < 4)
    {
        data->image[i].addr = mlx_get_data_addr(data->image[i].image, 
                                    &data->image[i].bits_per_pixel,
                                     &data->image[i].line_length,
                                      &data->image[i].endian);
        i++;
    }
    return (0);
}

void clear_texture(t_texture *tex)
{
    t_texture *tmp;
    while (tex)
    {
        tmp = tex;
        tex = tex->next;
        free(tmp->Path);
        free(tmp->rgp_color);
        free(tmp);
    }
}