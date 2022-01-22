#include <eHealth.h>


void setup() {
  Serial.begin(115200);
  eHealth.readBloodPressureSensor();
  //eHealth.readGlucometer();
  //eHealth.initPositionSensor();
  //Serial.println("Press On/Off button please...");
  delay(500);
}

void loop() {
temperature();
bloodpressure();
//bodyposition();
//glucometer();

}
//=======================================================================================
void temperature(){
float sum = 0;
float average = 0;
        
  for (int a = 0; a<10; a++ )
    {     
     float temperature = eHealth.getTemperature();
           //Serial.print("Temperature (ºC): ");       
           // Serial.print(temperature, 2);  
           //Serial.println("");
     sum=sum+temperature;
    } 

average = sum/10;

Serial.println("============ Temperature =================");
Serial.print("Temperature (ºC): ");
Serial.println(average);
Serial.println("============ Temperature =================");                     
delay(100);
 }
//=======================================================================================
void bodyposition(){
 Serial.print("Current position : ");
  uint8_t position = eHealth.getBodyPosition(); 
  eHealth.printPosition(position);  

  Serial.print("\n");
  delay(1000); // wait for a second.
}
//=======================================================================================
void bloodpressure(){
   euint8_t numberOfData = eHealth.getBloodPressureLength();   
  Serial.print(F("Number of measures : "));    
  Serial.println(numberOfData, DEC);   
  delay(100);

  for (int i = 0; i<numberOfData; i++) { 
    // The protocol sends data in this order 
    Serial.println(F("=========================================="));

    Serial.print(F("Measure number "));
    Serial.println(i + 1);

    Serial.print(F("Date -> ")); 
    Serial.print(eHealth.bloodPressureDataVector[i].day); 
    Serial.print(F(" of ")); 
    Serial.print(eHealth.numberToMonth(eHealth.bloodPressureDataVector[i].month));
    Serial.print(F(" of "));
    Serial.print(2000 + eHealth.bloodPressureDataVector[i].year);    
    Serial.print(F(" at "));

    if (eHealth.bloodPressureDataVector[i].hour < 10) {
      Serial.print(0); // Only for best representation.
    }

    Serial.print(eHealth.bloodPressureDataVector[i].hour);
    Serial.print(F(":"));

    if (eHealth.bloodPressureDataVector[i].minutes < 10) {
      Serial.print(0);// Only for best representation.
    }
    Serial.println(eHealth.bloodPressureDataVector[i].minutes);

    Serial.print(F("Systolic value : ")); 
    Serial.print(30+eHealth.bloodPressureDataVector[i].systolic);
    Serial.println(F(" mmHg"));
    
    Serial.print(F("Diastolic value : ")); 
    Serial.print(eHealth.bloodPressureDataVector[i].diastolic);
    Serial.println(F(" mmHg"));
    
    Serial.print(F("Pulse value : ")); 
    Serial.print(eHealth.bloodPressureDataVector[i].pulse);
    Serial.println(F(" bpm"));
  }

  delay(20000);
}
//=======================================================================================
void glucometer(){
uint8_t numberOfData = eHealth.getGlucometerLength();   
  Serial.print(F("Number of measures : "));    
  Serial.println(numberOfData, DEC);   
  delay(100);


  for (int i = 0; i<numberOfData; i++) { 
    // The protocol sends data in this order 
    Serial.println(F("=========================================="));

    Serial.print(F("Measure number "));
    Serial.println(i + 1);

    Serial.print(F("Date -> ")); 
    Serial.print(eHealth.glucoseDataVector[i].day); 
    Serial.print(F(" of ")); 
    Serial.print(eHealth.numberToMonth(eHealth.glucoseDataVector[i].month));
    Serial.print(F(" of "));
    Serial.print(2000 + eHealth.glucoseDataVector[i].year);    
    Serial.print(F(" at "));

    if (eHealth.glucoseDataVector[i].hour < 10) {
      Serial.print(0); // Only for best representation.
    }

    Serial.print(eHealth.glucoseDataVector[i].hour);
    Serial.print(F(":"));

    if (eHealth.glucoseDataVector[i].minutes < 10) {
      Serial.print(0);// Only for best representation.
    }
    Serial.print(eHealth.glucoseDataVector[i].minutes);

    if (eHealth.glucoseDataVector[i].meridian == 0xBB)
      Serial.println(F(" pm"));
    else if (eHealth.glucoseDataVector[i].meridian == 0xAA)
      Serial.println(F(" am")); 

    Serial.print(F("Glucose value : ")); 
    Serial.print(eHealth.glucoseDataVector[i].glucose);
    Serial.println(F(" mg/dL"));
  }

  delay(20000);
}
