# FunBin - Ultrasonic Distance Monitoring and Feedback System

FunBin is an Arduino-based project that utilizes an ultrasonic sensor to monitor distances and provides interactive feedback through various components such as an LCD display, an 8x8 dot matrix, a buzzer, and a servo motor. FunBin is designed to create an engaging and interactive experience by reacting differently based on the distance between objects.

## Components Used

- Arduino UNO board
- Ultrasonic sensor HC-SR04
- LCD display (I2C module)
- 8x8 dot matrix (MAX7219 module)
- Buzzer
- Servo motor SG90

## Pin Configuration

- `buzzerPin` - Pin connected to the buzzer
- `echoPin` - Pin connected to the echo pin of the ultrasonic sensor
- `trigPin` - Pin connected to the trigger pin of the ultrasonic sensor
- `DINPin` - Pin connected to the DIN pin of the 8x8 dot matrix module
- `CLKPin` - Pin connected to the CLK pin of the 8x8 dot matrix module
- `CSPin` - Pin connected to the CS pin of the 8x8 dot matrix module
- `ServoPin` - Pin connected to the signal pin of the servo motor

## Variables
- `lcd`: Variable named lcd of type **LiquidCrystal_I2C**, representing an LCD display. It is initialized with an I2C address of 0x27, 16 columns, and 2 rows.
- `lc`: Variable named **lc** of type **LedControl**, representing an 8x8 dot matrix LED display. It is initialized with the pins DINPin, CLKPin, and CSPin, and the number of connected LED matrices as 0.
- `srv`: Variable named **srv** of type **Servo**, representing a servo motor.
- `maxRange` - Maximum range for distance measurement
- `minRange` - Minimum range for distance measurement
- `duration` - Duration of the ultrasonic pulse
- `distance` - Calculated distance from the ultrasonic sensor
- `too_close_distance` - Threshold distance for detecting objects too close
- `display_string` - String variable to hold the display message

## Functions

### `setup()`

- Initializes the LCD display
- Sets the pin modes for the ultrasonic sensor, buzzer, and servo motor
- Initializes the 8x8 dot matrix module
- Attaches the servo motor and sets its initial position
- Starts the serial communication

### `loop()`

- Measures the distance using the ultrasonic sensor and stores it in the `distance` variable
- Checks if the distance is within the valid range
  - If the distance is out of range, in other words in IDLE status, displays a "Hi, I am FunBin!" message on the LCD, sets the servo motor position to 180 degrees so that the lid of the bin is open, and displays a neutral face on the dot matrix module
  - If the distance is in the middle range, rings the buzzer according to the distance, displays a "COME CLOSER!" message on the LCD, sets the servo motor position to 180 degrees so that the lid of the bin is open, and displays a sad face on the dot matrix module
  - If the distance is too close, rings the buzzer according to the distance, displays a "HAHAHA TOO CLOSE" message on the LCD, sets the servo motor position to 0 degrees so that the lid of the bin is close, and displays a happy face on the dot matrix module

### `dist_fnc(int maxRange, int minRange)`

- Calculates the distance from the ultrasonic sensor using the duration of the pulse
- Returns the calculated distance

### `ring_fnc(int distance1)`

- Generates a tone on the buzzer for a duration based on the distance
- Pauses for a duration based on the distance
- Stops the tone on the buzzer

### `display_fnc(String display_string)`

- Sets the cursor position on the LCD to the first row and first column
- Clears the LCD display
- Toggles the backlight of the LCD
- Prints the provided string on the LCD

### `printByte_fnc(byte character[])`

- Displays a custom byte character on the 8x8 dot matrix module by setting the rows

## How to Use

1. Connect the components to the Arduino board as specified in the pin configuration section and provided project diagram/schematic.
2. Upload the code to the Arduino board.
3. (Optional) Open the serial monitor to view the distance measurements.
4. Observe the actions and feedback on the LCD, dot matrix, buzzer, and servo motor based on the measured distance.

**Note:** Make sure to install the required libraries before uploading the code. **Required libraries are also provided.**

Feel free to modify and adapt the code according to your specific requirements.
