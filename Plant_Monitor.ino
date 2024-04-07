#define MOISTURE_SENSOR A0                    // Moisture Sensor pin
#define LIGHT_SENSOR A1                       // Moisture Sensor pin
#define BLUE_LED 13                           // Blue LED pin
#define YELLOW_LED 12                         // Red LED pin

#define M_THRESHOLD 300                       // Min moisture threshold
#define L_THRESHOLD 500                       // Min light threshold
#define T_THRESHOLD 64800000                  // 18 hours in milliseconds
#define TWO_MINUTES 120000                    // 2 minutes in milliseconds

#define LED_ON(x) digitalWrite(x, HIGH)       // Turn on LED
#define LED_OFF(x) digitalWrite(x, LOW)       // Turn off LED

int moisture_level = 0;                       // Init moisture level variable
int light_level = 0;                          // Init light level variable
bool eighteen_hours = false;                  // Init current time variable

void setup() {

  // LEDs as output
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Read values from sensors
  moisture_level = analogRead(MOISTURE_SENSOR);
  light_level = analogRead(LIGHT_SENSOR);

  // Check moisture is above threshold for moist soil
  if(moisture_level < M_THRESHOLD) 
    LED_ON(BLUE_LED);    
  else
    LED_OFF(BLUE_LED);

  // Check light is above threshold for optimal light \
     and if 18 hours has passed 
  eighteen_hours = ((millis() % T_THRESHOLD) <= TWO_MINUTES) ? true : false;
  if(light_level < L_THRESHOLD && eighteen_hours == true)
    LED_ON(YELLOW_LED);    
  else
    LED_OFF(YELLOW_LED);
  
  // Check sensor data every 2 minutes
  delay(TWO_MINUTES);
}
