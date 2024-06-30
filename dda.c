#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


#define	width 50
#define	height 20
void	init_table();
char	table[height][width];

void	print_table()
{
	int	x = 0;
	int	y = 0;
	system("clear");
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("%c", table[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	init_table();
}

void	init_table()
{
	int	x = 0;
	int	y = 0;

	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			table[y][x] = '*';
			x++;
		}
		table[y][x] = '\0';
		y++;
	}
}

void	dda(int sx, int sy, int ex, int ey)
{
	int		dx;
	int		dy;
	int		step;
	double	xinc;
	double	yinc;

	dx = ex - sx;
	dy = ey - sy;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	xinc = (double) dx / step;
	yinc = (double) dy / step;
	double	x = sx, y = sy;
	for (int i = 0; i < step; i++)
	{
		table[(int)round(y)][(int)round(x)] = ' ';
		x += xinc;
		y += yinc;
	}
}

# define SPEED 100000

int main()
{
	init_table();
	int i = 0;
	while (1)
	{
		dda(0, 0, width, height);
		print_table();
		usleep(SPEED);
		dda((width) / 2, 0, (width) / 2, height);
		print_table();
		usleep(SPEED);
		dda(0, height / 2, width, height / 2);
		print_table();
		usleep(SPEED);
		dda(width, 0, 0, height);
		print_table();
		usleep(SPEED);
	}
}
