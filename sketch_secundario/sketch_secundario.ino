void setup() {
  Serial3.begin(9600);  // Inicializa la comunicacion con el arduino principal
}

char solicitud[2];
void loop() {

  if (Serial3.available()) {
    Serial3.readBytes(solicitud, 2);
    if (solicitud[0] == 'S') {
      if (solicitud[1] == '1') {
        Serial3.print(analogRead(A0));
      } else if (solicitud[1] == '2') {
        Serial3.print(analogRead(A1));
      } else if (solicitud[1] == '3') {
        Serial3.print(analogRead(A2));
      } else if (solicitud[1] == '4') {
        Serial3.print(analogRead(A3));
      } else if (solicitud[1] == '5') {
        Serial3.print(analogRead(A4));
      } else if (solicitud[1] == '6') {
        Serial3.print(analogRead(A5));
      } else if (solicitud[1] == '7') {
        Serial3.print(analogRead(A6));
      } else if (solicitud[1] == '8') {
        Serial3.print(analogRead(A7));
      } else if (solicitud[1] == '9') {
        Serial3.print(analogRead(A8));
      }
    } else if (solicitud[0] == 'B') {
      if (solicitud[1] == '1') {
        Serial3.print(digitalRead(22));
      } else if (solicitud[1] == '2') {
        Serial3.print(digitalRead(23));
      } else if (solicitud[1] == '3') {
        Serial3.print(digitalRead(24));
      } else if (solicitud[1] == '4') {
        Serial3.print(digitalRead(25));
      } else if (solicitud[1] == '5') {
        Serial3.print(digitalRead(26));
      } else if (solicitud[1] == '6') {
        Serial3.print(digitalRead(27));
      } else if (solicitud[1] == '7') {
        Serial3.print(digitalRead(28));
      } else if (solicitud[1] == '8') {
        Serial3.print(digitalRead(29));
      } else if (solicitud[1] == '9') {
        Serial3.print(digitalRead(30));
      }
    }
  }
}
