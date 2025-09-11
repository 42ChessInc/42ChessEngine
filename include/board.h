/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:29:39 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/11 21:11:39 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
#define BOARD_H

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>

typedef uint64_t	Bitboard; // 64 squares for board representation

typedef struct s_board
{
	Bitboard	pieces[2][6]; //Squares occupied by each piece (6) for each color (2)

	Bitboard	ocuppied; //All ocuppied squares (both black and white)
	Bitboard	ocuppiedColor[2]; //Ocuppied squares by color
}	t_board;

typedef struct s_state
{
	int				*board;
	int				size;
	struct s_state	*next;
}	t_state;

#endif
