// Estructura que almacena los eventos que ocurren en la app.
// Tamanio de la estructura = 21 bytes
struct S_Log {
  short id = 0;                                                                                                                     // 2 bytes
  char descripcion[17] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };  // 17 bytes
  int siguiente = -1;                                                                                                               // 2 bytes
};

// Estructura que almacena la informacion de un usuario.
// Tamanio de la estructura = 39 bytes
struct S_Usuario {
  char nombre[13] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };       // 13 bytes
  char contrasenia[13] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };  // 13 bytes
  char num_celular[9] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };                           // 9 bytes
  char admin[2] = { '\0', '\0' };                                                                           // 2 bytes
  int siguiente = -1;                                                                                       // 2 bytes
};

// Es una estructura auxiliar que ayuda a determinar en que posicion de la memoria EEPROM inicia la lectura de los datos del usuario y log.
// Ademas, ayuda a determinar en que posicion se puede almacenar un nuevo registro (ini_libre).
// Tamanio de la estructura = 6 bytes
struct S_Inicial {
  int ini_usuario = -1;  // Representa la posicion inicial de lectura de una estructura de tipo usuario; 2 bytes
  int ini_log = -1;      // Representa la posicion inicial de lectura de una estructura de tipo log; 2 bytes
  int ini_libre = -1;    // Representa la posicion inicial de guardado de un nuevo registro sin importar su tipo de estructura; 2 bytes
};

// Valor de los caracteres que posee el teclado
char valores_teclado[4][3] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

// Abecedario
bool abecedario[26][8][8] = {
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
};