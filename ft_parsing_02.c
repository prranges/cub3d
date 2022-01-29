/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:34:28 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/28 18:49:15 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_size_map(char **argv) // определение размера карты
{
    int     size;
    int     end_file;
    int     fd;
    char    *str;

    size = 0;
    str = NULL;
    end_file = 1;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        perror("Error");
    while (end_file)
    {
        end_file = get_next_line(fd, &str);
        free(str);
        size++;
    }
    close(fd);
    return(size);
}

void ft_load_map(char **argv, char ***map) // загрузка параметров карты
{
    int     fd;
    int     end_file;
    int     i;
    int     size;
    char    *str;
    char    **temp = NULL;
            
    i = 0;
    end_file = 1;
    size = ft_size_map(argv);
    temp = (char **)malloc(sizeof(char *) * (size + 1));
    fd = open(argv[1], O_RDONLY); 
    
    while (end_file)
    {
        end_file = get_next_line(fd, &str);
        temp[i] = str;
        i++;
    }
    temp[i] = NULL;
    i = 0;
    *map = temp;
    close(fd);
}

void    ft_save_param(char *line_split, char **path_texture, t_data *g)  // запись текстур
{
    if (!*path_texture)
    {
        *path_texture = line_split;
        g->map.param_count++;
    }
    else
    {
        printf("Error: Params dublicate!");
        exit (0);
    }
}


int rgb_to_int(int r, int g, int b) // перевод rgb в int
{
  int c = r;
  c = (c << 8) | g;
  c = (c << 8) | b;
  return c;
}

int	ft_strisnum(const char *str) // проверка на число
{
	int	i;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
int    ft_check_rgb(char **split_color)
{
    int i;
    int rgb[3];
    i = 0;
    while (i < 3)
    {
        if(ft_strisnum(split_color[i]) && ft_atoi(split_color[i]) <= 255)
        {
            rgb[i] = ft_atoi(split_color[i]);   
            printf("This is num: %d\n", rgb[i]);
        }
        else
        {
            printf("Error: This is not num or num > 255\n");
            exit (1);
        }          
        i++;
    }
    return (rgb_to_int(rgb[0], rgb[1], rgb[2]));
}

void    ft_save_color(char **line_split, char **color, t_data *g) //запись цвета для пола и потолка
{
    // t_color rgb;
    char    **split_color;

    // if (!*color)
    // {
    //     *color = line_split;
    //     g->map.param_count++;
    // }
    // else
    // {
    //     printf("Error: Params dublicate!!!");
    //     exit (0);        
    // }
    if (*color)
    {
        printf("Error: Params dublicate!!!");
        exit (0);        
    }
    *color = line_split[1];
    g->map.param_count++;
    split_color = ft_split(*color, ',');

    if (!ft_strncmp(line_split[0], "C", 1))
        g->map.celing_color =ft_check_rgb(split_color);
    if (!ft_strncmp(line_split[0], "F", 1))
        g->map.floor_color =ft_check_rgb(split_color);
}

void ft_map_lines_check(char **lines, int i, t_data *g)
{
    int j;
    int position_flag;
    
    j = 0;
    position_flag = 0;
    while (lines[i])
    {
        j = 0;
        while (lines[i][j])
        {
            if (lines[i][j] != '1' && lines[i][j] != '0' && lines[i][j] != 'N' && lines[i][j] != 'S' && lines[i][j] != 'W' && lines[i][j] != 'E' && lines[i][j] != ' ')
            {
                printf("Error: Map use invalid symbol! %c", lines[i][j]);
                exit (1);
            }
            if ((lines[i][j] == 'N' || lines[i][j] == 'S' || lines[i][j] == 'W' || lines[i][j] == 'E') && position_flag < 1)
            {
                position_flag++;
                g->map.plaer_orient = lines[i][j];
            }
            else if ((lines[i][j] == 'N' || lines[i][j] == 'S' || lines[i][j] == 'W' || lines[i][j] == 'E') && position_flag == 1)
            {
                printf("Error: Double position! %c\n", lines[i][j]);
                exit (1);
            }
            j++;
        }
        if ((int)ft_strlen(lines[i]) > g->map.map_size_l)
            g->map.map_size_l = (int)ft_strlen(lines[i]);
        if (ft_strcmp (lines[i], ""))
            g->map.map_size_h++;
        else
        {    
            printf("Error: Map is invalid new lines!\n");
            exit (1);
        }
        i++;

    }    
}

void	ft_bchar(void *dest, size_t len, char c) // заполнение строки символами
{
	char	*tmp;
	size_t	i;

	tmp = dest;
	i = 0;
	while (i < len)
		*(tmp + i++) = c;
}

void    ft_check_border_map_l(char **map, t_data *g)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < g->map.map_size_h)
    {
        j = -1;
        while(map[i][++j] == ' ')
            ;
        if (map[i][j] != '1')
        {
            printf("Error1 '%c' %d %d", map[i][j], i, j);
            exit (1); 
        }
        j = g->map.map_size_l;
        while(map[i][--j] == ' ')
            ;
        if (map[i][j] != '1')
        {
            printf("Error2 '%c' %d %d", map[i][j], i, j);
            exit (1);
        }       
        i++;
    }
}

void    ft_check_border_map_h(char **map, t_data *g)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < g->map.map_size_l)
    {
        j = -1;
        while(map[++j][i] == ' ')
            ;
        if (map[j][i] != '1')
        {
            printf("Error3 '%c' %d %d", map[j][i], j, i);
            exit (1); 
        }
        j = g->map.map_size_h;
        while(map[--j][i] == ' ')
            ;
        if (map[j][i] != '1')
        {
            printf("Error4 '%c' %d %d", map[j][i], j, i);
            exit (1);
        }       
        i++;
    }
}

void    ft_check_map_inside_l(char **map, t_data *g) // горизонтальна проверка внутренностей карты
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < g->map.map_size_h)
    {        
       
        while ((map[i][j] != '0' &&  map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E') && j < g->map.map_size_l - 1)
            j++;
        if (j == g->map.map_size_l - 1)
        {
            i++;
            j = 0;
            continue;
        }
        while ((map[i][j] == '0' ||  map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E') && j < g->map.map_size_l - 1)
            j++;
        if (map[i][j] == '1' && j < g->map.map_size_l - 1)
        {
            j++;
            continue;            
        }
        else if (map[i][j] != '1')
        {
            printf("Error5 '%c' %d %d", map[i][j], i, j);
            exit (1);
        }
        j = 0;
        i++;
    }
}

void    ft_check_map_inside_h(char **map, t_data *g) // вертикальная проверка внутренностей карты
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < g->map.map_size_l)
    {        
       
        while ((map[j][i] != '0' &&  map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'W' && map[j][i] != 'E') && j < g->map.map_size_h-1)
            j++;
        if (j == g->map.map_size_h - 1)
        {
            i++;
            j = 0;
            continue;
        }
        while ((map[j][i] == '0' ||  map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E') && j < g->map.map_size_h-1)
            j++;
        if (map[j][i] == '1' && j < g->map.map_size_h - 1)
        {
            j++;
            continue;            
        }
        else if (map[j][i] != '1')
        {
            printf("Error6 '%c' %d %d", map[j][i], j, i);
            exit (1);
        }
        j = 0;
        i++;
    }
}

void    ft_map_record(char **lines, int i, t_data *g)
{
//    char    **map;
    int     j;
    int     k;

    (void)i;    
    (void)lines;
    j = 0;
    k = 0;
    g->map.map_pars = malloc(sizeof(char*) * g->map.map_size_h);
    while (j < g->map.map_size_h)
    {
        g->map.map_pars[j] = malloc(sizeof(char) * g->map.map_size_l);
        ft_bchar(g->map.map_pars[j], g->map.map_size_l, ' ');
        j++;
    }
    j =0;
    while(j < g->map.map_size_h)
    {
        k = 0;
        while(lines[i][k])
        {
            g->map.map_pars[j][k] = lines[i][k];
            printf("%c", g->map.map_pars[j][k]);
            k++;
        }
        printf("\n");
        j++;
        i++;
    }
    ft_check_border_map_l(g->map.map_pars, g);
    ft_check_border_map_h(g->map.map_pars, g);
    ft_check_map_inside_l(g->map.map_pars, g);
    ft_check_map_inside_h(g->map.map_pars, g);
}

void    ft_check_param(t_data *g, char ***map) // проверим параметры карты на валидность
{
    char    **lines;
    char    **line_split;
    int     i;
    int     j;
        
    i = 0;
    j = 0;
    lines = *map;         
    while (lines[i])
    {
        line_split = ft_split(lines[i], ' ');
        if (!line_split[0])
        {
            i++;
            continue;
        }
        if (!ft_strncmp(line_split[0], "NO", ft_strlen(line_split[0])))
        {
            ft_save_param(line_split[1], &g->map.path_north_texture, g);
            printf("%s %s\n", line_split[0], line_split[1]);
        }
        else if (!ft_strncmp(line_split[0], "SO", ft_strlen(line_split[0])))
        {
            ft_save_param(line_split[1], &g->map.path_south_texture, g);
            printf("%s %s\n", line_split[0], line_split[1]);
        }
           
        else if (!ft_strncmp(line_split[0], "WE", ft_strlen(line_split[0])))
        {
            ft_save_param(line_split[1], &g->map.path_west_texture, g);
            printf("%s %s\n", line_split[0], line_split[1]);
        }
        else if (!ft_strncmp(line_split[0], "EA", ft_strlen(line_split[0])))
        {
            ft_save_param(line_split[1], &g->map.path_east_texture, g);
            printf("%s %s\n", line_split[0], line_split[1]);
        }    
        else if (!ft_strncmp(line_split[0], "C", ft_strlen(line_split[0])))
        {
            ft_save_color(line_split, &g->map.celing, g);
            printf("%s %s\n", line_split[0], line_split[1]);
            printf("Int RGB C: %d\n", g->map.celing_color);
        }    
        else if (!ft_strncmp(line_split[0], "F", ft_strlen(line_split[0])))
        {
             ft_save_color(line_split, &g->map.floor, g);
             printf("%s %s\n", line_split[0], line_split[1]);
             printf("Int RGB F: %d\n", g->map.floor_color);
        }
        else if (lines[i][0] == '\n')
        {    
            i++;
            continue;
        }
        
        else
        { 
            ft_param_validation(g);
            break ;            
        }
        i++;
    }
       
    ft_map_lines_check(lines, i, g);
    printf("Height map: %d, Width map: %d\n", g->map.map_size_h, g->map.map_size_l);
    ft_map_record(lines, i, g);
    
   
    

}

void    ft_param_validation(t_data *g) // проерим валидность параметров
{
    if (g->map.param_count != 6)
    {
        printf("Error: Malo parametrov");
        exit (1);
    }


}

void    ft_pars_params(char **argv, t_data *g) // парсинг параметров
{
    int i;
    char    **map;
    
    i = 0;
    map = NULL;
    ft_load_map(argv, &map);
    printf("\n \n ALL MAPA\n");
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
    ft_check_param(g, &map);  
}
