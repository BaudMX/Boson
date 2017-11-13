#define TRIGGER_PIN_x 3
#define ECHO_PIN_x 2
#define PWM_PIN 5

#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 10
#define MEASURE_SAMPLES 18
#define MEASURE_DELAY 40


String x = "";

char x_[50];

void setup()
{
  // Serial monitoring
  Serial.begin(9600);
  
  // Initializing Trigger Output and Echo Input
  pinMode(TRIGGER_PIN_x, OUTPUT);
  pinMode(ECHO_PIN_x, INPUT);
  
  // Reset the trigger pin and wait a half a second
  digitalWrite(TRIGGER_PIN_x, LOW);

  delayMicroseconds(500);
}

long singleMeasurement_x()
{
  long duration = 0;
  
  // Measure: Put up Trigger...
  digitalWrite(TRIGGER_PIN_x, HIGH);
  // ... wait for 11 µs ...
  delayMicroseconds(11);
  // ... put the trigger down ...
  digitalWrite(TRIGGER_PIN_x, LOW);
  // ... and wait for the echo ...
  duration = pulseIn(ECHO_PIN_x, HIGH);
  return (long) (((float) duration / USONIC_DIV) * 10.0);
}

long measure_x()
{
  long measureSum = 0;
  for (int i = 0; i < MEASURE_SAMPLES; i++)
  {
    delay(MEASURE_SAMPLE_DELAY);
    measureSum += singleMeasurement_x();
  }
  return measureSum / MEASURE_SAMPLES;
}

void loop()
{
  delay(MEASURE_DELAY);
  int distance_x = measure_x()*0.1;
  
  //sprintf(x_, "%dx", distance_x);
  //Serial.println(x_);
 analogWrite(PWM_PIN,distance_x);
  Serial.println(distance_x);

}
