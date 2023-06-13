// Estructura que almacena los eventos que ocurren en la app.
// Tamanio de la estructura = 20 bytes
struct S_Log {
  short id = 0;                                                                                                               // 2 bytes
  char descripcion[16] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };  // 16 bytes
  int siguiente = -1;                                                                                                         // 2 bytes
};

// Estructura que almacena la informacion de un usuario. 
// Tamanio de la estructura = 28 bytes
struct S_Usuario {
  char nombre[12] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };         // 12 bytes
  char contrasenia[12] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };    // 12 bytes
  int num_celular = 0;                                                                                  // 2 bytes
  int siguiente = -1;                                                                                   // 2 bytes
};

// Es una estructura auxiliar que ayuda a determinar en que posicion de la memoria EEPROM inicia la lectura de los datos del usuario y log.
// Ademas, ayuda a determinar en que posicion se puede almacenar un nuevo registro (ini_libre).
// Tamanio de la estructura = 6 bytes
struct S_Inicial {
  int ini_usuario = -1;   // Representa la posicion inicial de lectura de una estructura de tipo usuario; 2 bytes
  int ini_log = -1;  // Representa la posicion inicial de lectura de una estructura de tipo log; 2 bytes
  int ini_libre = -1;      // Representa la posicion inicial de guardado de un nuevo registro sin importar su tipo de estructura; 2 bytes
};

// Valor de los caracteres que posee el teclado
char valores_teclado[4][3] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
