/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:22 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/13 18:30:20 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
   // double texture_pos = (top_y - window_height / 2 + line_height / 2) * step;  // Start position for texture mapping

    // for (y = (int)top_y; y < (int)bottom_y; y++) {
    //     // Calculate the corresponding Y coordinate in the texture
    //     tex_y = (int)texture_pos & (data->image[0].height - 1);  // Use modulo for wrapping within texture height
    //     texture_pos += step;

    //     // Get the pixel color from the texture at (texture_x, tex_y)
    //     color = get_texture_pixel_color(data, texture_x, tex_y);

    //     // Draw the pixel on the screen at the calculated position
    //     mlx_pixel_put(data->mlx, data->win_test, column, y, color);
    // }