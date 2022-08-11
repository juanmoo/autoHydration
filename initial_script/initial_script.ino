const int AirValue = 878;                 //you need to replace this value with fully dry soil level, see calibration steps in docs
const int WaterValue = 438;               //you need to replace this value with moist soil level, see calibration steps in docs
const int moisturePercentSetPoint = 50;   //tweak this value to change how wet the soil is

int soilMoistureValue = 0;
int soilMoisturePercent = 0;
long int data;
int relay = D2; //specifies the relay pin
int soilSensor = A0; //specifies the soil sensor pin

void setup() {
  Serial.begin(115200); //open serial port for debugging
  pinMode(soilSensor, INPUT); //configure the sensor pin as input
  pinMode(relay, OUTPUT); //configure the relay pin as output
  digitalWrite(relay, HIGH); //set the relay to the motor off position initially
}

void loop() {
  soilMoistureValue = analogRead(soilSensor); //read the soil sensor value
  Serial.println(soilMoistureValue); //print the soil sensor value to the serial monitor
  soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100); //map the soil sensor value to a percentage
  if(soilMoisturePercent < moisturePercentSetPoint) //if the soil is less wet than specified, turn on the pump
  {
    digitalWrite(relay, HIGH); //activates the water pump
    delay(500); //pause for effect
  }
  else if(soilMoisturePercent > moisturePercentSetPoint) //if the soil is more wet than expected, turn off the pump
  {
    digitalWrite(relay, LOW);  //shuts off the water pump
    delay(500); //pause for effect
  }
  Serial.print(soilMoisturePercent);
  Serial.println("%");
  delay(250);
}
