// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// HC-SR04
int trig = 41;
int echo = 39;
long duration;
float distance;

const int bufferSize = 50;
float readings[bufferSize];
int currentIndex = 0;
int total = 0;
int average = 0;


void setup()
{
  // Init serial
  Serial.begin(9600);

  // Init HC-SR04
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
}

float read_distance() {
    // Send target signal 10 microsecond
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Waiting receiveing signal and compute distance
    duration = float(pulseIn(echo, HIGH));
    distance = duration / 58.0; // http://www.gotronic.fr/pj2-hc-sr04-utilisation-avec-picaxe-1343.pdf

    return distance;
}

float read_distances() {
  float total = 0;

  for (int i=0; i < bufferSize; i++){
    readings[i] = read_distance();
    delay(100);
  }

  for (int i=0; i < bufferSize; i++){
    float value = readings[i];
    total += value;
    Serial.println(value);
  }

  float average = total / float(bufferSize);
  Serial.println("===");
  Serial.println(average);
  Serial.println("===");
  Serial.println("");
  Serial.println("");
  Serial.println("");

  return average;
}

void loop()
{
    distance = read_distances();
    delay(1000);
}
