# miniRT

miniRT is a simple and small ray tracer created for my studies at the 42 school codam in Amsterdam.

## Usage
Just clone the repository and type **make** :D You will find a executable called miniRT. To showcase rendered images just run the program with one of my existing scenes.


```bash
make
./miniRT scenes/cube.rt
```
You can also add a --save option to save the output as a .bmp file.
```bash
./miniRT scenes/cube.rt --save
```

If a scene has more than one you can swap the camera in your rendered image with the right arrow key.

## Scene Files
My miniRT takes a scene file as a first argument with the.rt extension. The scene file contains all the information my mini ray tracer needs to render a full image. Each element first’s information is the type identifier, followed by all specific information for each object in a strict order.

* Resolution R
* Ambient lightning A
* Camera c
* Light l
* Sphere sp
* Plane pl
* Square sq
* Cylinder cyl
* Triangle tr

Mandatory elements are:
Resolution,
Ambient Light
and atleast one Camera.

You find a detailed explanation of the scene file [here :)](https://docdro.id/QySFfXH)

![Example Scene](https://i.imgur.com/11Gxte8.png)

## Examples
```bash
./miniRT scenes/7-wolfie.rt 
```
![Wolfie Scene](https://i.imgur.com/enOBJuT.png)
```bash
./minirt scenes/cube.rt
```
![Cube Scene](https://i.imgur.com/zVuZYG6.png)

