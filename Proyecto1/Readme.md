# Proyecto 1 de Creación de Videojuegos 2025-I

## Descripcion

El presente proyecto es un videojuego del genero side-scroller shooter, es decir, consiste en moverse en una sola dirección por un nivel mientras se dispara hacia enemigos. El juego está basado mayoritariamente en Gradius, un juego de arcade publicado por Konami en 1985, pero para inspiración se usó principalmente la version de NES salida en 1986, el titulo del juego es Battle of Andronika

## Juego

### Menu Principal

El juego empieza en un menú principal en el que solo se permite elegir de una serie de botones usando el mouse, para avanzar simplemente se debe hacer click sobre el botón deseado, llevando a un nivel diferente dependiendo del botón presionado, existen 3 niveles diferentes, cada uno con una versión para uno o 2 jugadores

### Niveles

Al entrar a un nivel, se podrá mover una nave utilizando el teclado, en el caso del jugador 1 se moverá utilizando WASD y se dispará con J, mientras que el jugador 2 debe utilizar las flechas para movimiento y el numero 0 del NUMPAD para atacar.

### Enemigos

Los enemigos aparecen en grupos (algunos grupos de 1), existen 4 tipos generales de enemigos:

- **Mini-Alan:** Enemigo básico que se mueve de derecha a izquierda sin atacar directamente al jugador

- **Misil:** Enemigo que busca al jugador más cercano e intenta chocar con él, puede cambiar dirección como sea necesario para perseguir al jugador

- **Cruiser:** Se mueve de derecha a izquierda al igual que Alan, pero intenta disparar al jugador (aun si tiene muy mala punteria), es el enemigos normal con más vida

- **Jefe:** Aparecen al final del nivel al alcanzarse cierta cantidad de puntos, detienen la aparición de los otros enemigos, son muy duraderos y buscan perseguir al jugador, pero no son tan lentos. Tras su muerte, el nivel termina.


## Compilación

Para compilar el juego se recomienda utilizar el makefile recomendado, es importante señalar que es necesario tener instaladas las bibliotecas SDL2, GLM y Sol para que la compilación funcione correctamente. Teniendo estas bibliotecas instaladas se puede compilar usando el comando

    make

Esto genera un ejecutable llamado game_engine.out, si desea correrlo puede hacerlo a mano o utilizar el siguiente comando:

    make run

En caso de querer ver la documentación doxygen se usa el comando:

    doxygen Doxyfile

Tras esto, se generará una carpeta llamada Doc, dentro de la cual se encontrará otra llamada html, donde se encuentra una versión html de la documentación.

## Diseño

El diseño del programa se encuentra en la carpeta diseño como una imagen png que contiene el diagrama UML del juego. Se incluye en este readme, pero debido a su tamaño se recomienda revisar la imagen completa para mejor legibilidad.

   ![Diagrama UML](/design/UML.png)


## Creditos

El código fue escrito principalmente en base a los videos del profesor Alberto Rojas, con comentarios Doxygen generados con ayuda de la IA Claude, con revisión posterior de mi parte.

Los sprites fueron tomados de itch.io, pero todos fueron editados hasta cierto punto utilizando la herramienta Piskel para acoplarse de mejor manera a lo buscado en el proyecto (ej. Glup fue descargado de itch.io pero sus frames de golpe y muerte fueron hechas mediante Piskel)

Este proyecto fue creado por André Salas Chinchill (correo andre.salaschinchilla@ucr.ac.cr) como parte del curso de desarrollo de videojuegos