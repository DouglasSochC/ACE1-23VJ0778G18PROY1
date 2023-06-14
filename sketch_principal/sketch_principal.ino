#include <Keypad.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <LedControl.h>
#include "Estructuras_Auxiliares.h"

// Pines
LedControl matriz_driver = LedControl(51, 53, 52, 1);                        // Matriz con driver
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);                                         // Pantalla LCD
byte Fpines[4] = { 22, 23, 24, 25 };                                         // Pines para manejar las filas del teclado
byte Cpines[4] = { 26, 27, 28 };                                             // Pines para manejar las columnas del teclado
Keypad teclado = Keypad(makeKeymap(valores_teclado), Fpines, Cpines, 4, 3);  // Mapeo de los valores que se obtienen a traves del teclado
#define PIN_ACEPTAR 8                                                        // Pin para manejar la aceptacion de alguna accion
#define PIN_CANCELAR 9                                                       // Pin para manejar la cancelacion de alguna accion

// Estados del programa
#define SECUENCIA_INICIAL 0
#define MENU_PRINCIPAL 1
#define INICIO_SESION 2
#define REGISTRO_USUARIO 3
int estado_app = SECUENCIA_INICIAL;  // Indica el estado actual en el que esta el programa

// Util
#define CLAVE_1 '2'            // Representa el valor que sera utilizado para aplicar un XOR en la primera pasada
#define CLAVE_2 '9'            // Representa el valor que sera utilizado para aplicar un XOR en la segunda pasada
bool imprimir_mensaje = true;  // Es utilizada para imprimir informacion una sola vez al LCD
String entrada = "";           // Es utilizada para determinar si ya se ha eligido una entrada; las opciones que se pueden encontrar son: P (panel), M (movil) y B (un auxiliar para la conexion bluetooth)
String temp_texto = "";        // Es utilizado para almacenar la informacion obtenida atraves del panel de operacion o la aplicacion movil
S_Usuario temp_usuario;        // Es utilizado para almacenar la informacion del usuario obtenida a traves de del panel de operacion o la aplicacion movil

void setup() {

  Serial.begin(9600);   // Inicializa la comunicacion con el virtual terminal
  Serial1.begin(9600);  // Inicializa la comunicacion con el HC-05
  Serial3.begin(9600);  // Inicializa la comunicacion con el segundo arduino
  lcd.begin(16, 4);     // Inicializa el LCD

  // Inicializando la matriz con driver
  matriz_driver.shutdown(0, false);
  matriz_driver.setIntensity(0, 8);
  matriz_driver.clearDisplay(0);

  // Reinicia el EEPROM cada vez que se ejecute el programa
  if (true) {

    S_Inicial ini;
    ini.ini_libre = sizeof(S_Inicial);
    EEPROM.put(0, ini);

    S_Usuario usu;
    strcpy(usu.nombre, "ADMIN*22922");
    strcpy(usu.contrasenia, "GRUPO18");
    strcpy(usu.admin, "1");
    guardarUsuario(usu);
  }
}

void loop() {

  if (estado_app == SECUENCIA_INICIAL) {
    imprimirMensajeInicial(0);
    delay(500);
    imprimirMensajeInicial(-1);
    delay(500);
    estado_app = MENU_PRINCIPAL;
  } else if (estado_app == MENU_PRINCIPAL) {

    // Imprimiendo opciones disponibles
    if (imprimir_mensaje) {
      imprimirMenuPrincipal();
      imprimir_mensaje = false;
    }

    // Selecciona alguna opcion del menu principal
    char llave = teclado.getKey();
    if (llave != NO_KEY) {
      temp_texto += llave;
      lcd.setCursor(0, 3);           // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
      lcd.print(">>" + temp_texto);  // Se imprime un texto
    }
  } else if (estado_app == INICIO_SESION) {

    if (entrada == "") {  // Seleccionando el tipo de entrada que sera utilizada para el inicio de sesion

      // Imprimiendo opciones disponibles
      if (imprimir_mensaje) {
        imprimirEntradaAPP();
        imprimir_mensaje = false;
      }

      // Interaccion atraves del panel de operacion
      char llave = teclado.getKey();
      if (llave != NO_KEY) {
        temp_texto += llave;
        lcd.setCursor(0, 3);           // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
        lcd.print(">>" + temp_texto);  // Se imprime un texto
      }
    } else if (entrada == "B") {  // Si selecciono MOVIL entonces se hara la conexion bluetooth
      // Imprimiendo opciones disponibles
      if (imprimir_mensaje) {
        imprimirConexionBluetooth();
        imprimir_mensaje = false;
      }

      // Recibiendo la respuesta
      if (Serial1.available() > 0) {
        entrada = "M";
        reiniciarVariableAuxiliares();
      }
    } else if (entrada == "M") {  // Trabajando con la app movil
      Serial.println("ESTOY EN MOVIL");
      // Hay que recordar que al final de utilizar esta opcion hay que reiniciar la entrada a ""
    } else if (entrada == "P") {  // Trabajando con el panel de operaciones
      Serial.println("ESTOY EN PANEL DE OPERACION");
      // Hay que recordar que al final de utilizar esta opcion hay que reiniciar la entrada a ""
    }

  } else if (estado_app == REGISTRO_USUARIO) {

    if (entrada == "") {  // Seleccionando el tipo de entrada que sera utilizada para el registro de usuario
      // Imprimiendo opciones disponibles
      if (imprimir_mensaje) {
        imprimirEntradaAPP();
        imprimir_mensaje = false;
      }

      // Interaccion atraves del panel de operacion
      char llave = teclado.getKey();
      if (llave != NO_KEY) {
        temp_texto += llave;
        lcd.setCursor(0, 3);           // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
        lcd.print(">>" + temp_texto);  // Se imprime un texto
      }
    } else if (entrada == "B") {  // Si selecciono MOVIL entonces se hara la conexion bluetooth
      // Imprimiendo opciones disponibles
      if (imprimir_mensaje) {
        imprimirConexionBluetooth();
        imprimir_mensaje = false;
      }

      // Recibiendo la respuesta
      if (Serial1.available() > 0) {
        entrada = "M";
        reiniciarVariableAuxiliares();
      }
    } else if (entrada == "M") {  // Trabajando con la app movil
      Serial.println("ESTOY EN MOVIL");
      // Hay que recordar que al final de utilizar esta opcion hay que reiniciar la entrada a ""
    } else if (entrada == "P") {  // Trabajando con el panel de operaciones
      Serial.println("ESTOY EN PANEL DE OPERACION");
      // Hay que recordar que al final de utilizar esta opcion hay que reiniciar la entrada a ""
    }
  }

  botonAceptar();
  botonCancelar();
  // char respuesta[2];
  // Serial3.print("L1"); // Se envia un comando al arduino secundario
  // Serial3.readBytes(respuesta, 2); // Se lee la respuesta del arduino secundario y se almacena en el char 'respuesta'
}

/***********************************/
/************* USUARIO *************/
/***********************************/

// Se encarga de almacenar el usuario en el EEPROM
void guardarUsuario(S_Usuario usuario_nuevo) {

  // Se cifran los datos
  cifrarDato(usuario_nuevo.nombre);
  cifrarDato(usuario_nuevo.contrasenia);
  cifrarDato(usuario_nuevo.num_celular);
  cifrarDato(usuario_nuevo.admin);

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
      // Descifrando la informacion
      descifrarDato(usu_aux.nombre);
      descifrarDato(usu_aux.contrasenia);
      descifrarDato(usu_aux.num_celular);
      descifrarDato(usu_aux.admin);

      // Imprimiendo lo que se ha encontrado
      Serial.println(usu_aux.nombre);
      Serial.println(usu_aux.contrasenia);
      Serial.println(usu_aux.num_celular);
      Serial.println(usu_aux.admin);
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
/************ BOTONES **************/
/***********************************/

// Reconoce el boton de aceptar presionado
bool estado_boton_aceptar = false;
bool ultimo_estado_boton_aceptar = false;
unsigned long ultimo_tiempo_rebote_boton_aceptar = 0;
const unsigned long delay_rebote_boton_aceptar = 50;
void botonAceptar() {

  int btnAceptar = digitalRead(PIN_ACEPTAR);

  if (btnAceptar != ultimo_estado_boton_aceptar) {
    ultimo_tiempo_rebote_boton_aceptar = millis();
  }

  if ((millis() - ultimo_tiempo_rebote_boton_aceptar) > delay_rebote_boton_aceptar) {
    if (btnAceptar != estado_boton_aceptar) {
      estado_boton_aceptar = btnAceptar;

      if (estado_boton_aceptar == LOW) {

        if (estado_app == MENU_PRINCIPAL) {

          if (temp_texto == "1") {
            estado_app = INICIO_SESION;
          } else if (temp_texto == "2") {
            estado_app = REGISTRO_USUARIO;
          }
          reiniciarVariableAuxiliares();

        } else if (estado_app == INICIO_SESION && entrada == "") {
          if (temp_texto == "1") {
            entrada = "B";
          } else if (temp_texto == "2") {
            entrada = "P";
          }
          reiniciarVariableAuxiliares();
        } else if (estado_app == REGISTRO_USUARIO && entrada == "") {
          if (temp_texto == "1") {
            entrada = "B";
          } else if (temp_texto == "2") {
            entrada = "P";
          }
          reiniciarVariableAuxiliares();
        }
      }
    }
  }

  ultimo_estado_boton_aceptar = btnAceptar;
}

// Reconoce el boton de cancelar presionado
bool estado_boton_cancelar = false;
bool ultimo_estado_boton_cancelar = false;
unsigned long ultimo_tiempo_rebote_boton_cancelar = 0;
const unsigned long delay_rebote_boton_cancelar = 50;
void botonCancelar() {
  int btnCancelar = digitalRead(PIN_ACEPTAR);

  if (btnCancelar != ultimo_estado_boton_cancelar) {
    ultimo_tiempo_rebote_boton_cancelar = millis();
  }

  if ((millis() - ultimo_tiempo_rebote_boton_cancelar) > delay_rebote_boton_cancelar) {
    if (btnCancelar != estado_boton_cancelar) {
      estado_boton_cancelar = btnCancelar;

      if (estado_boton_cancelar == LOW) {
      }
    }
  }

  ultimo_estado_boton_cancelar = btnCancelar;
}

/***********************************/
/************** UTIL ***************/
/***********************************/

// Imprime el mensaje inicial en la pantalla LCD
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

// Imprime las opciones disponibles del menu principal
void imprimirEntradaAPP() {
  lcd.clear();                // Se limpia el LCD
  lcd.setCursor(0, 0);        // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
  lcd.print("Entrada:");      // Se imprime un texto
  lcd.setCursor(0, 1);        // Se agrega al cursor para empezar a escribir en columna = 0, fila = 1
  lcd.print("1) APP Movil");  // Se imprime un texto
  lcd.setCursor(0, 2);        // Se agrega al cursor para empezar a escribir en columna = 0, fila = 1
  lcd.print("2) Panel Op.");  // Se imprime un texto
}

// Imprime el mensaje de espera de conexion a la aplicacion movil
void imprimirConexionBluetooth() {
  lcd.clear();               // Se limpia el LCD
  lcd.setCursor(0, 0);       // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
  lcd.print("Esperando");    // Se imprime un texto
  lcd.setCursor(0, 1);       // Se agrega al cursor para empezar a escribir en columna = 0, fila = 1
  lcd.print("conexion...");  // Se imprime un texto
}

// Imprime las opciones disponibles del menu principal
void imprimirMenuPrincipal() {
  lcd.clear();               // Se limpia el LCD
  lcd.setCursor(0, 0);       // Se agrega al cursor para empezar a escribir en columna = 0, fila = 0
  lcd.print("1) Login");     // Se imprime un texto
  lcd.setCursor(0, 1);       // Se agrega al cursor para empezar a escribir en columna = 0, fila = 1
  lcd.print("2) Registro");  // Se imprime un texto
}

// Reinicia las variables auxiliares cada vez que se modifica el estado del app
void reiniciarVariableAuxiliares() {
  imprimir_mensaje = true;
  temp_texto = "";
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
void cifrarDato(char datos[]) {

  int tamanio = strlen(datos);
  // Primer pasada
  for (int i = 0; i < tamanio; i++) {
    datos[i] = datos[i] ^ CLAVE_1;
  }

  // Segunda pasada
  for (int i = 0; i < tamanio; i++) {
    datos[i] = datos[i] ^ CLAVE_2;
  }

  return datos;
}

// Se encarga de cifrar los datos aplicando XOR a cada char
void descifrarDato(char datos[]) {

  int tamanio = strlen(datos);

  // Segunda pasada
  for (int i = 0; i < tamanio; i++) {
    datos[i] = datos[i] ^ CLAVE_2;
  }

  // Primer pasada
  for (int i = 0; i < tamanio; i++) {
    datos[i] = datos[i] ^ CLAVE_1;
  }

  return datos;
}
