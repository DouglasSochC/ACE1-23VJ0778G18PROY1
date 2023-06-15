void setup() {
  Serial3.begin(9600);  // Inicializa la comunicacion con el arduino principal
}

void loop() {

  // Se esta recibiendo datos por parte del arduino principal
  if(Serial3.available() > 0){

  }
}
