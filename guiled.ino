int incomingByte = 0;
int tON = 1000;
byte RXBuf[64];

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);

}

void hidup(int tON){
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      delay(tON);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      delay(tON);
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      delay(tON);
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, HIGH);
      delay(tON);
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      delay(tON);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      delay(tON);
}

void kedip(int tON){
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        delay(tON);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(11, HIGH);
        digitalWrite(10, HIGH);
        delay(tON);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()){
    char in = Serial.read();
     switch (in){
      case 'A':
        for (int x = 0; x < 255; x ++)
        {
            x = 0;
            hidup(tON);
            if (Serial.available()){
            int nBytes = Serial.readBytes(RXBuf,sizeof(RXBuf));
            if (nBytes>=2) {
            tON  = int(RXBuf[0])*100;
            Serial.print("Confirm tON = ");
            Serial.print(tON, DEC);
            Serial.print(" ms ");
            }
          }
            continue;
        }
        break;

      case 'B':
      for (int x = 0; x < 255; x++){
        x=0;
        kedip(tON);
        if (Serial.available()){
          int nBytes = Serial.readBytes(RXBuf,sizeof(RXBuf));
          if (nBytes>=2) {
          tON  = int(RXBuf[0])*100;
          Serial.print("Confirm tON = ");
          Serial.print(tON, DEC);
          Serial.print(" ms ");
          }
        }
        continue;
      }
        break;
     }
  }
}
