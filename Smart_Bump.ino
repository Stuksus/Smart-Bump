#include <NewPing.h>
 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 30
int arrayDistant[10];
int arrayTime[10];
int arrayRasDist[5];
int arrayRasTime[5];
double arraySpeed[5];
int flag = 0;
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  if (sonar.ping_cm() == 0){
    Serial.println("Nothing");
    
  }
  else{
      for(int i = 0; i<10; i++){            // запись данных в массивы
        arrayDistant[i] = sonar.ping_cm(); // запись растояния в массив
        arrayTime[i] = millis(); // запись времени в массив
        Serial.print("Diatant number(");
        Serial.print(i); 
        Serial.print(") = ");
        Serial.print(arrayDistant[i]);
        Serial.println();
        Serial.println(arrayTime[i]);
        delay(100);
        }
          for(int j = 0; j < 10; j+=2){
            int rasTime = arrayTime[j+1] - arrayTime[j]; // получение разности растояния(между пятью прами значений)
            int rasDist = arrayDistant[j]-arrayDistant[j+1];  // получение разности времени(между пятью прами значений)
            arrayRasTime[flag] = abs(rasTime);  // запись данных разности в массив (время)
          arrayRasDist[flag] = abs(rasDist);  // запись данных разности в массив (расстояние)
          flag++;
          }
          for (int i = 0;i<5; i++){
          Serial.print("Diatant ras number(");
          Serial.print(i); 
          Serial.print(") = ");
          Serial.println(arrayRasDist[i]);  // вывод данных массива разности (растояние)
          Serial.print("Time ras number(");
          Serial.print(i); 
          Serial.print(") = ");
          Serial.println(arrayRasTime[i]); // вывод данных массива разности(время)
       } 

        for ( int i = 0; i < 5 ; i++){
        double speedCar = arrayRasDist[i]/arrayRasTime[i] ;
        arraySpeed[i] = abs(speedCar);
        Serial.print("Speed number (");
        Serial.print(i);
        Serial.print("):");
        Serial.println(arraySpeed[i]);
        Serial.println();
        }
        
  }
  
}
    
    
  /*Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");*/

