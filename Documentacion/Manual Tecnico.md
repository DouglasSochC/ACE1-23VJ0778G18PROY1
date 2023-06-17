
# Manual Tecnico  -  Proyecto I Arduino VJ2023
Sé desarrollo de un prototipo para un sistema de cargado de celulares. En este sistema, los usuarios registrados podrán obtener acceso
temporal a un espacio para la carga de su dispositivo. Se le
brindará a los administradores herramientas para controlar
de forma efectiva el sistema y obtener datos relevantes. Es
preciso, también, considerar aspectos como la seguridad en
un sistema como este; por lo que se deberán implementar
características que la permitan.


## Authors

- 201902502 - Carlos Eduardo Soto Marroquín
- 201709282 - Carlos Javier Martinez Polanco
- 201807032 - Douglas Alexander Soch Catalán
- 201945242 - Jefferson Gamaliel Molina Barrios
- 201807389 - Gladys Leticia Ajuchán Vicente


## Requisitos del Sistema.

###### Procesador:
- Intel Superior a la 4ta gen
- AMD Superior a las versiones de Opteron
###### Memoria RAM:
- Superior a las 2GB de RAM, en versiones superiores a DDR3
###### Espacio de Disco:
- Tener libre 30MB
###### Sistema Operativo:
- MacOS, Windows, Distribuciones de Linux (Compatibles con Proteus 8.12).
###### Herramientas de desarrollo de Software:
- Arduino IDE y Proteus 8.12
###### Resolución Gráfica:
No es necesario una tarjeta gráfica o un chip de video


## Librerias Usadas

- <Keypad.h>
- <EEPROM.h>
- <LiquidCrystal.h>
- <LedControl.h>

## Implementacion del codigo

#### Estructuras Auxiliares
- Estructura que almacena los eventos que ocurren en la app.

```ruby
// Tamanio de la estructura = 21 bytes
struct S_Log {
  short id = 0;                                                                                                                     // 2 bytes
  char descripcion[17] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };  // 17 bytes
  int siguiente = -1;                                                                                                               // 2 bytes
};
```

#### Estructura que almacena la informacion de un usuario.

```ruby

// 
// Tamanio de la estructura = 39 bytes
struct S_Usuario {
  char nombre[13] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };       // 13 bytes
  char contrasenia[13] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };  // 13 bytes
  char num_celular[9] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };                           // 9 bytes
  char admin[2] = { '\0', '\0' };                                                                           // 2 bytes
  int siguiente = -1;                                                                                       // 2 bytes
};

```

#### Representa que usuarios estan utilizando los 9 compartimientos
- Se creo una matriz para los 9 comportamientos de los usuarios
```ruby
struct S_Compartimientos {
  char compartimentos[9][13] = {
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
    { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' }
  };
};
```

#### Valor de los caracteres que posee el teclado
- Se creo una matriz para definnir los valores del teclado

```ruby
char valores_teclado[4][3] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
```

#### Matriz con el ABECEDARIO
- Se creo una matriz para cada letra de la palabra "ABECEDARIO"
```ruby
bool abecedario[31][8][8] = {
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 1, 0, 0, 0 },
    { 0, 1, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 1, 0, 0, 1, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 1, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 1, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 0, 1, 1, 0 },
    { 0, 1, 0, 1, 0, 1, 1, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 0, 1, 0, 1, 0, 0 },
    { 0, 0, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 0, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 1, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 1, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 1, 0, 1, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 1, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 1, 0, 0, 0 } },
  { { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 1, 0 },
    { 0, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 } },
  { { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 } },
  { { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 1, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 1, 1, 0, 0, 0 } }

};
```

#### inicilizacion del LCD
-Se creo una funcion para inicilizar la pantalla
```ruby
lcd.begin();
lcd.clear(); //limpiamos la pantalla
lcd.setCursor(0, 0); //Colocamos el cursor en la columna 0 fila 0
lcd.print("GRP 18 N ACE1"); //imprimir texto
lcd.setCursor(0, 1); //Colocamos el cursor en la columna 0 fila 1
lcd.print("PROYECTO 1"); //imprimir texto
delay(5000);
lcd.clear();
Serial.begin(9600);
pinMode(LuzIzquierda, INPUT);
pinMode(LuzDerecha, INPUT);

```

####  Estados del programa
```ruby
#define SECUENCIA_INICIAL 0
#define MENU_PRINCIPAL 1
#define INICIO_SESION 2
#define REGISTRO_USUARIO 3
#define MENU_USUARIO 4
#define MENU_ADMINISTRADOR 5
#define INGRESO_CELULAR 6
#define RETIRO_CELULAR 7
#define ELIMINACION_CUENTA 8
#define INGRESO_CELULAR_ENTRADA 9
#define RETIRO_CELULAR_ENTRADA 10
#define LOGS 11
#define ESTADO_SISTEMA 12
#define ESTADO_SISTEMA_ENVIO 13
```

#### Reconociendo sensores
- los siguientes son los piertos para reconocer los sensores
``` ruby
Serial3.print("S1");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[0] = atoi(res_analogica);
  Serial3.print("S2");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[1] = atoi(res_analogica);
  Serial3.print("S3");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[2] = atoi(res_analogica);
  Serial3.print("S4");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[3] = atoi(res_analogica);
  Serial3.print("S5");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[4] = atoi(res_analogica);
  Serial3.print("S6");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[5] = atoi(res_analogica);
  Serial3.print("S7");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[6] = atoi(res_analogica);
  Serial3.print("S8");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[7] = atoi(res_analogica);
  Serial3.print("S9");
  Serial3.readBytes(res_analogica, 2);
  temp_calor[8] = atoi(res_analogica);
```

#### Imprime el mensaje inicial en la pantalla LCD
- Se crea una funcion para mostrar el mensaje inicial


```ruby
void imprimirMensajeInicial(int posicion) {
  lcd.clear();                    // Se limpia el LCD
  lcd.setCursor(0, posicion);     // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
  lcd.print("201709282|Javier");  // Se imprime un texto

  lcd.setCursor(0, posicion + 1);  // Se agrega al cursor para empezar a escribir en columna = 0, fila = 1
  lcd.print("201807032|Douglas");  // Se imprime un texto
  lcd.setCursor(0, posicion + 2);  // Se agrega al cursor para empezar a escribir en columna = 0, fila = 2
  lcd.print("201807389|Gladys");   // Se imprime un texto

  lcd.setCursor(0, posicion + 3);  // Se agrega al cursor para empezar a escribir en columna = 0, fila = 3
  lcd.print("201902502|Eduardo");  // Se imprime un texto

  if (posicion == -1) {
    lcd.setCursor(0, posicion + 4);    // Se agrega al cursor para empezar a escribir en columna = 0, fila = 4
    lcd.print("201945242|Jefferson");  // Se imprime un texto
  }
}
```

#### Se modifica la app 
- Reinicia las variables auxiliares cada vez que se modifica el estado del app
```ruby
void reiniciarVariableAuxiliares() {
  imprimir_mensaje = true;
  temp_texto = "";
}
```

#### Encendido de las luces luc.

- Implementacion de una funcion para Verificar Luz de la Derecha
```ruby
int EncenderIzquierda() {
  int tI = 0;
  int dI = 0;
  digitalWrite(TriggerIzquierda, HIGH); //FUNCIONAMIENTO DEL SENSOR ULTRASONICO
  delay(1000); //pausa para integrar respuesta
  digitalWrite(TriggerIzquierda, LOW);
  tI = pulseIn(EchoIzquierda, HIGH); // pausa para integrar respuesta
  dI = round(tI / 59); //Distancia - tiempo
  return dI;
  
}
```
- Implementacion de una funcion para la led de de la Derecha
```ruby
int EncenderDerecha() {
  int tD = 0;
  int dD = 0;
  digitalWrite(TriggerDerecha, HIGH); //FUNCIONAMIENTO DEL SENSOR ULTRASONICO
  delay(1000); //pausa para integrar respuesta
  digitalWrite(TriggerDerecha, LOW);
  tD = pulseIn(EchoDerecha, HIGH); // pausa para integrar respuesta
  dD = round(tD / 59); //Distancia - tiempo
  return dD;
}
```
- Implementacion de una funcion para Verificar Luz de la iziquierda
```ruby
int VerificarLuzIzquierda(){
  int valorI = 0;
  valorI = digitalRead(LuzIzquierda);  
  delay(1000);
  return valorI;
}
```

- Implementacion de una funcion para Verificar Luz de la Derecha
``` ruby
int VerificarLuzDerecha(){
  int valorD = 0;
  valorD = digitalRead(LuzDerecha);  
  delay(1000);
  return valorD;
}
```

