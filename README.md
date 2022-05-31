# cub3d
***This project is a graphic design project, inspired by the famous game [Wolfenstein 3D](http://users.atw.hu/wolf3d/). We need to create a "realistic" 3D graphical representation of the inside of a maze from a first person perspective, using Ray-Casting principles.***

This project also enables us to improve skills in: windows, colors, events, fill shapes, etc.

## Technical considerations

- Allowed functions: ```open```, ```close```, ```read```, ```write```, ```malloc```, ```free```, ```perror```, ```strerror```, ```exit```, all functions of the ```math``` library and the ```MinilibX``` library
- All heap allocated memory space must be properly freed when necessary
- Management of window must remain smooth
- Allow for the display of different wall textures
- Allow for setting the floor and ceilling colors to two different colors
- Program must take a scene description file as a first argument

## How to test

> Run the following commands. Two map files (```xx.cub```) are provided in the ```maps``` directory. Replace ```map_or_map_bonus.cub```

```shell
$ git clone https://github.com/prranges/cub3d
$ make - for mandatory part
$ make bonus - for bonus part
$ ./cub3d maps/map_or_map_bonus.cub
```

- Press ```W / A / S / D``` key to move
- Press ```Space``` key to open or close the door. Also you can use a mouse to rotate.

## Screenshot

![cub3d](https://raw.githubusercontent.com/prranges/readme_files/main/cub3d_01.png "cub3d")
