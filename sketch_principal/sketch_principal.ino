#include <Keypad.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <LedControl.h>
#include "Estructuras_Auxiliares.h"

// Pines
LedControl matriz_driver = LedControl(51, 53, 52, 1);  // Matriz con driver
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);                   // Pantalla LCD
byte Fpines[4] = { 22, 23, 24, 25 };                                         // Pines para manejar las filas del teclado
byte Cpines[4] = { 26, 27, 28 };                                             // Pines para manejar las columnas del teclado
Keypad teclado = Keypad(makeKeymap(valores_teclado), Fpines, Cpines, 4, 3);  // Mapeo de los valores que se obtienen a traves del teclado
#define PIN_ACEPTAR 8                                                        // Pin para manejar la aceptacion de alguna accion
#define PIN_CANCELAR 13                                                      // Pin para manejar la cancelacion de alguna accion
#define PIN_DERECHA 31                                                       // Pin para manejar el movimiento hacia la derecha
#define PIN_IZQUIERDA 32                                                     // Pin para manejar el movimiento hacia la izquierda

// Estados del programa
#define MENU 0
#define INICIO_SESION 1
#define REGISTRO 2
#define USER 3
#define ADMIN 4
#define ADDPRODUCTS 5
#define BUYPRODUCTS 6
#define CHANGEPRODUCTS 7
#define M0 8
#define M1 9
#define M2 10
#define M3 11
#define VIEWSMACHINE 12
int estado_app = MENU;  // Indica el estado actual en el que esta el programa

// Util
#define CLAVE_1 1  // Representa el valor que sera utilizado para aplicar un XOR en la primera pasada
#define CLAVE_2 4  // Representa el valor que sera utilizado para aplicar un XOR en la segunda pasada

void setup() {
  
  Serial.begin(9600);   // Inicializa la comunicacion con el virtual terminal
  Serial3.begin(9600);  // Inicializa la comunicacion con el segundo arduino
  lcd.begin(16, 2);     // Inicializa el LCD

  // Inicializando la matriz con driver
  matriz_driver.shutdown(0, false);
  matriz_driver.setIntensity(0, 8);
  matriz_driver.clearDisplay(0);

  // Mensaje inicial
  imprimirMensajeInicial();

  // Reinicia el EEPROM cada vez que se ejecute el programa
  if (false) {
    S_Inicial ini;
    ini.ini_libre = sizeof(S_Inicial);
    EEPROM.put(0, ini);

    S_Usuario usu;
    strcpy(usu.nombre, "USU1");
    strcpy(usu.contrasenia, "11111");
    usu.num_celular = 100;
    guardarUsuario(usu);

    strcpy(usu.nombre, "USU2");
    strcpy(usu.contrasenia, "22222");
    usu.num_celular = 125;
    guardarUsuario(usu);

    strcpy(usu.nombre, "USU3");
    strcpy(usu.contrasenia, "33333");
    usu.num_celular = 150;
    guardarUsuario(usu);

    mostrarUsuariosEEPROMConsola();
  }
}

void loop() {
  char llave = teclado.getKey();
  if (llave != NO_KEY) {
    Serial.println(llave);
  }
  // switch(estado_app){
  //   case MENU:
  //     break;
  //   case INICIO_SESION:
  //     break;
  // }

  // char respuesta[2];
  // Serial3.print("L1"); // Se envia un comando al arduino secundario
  // Serial3.readBytes(respuesta, 2); // Se lee la respuesta del arduino secundario y se almacena en el char 'respuesta'
}

/***********************************/
/************* USUARIO *************/
/***********************************/

// Se encarga de almacenar el usuario en el EEPROM
void guardarUsuario(S_Usuario usuario_nuevo) {

  S_Inicial puntero;  // Servira para leer los punteros existentes
  S_Usuario usu_aux;  // Servira para leer usuario x usuario en la memoria EEPROM
  int pos_aux;        // Almacena la posicion donde se encuentra el ultimo registro de la estructura usuario

  // Se obtiene la estructura que contiene la informacion del puntero
  EEPROM.get(0, puntero);

  // Si el puntero de inicio del usuario es igual a -1 quiere decir que no existe un registro en la memoria EEPROM
  if (puntero.ini_usuario == -1) {
    // Se inserta el nuevo usuario
    EEPROM.put(puntero.ini_libre, usuario_nuevo);

    // Se actualiza la posicion de inicio del usuario y tambien la nueva posicion libre
    puntero.ini_usuario = puntero.ini_libre;
    puntero.ini_libre += sizeof(S_Usuario);
    EEPROM.put(0, puntero);
  }
  // Si el puntero de inicio del usuario es diferente de -1 quiere decir que ya puede ser leeido en la memoria EEPROM
  else {
    // Se lee el primer registro
    EEPROM.get(puntero.ini_usuario, usu_aux);
    pos_aux = puntero.ini_usuario;

    // Se busca el ultimo registro para poder ingresar el usuario nuevo
    while (usu_aux.siguiente != -1) {
      pos_aux = usu_aux.siguiente;
      EEPROM.get(usu_aux.siguiente, usu_aux);
    }

    // Se modifica el puntero 'siguiente' del ultimo registro para que apunte al nuevo registro a ingresar
    usu_aux.siguiente = puntero.ini_libre;
    EEPROM.put(pos_aux, usu_aux);

    // Se inserta el nuevo usuario
    EEPROM.put(usu_aux.siguiente, usuario_nuevo);

    // Se actualiza la nueva posicion libre
    puntero.ini_libre += sizeof(S_Usuario);
    EEPROM.put(0, puntero);
  }

  return true;
}

// Se encarga de eliminar un usuario que esta en el EEPROM segun su nombre
void eliminarUsuario(const char* nombre) {

  S_Inicial puntero;      // Servira para leer los punteros existentes
  S_Usuario usu_actual;   // Servira para leer usuario x usuario en la memoria EEPROM
  int pos_anterior = -1;  // Almacena la posicion de un registro anterior
  int pos_actual = -1;    // Almacena la posicion del registro actual

  // Se obtiene la estructura que contiene la informacion del puntero
  EEPROM.get(0, puntero);
  // Se setea la posicion actual de lectura
  pos_actual = puntero.ini_usuario;

  do {

    // Se lee el registro
    EEPROM.get(pos_actual, usu_actual);

    // Se realiza la eliminacion del usuario
    if (strcmp(usu_actual.nombre, nombre) == 0) {

      // Se elimina el primer usuario registrado
      if (pos_anterior == -1) {
        puntero.ini_usuario = usu_actual.siguiente;
        EEPROM.put(0, puntero);
      }
      // Se elimina un usuario posterior al registrado
      else {
        // Se obtiene al registro anterior en referencia al actual para modificar el siguiente
        S_Usuario usu_anterior;
        EEPROM.get(pos_anterior, usu_anterior);

        // Se modifica el siguiente del registro anterior
        usu_anterior.siguiente = usu_actual.siguiente;

        // Se guarda el siguiente del registro anterior
        EEPROM.put(pos_anterior, usu_anterior);
      }

      break;
    }

    pos_anterior = pos_actual;
    pos_actual = usu_actual.siguiente;

  } while (usu_actual.siguiente != -1);
}

// Se encarga de verificar si existe un usuario con el mismo nombre en el EEPROM
bool existenciaUsuario(const char* nombre) {

  S_Inicial puntero;    // Servira para leer los punteros existentes
  S_Usuario usu_aux;    // Servira para leer usuario x usuario en la memoria EEPROM
  int pos_actual = -1;  // Servira como indice para empezar a leer una estructura de usuario

  // Se obtiene la estructura que contiene la informacion del puntero
  EEPROM.get(0, puntero);
  pos_actual = puntero.ini_usuario;

  do {
    // Se lee el registro
    EEPROM.get(pos_actual, usu_aux);

    // Se indica que ya existe un usuario con el nombre indicado
    if (strcmp(usu_aux.nombre, nombre) == 0) {
      return true;
    }

    // Se modifica la posicion actual para verificar el siguiente registro
    pos_actual = usu_aux.siguiente;

  } while (usu_aux.siguiente != -1);

  // Se indica que no existe el nombre de usuario indicado
  return false;
}

// Muestra en consola todos los usuarios que estan registrados en el EEPROM
void mostrarUsuariosEEPROMConsola() {
  Serial.println("USUARIOS:");
  S_Usuario usu_aux;
  S_Inicial puntero;  // Servira para leer los punteros existentes

  // Se obtiene la estructura que contiene la informacion del puntero
  EEPROM.get(0, puntero);

  if (puntero.ini_usuario != -1) {
    // Se obtiene el primer registro
    int posicion_actual = puntero.ini_usuario;

    // Se recorre cada registro
    do {
      EEPROM.get(posicion_actual, usu_aux);
      Serial.println(usu_aux.nombre);
      Serial.println(usu_aux.contrasenia);
      Serial.println(usu_aux.num_celular);
      Serial.println(usu_aux.siguiente);
      posicion_actual = usu_aux.siguiente;
    } while (usu_aux.siguiente != -1);
  }
}

/***********************************/
/*************** LOGS **************/
/***********************************/

// Se encarga de almacenar el log en el EEPROM
void guardarLog(S_Log log_nuevo) {

  S_Inicial puntero;  // Servira para leer los punteros existentes
  S_Log log_aux;      // Servira para leer log x log en la memoria EEPROM
  int pos_aux;        // Almacena la posicion donde se encuentra el ultimo registro de la estructura log

  // Se obtiene la estructura que contiene la informacion del puntero
  EEPROM.get(0, puntero);

  // Si el puntero de inicio del log es igual a -1 quiere decir que no existe un registro en la memoria EEPROM
  if (puntero.ini_log == -1) {
    // Se inserta el nuevo log
    EEPROM.put(puntero.ini_libre, log_nuevo);

    // Se actualiza la posicion de inicio del log y tambien la nueva posicion libre
    puntero.ini_log = puntero.ini_libre;
    puntero.ini_libre += sizeof(S_Log);
    EEPROM.put(0, puntero);
  }
  // Si el puntero de inicio del log es diferente de -1 quiere decir que ya puede ser leeido en la memoria EEPROM
  else {
    // Se lee el primer registro
    EEPROM.get(puntero.ini_log, log_aux);
    pos_aux = puntero.ini_log;

    // Se busca el ultimo registro para poder ingresar el log nuevo
    while (log_aux.siguiente != -1) {
      pos_aux = log_aux.siguiente;
      EEPROM.get(log_aux.siguiente, log_aux);
    }

    // Se modifica el puntero 'siguiente' del ultimo registro para que apunte al nuevo registro a ingresar
    log_aux.siguiente = puntero.ini_libre;
    EEPROM.put(pos_aux, log_aux);

    // Se inserta el nuevo log
    EEPROM.put(log_aux.siguiente, log_nuevo);

    // Se actualiza la nueva posicion libre
    puntero.ini_libre += sizeof(S_Log);
    EEPROM.put(0, puntero);
  }
}

// Muestra en consola todos los usuarios que estan registrados en el EEPROM
void mostrarLogsEEPROMConsola() {
  Serial.println("LOGS:");
  S_Log log_aux;
  S_Inicial puntero;  // Servira para leer los punteros existentes

  // Se obtiene la estructura que contiene la informacion del puntero
  EEPROM.get(0, puntero);

  if (puntero.ini_log != -1) {
    // Se obtiene el primer registro
    int posicion_actual = puntero.ini_log;

    // Se recorre cada registro
    do {
      EEPROM.get(posicion_actual, log_aux);
      Serial.println(log_aux.id);
      Serial.println(log_aux.descripcion);
      Serial.println(log_aux.siguiente);
      posicion_actual = log_aux.siguiente;
    } while (log_aux.siguiente != -1);
  }
}

/***********************************/
/************** UTIL ***************/
/***********************************/

// Imprime el mensaje inicial en la pantalla LCD
void imprimirMensajeInicial() {
  lcd.clear();              // Se limpia el LCD
  lcd.setCursor(1, 0);      // Se agrega al cursor para empezar a escribir en columna = 1, fila = 0
  lcd.print("Bienvenido");  // Se imprime un texto

  lcd.setCursor(0, 1);          // Se agrega al cursor para empezar a escribir en columna = 0, fila = 1
  lcd.print("GRP 01   SEC B");  // Se imprime un texto

  lcd.createChar(0, caracter_bluetooth);  // Se crea el caracter customizado
  lcd.setCursor(0, 0);                    // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
  lcd.write(byte(0));                     // Se escribe el caracter
  lcd.setCursor(11, 0);                   // Se agrega al cursor para empezar a escribir en columna = 11, fila = 0
  lcd.write(byte(0));                     // Se escribe el caracter
}

// Valida que el texto cumpla con la siguiente expresion regular: [A-Z0-9]+
bool validarTexto(String texto) {
  for (int i = 0; i < texto.length(); i++) {
    char c = texto.charAt(i);
    if (!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
      return false;
    }
  }
  return true;
}

// Valida que el texto cumpla con la siguiente expresion regular: [0-9]+
bool validarNumeroTelefono(String texto) {
  for (int i = 0; i < texto.length(); i++) {
    char c = texto.charAt(i);
    if (!(c >= '0' && c <= '9')) {
      return false;
    }
  }
  return true;
}

// Valida que el texto cumpla con la siguiente expresion regular: [A-Z0-9*#$!]+
bool validarContrasenia(String texto) {
  for (int i = 0; i < texto.length(); i++) {
    char c = texto.charAt(i);
    if (!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '*' || c == '#' || c == '$' || c == '!')) {
      return false;
    }
  }
  return true;
}

// Se encarga de cifrar los datos aplicando XOR a cada char
String cifrarDato(char datos[]) {

  // Primer pasada
  for (int i = 0; i < strlen(datos); i++) {
    datos[i] = datos[i] ^ CLAVE_1;
  }

  // Segunda pasada
  for (int i = 0; i < strlen(datos); i++) {
    datos[i] = datos[i] ^ CLAVE_2;
  }

  return datos;
}
