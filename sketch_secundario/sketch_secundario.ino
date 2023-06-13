#include <LiquidCrystal.h>
#include <LedControl.h>
#include "Estructuras_Auxiliares.h"

LedControl matriz_driver = LedControl(51, 53, 52, 1);  // Matriz con driver
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);                   // Pantalla LCD

void setup() {
  Serial3.begin(9600);  // Inicializa la comunicacion con el arduino principal
  lcd.begin(16, 2);     // Inicializa el LCD

  // Inicializando la matriz con driver
  matriz_driver.shutdown(0, false);
  matriz_driver.setIntensity(0, 8);
  matriz_driver.clearDisplay(0);

  // Mensaje inicial
  imprimirMensajeInicial();
}

void loop() {
  // put your main code here, to run repeatedly:
}

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
