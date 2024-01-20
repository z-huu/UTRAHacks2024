// IR Obstacle Collision Detection Module

int LED = 13; // Use the onboard Uno LED
int isObstaclePin = 7; // This is our input pin
int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(isObstaclePin, INPUT);
    Serial.begin(9600);
}

void loop() {
    isObstacle = digitalRead(isObstaclePin);
    if (isObstacle == LOW) {
        digitalWrite(LED, HIGH); // LED is high if there is an obstacle
    } else {
        digitalWrite(LED, LOW);
    }
    delay(200);
}