#include <NewPing.h>
 #include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // Устанавливаем дисплей
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 100
const int sizeRasArray = 10;
const int sizeSimpleArray = 10;
int arrayDistant[sizeSimpleArray];
long arrayTime[sizeSimpleArray];
int arrayRasDist[sizeRasArray];
int arrayRasTime[sizeRasArray];
double arraySpeed[sizeRasArray];
int flag;
int betweenArray;
int inc;
int n;
double count;
double finishSpeed;

 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(57600);
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея

}
 
void loop() { 
  
  if (sonar.ping_cm() != 0){  // начинаем считывать данные
    flag = 0;
      for(int i = 0; i<sizeSimpleArray; i++){   // запись данных в массивы
        betweenArray = sonar.ping_cm();
        if (betweenArray == 0){
          inc = i;      
          break;    
        }
        else{
        arrayDistant[i] = betweenArray; // запись растояния в массив (нанометры)
        
        arrayTime[i] = millis(); // запись времени в массив
        Serial.print("Diatant number(");
        Serial.print(i); 
        Serial.print(") = ");
        Serial.print(arrayDistant[i]);
        Serial.println();
        Serial.println(arrayTime[i]);
        inc = i+1;
        
        }
        }
        Serial.println(inc);
          for(int j = 0; j < inc -1; j++){
            int rasTime = arrayTime[j+1] - arrayTime[j]; // получение разности растояния(между пятью прами значений)
            int rasDist = arrayDistant[j]-arrayDistant[j+1];  // получение разности времени(между пятью прами значений)
            arrayRasTime[flag] = abs(rasTime);  // запись данных разности в массив (время)
          arrayRasDist[flag] = abs(rasDist);  // запись данных разности в массив (расстояние)
          flag++;
          }
          for (int i = 0;i < inc; i++){
          Serial.print("Diatant ras number(");
          Serial.print(i); 
          Serial.print(") = ");
          Serial.println(arrayRasDist[i]);  // вывод данных массива разности (растояние)
          Serial.print("Time ras number(");
          Serial.print(i); 
          Serial.print(") = ");
          Serial.println(arrayRasTime[i]); // вывод данных массива разности(время)
       } 

        for ( int i = 0; i < inc-1; i++){
        double speedCar = (double)arrayRasDist[i]/arrayRasTime[i] ;
        arraySpeed[i] = abs(speedCar);
        Serial.print("Speed number (");
        Serial.print(i);
        Serial.print(")");
        Serial.println(arraySpeed[i]);
        Serial.println();
        }
  
  for ( int i = 0; i< inc;i++){
    if (arraySpeed[i] == 0.0  ){
      n++;  
      Serial.println(n);
    }
    }
    for ( int i = 0; i< inc;i++){
      count += arraySpeed[i];
    }

    lcd.clear();
    
        if (inc-n != 0){
    finishSpeed = count / (inc-n);
    }
    else{
      finishSpeed = 0.0;
    }
    lcd.print("Smart Speed Bump"); 
    lcd.setCursor(0, 1);
    lcd.print("Speed:");
    lcd.print(finishSpeed);
    Serial.print("Speed: ");
    Serial.println(finishSpeed);
    
  }
  else{
    Serial.println("Nothing");
    
   lcd.clear();
   lcd.print("Smart Speed Bump"); 
   lcd.setCursor(0, 1);
   lcd.print("Speed:0");
   lcd.noDisplay(); // выключаем подсветку LCD дисплея
   delay(600); // ставим паузу
   lcd.display(); // включаем подсветку LCD дисплея
   delay(600); 
        } 
  count = 0;
  n = 0;
  finishSpeed = 0 ;
  delay(200);
}

    
    

