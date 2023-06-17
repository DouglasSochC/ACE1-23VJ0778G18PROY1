#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define TriggerIzquierda 3
#define TriggerDerecha 5
#define EchoIzquierda 2
#define EchoDerecha 4
#define LuzIzquierda 6
#define LuzDerecha 7

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

String limpiarFila = "                ";
int tamanoIzquierda = 0;
int tamanoDerecha = 0;

void setup()
{
  // initialize the LCD
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
}

void loop()
{
  int newIzquierda = EncenderIzquierda();
  Serial.println();
  Serial.print("Sensor de izquierda: ");
  Serial.println(newIzquierda);
  int newDerecha = EncenderDerecha();
  Serial.println();
  Serial.print("Sensor de derecha: ");
  Serial.println(newDerecha);
  int newLuzIzquierda = VerificarLuzIzquierda();
  Serial.println();
  Serial.print("valor luz izquierda: ");
  Serial.println(newLuzIzquierda);
  int newLuzDerecha = VerificarLuzDerecha();
  Serial.println();
  Serial.print("valor luz derecha: ");
  Serial.println(newLuzDerecha);
  if(newIzquierda != 0){
     if(newIzquierda < 17 && newLuzIzquierda == 0){
      lcd.setCursor(0,0);
      lcd.print(limpiarFila);
      lcd.setCursor(0,0);
      lcd.print("OCUPADO/ABIERTO");
    }else if(newIzquierda < 17 && newLuzIzquierda == 1){
      if(tamanoIzquierda == 0){
        lcd.setCursor(0,0);
        lcd.print(limpiarFila);
        lcd.setCursor(0,0);
        lcd.print("OCUPADO/CERRADO");
        tamanoIzquierda = newIzquierda;
        Serial.println();
        Serial.print("tamano izquierda: ");
        Serial.println(tamanoIzquierda);
      }else if(tamanoIzquierda < 17 && tamanoIzquierda != newIzquierda){
        lcd.setCursor(0,0);
        lcd.print(limpiarFila);
        lcd.setCursor(0,0);
        lcd.print("CAMBIO TELEFONO");
        Serial.println();
        Serial.print("tamano izquierda: ");
        Serial.println(tamanoIzquierda);
      }else if(tamanoIzquierda < 17 && tamanoIzquierda == newIzquierda){
        lcd.setCursor(0,0);
        lcd.print(limpiarFila);
        lcd.setCursor(0,0);
        lcd.print("TELEFONO LISTO");
        delay(3000);
        lcd.setCursor(0,0);
        lcd.print(limpiarFila);
        lcd.setCursor(0,0);
        lcd.print("OCUPADO/CERRADO");
        Serial.println();
        Serial.print("tamano izquierda: ");
        Serial.println(tamanoIzquierda);
      }
      
    }else if(newIzquierda > 17 && newLuzIzquierda == 0){
      lcd.setCursor(0,0);
      lcd.print(limpiarFila);
      lcd.setCursor(0,0);
      lcd.print("VACIO/ABIERTO");
    }else if(newIzquierda > 17 && newLuzIzquierda == 1){
      lcd.setCursor(0,0);
      lcd.print(limpiarFila);
      lcd.setCursor(0,0);
      lcd.print("VACIO/CERRADO");
    } 
  }else{
      lcd.setCursor(0,0);
      lcd.print(limpiarFila);
      lcd.setCursor(0,0);
      lcd.print("SIN LECTURA");
  }
  

  if(newDerecha != 0){
     if(newDerecha < 17 && newLuzDerecha == 0){
      lcd.setCursor(0,1);
      lcd.print(limpiarFila);
      lcd.setCursor(0,1);
      lcd.print("OCUPADO/ABIERTO");
    }else if(newDerecha < 17 && newLuzDerecha == 1){
      if(tamanoDerecha == 0){
        lcd.setCursor(0,1);
        lcd.print(limpiarFila);
        lcd.setCursor(0,1);
        lcd.print("OCUPADO/CERRADO");
        tamanoDerecha = newDerecha;
        Serial.println();
        Serial.print("tamano derecha: ");
        Serial.println(tamanoDerecha);
      }else if(tamanoDerecha < 17 && tamanoDerecha != newDerecha){
        lcd.setCursor(0,1);
        lcd.print(limpiarFila);
        lcd.setCursor(0,1);
        lcd.print("CAMBIO TELEFONO");
        Serial.println();
        Serial.print("tamano derecha: ");
        Serial.println(tamanoDerecha);
      }else if(tamanoDerecha < 17 && tamanoDerecha == newDerecha){
        lcd.setCursor(0,1);
        lcd.print(limpiarFila);
        lcd.setCursor(0,1);
        lcd.print("TELEFONO LISTO");
        delay(3000);
        lcd.setCursor(0,1);
        lcd.print(limpiarFila);
        lcd.setCursor(0,1);
        lcd.print("OCUPADO/CERRADO");
        Serial.println();
        Serial.print("tamano derecha: ");
        Serial.println(tamanoDerecha);
      }
    }else if(newDerecha > 17 && newLuzDerecha == 0){
      lcd.setCursor(0,1);
      lcd.print(limpiarFila);
      lcd.setCursor(0,1);
      lcd.print("VACIO/ABIERTO");
    }else if(newDerecha > 17 && newLuzDerecha == 1){
      lcd.setCursor(0,1);
      lcd.print(limpiarFila);
      lcd.setCursor(0,1);
      lcd.print("VACIO/CERRADO");
    }
  }else{
      lcd.setCursor(0,1);
      lcd.print(limpiarFila);
      lcd.setCursor(0,1);
      lcd.print("SIN LECTURA");
  } 
}


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

int VerificarLuzIzquierda(){
  int valorI = 0;
  valorI = digitalRead(LuzIzquierda);  
  delay(1000);
  return valorI;
}



int VerificarLuzDerecha(){
  int valorD = 0;
  valorD = digitalRead(LuzDerecha);  
  delay(1000);
  return valorD;
}
