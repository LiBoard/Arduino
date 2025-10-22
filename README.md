# LiBoard - Arduino library
This Arduino library provides the code running on the board's microcontroller.

## Installation
Clone this repo into `YOUR_ARDUINO_FOLDER/libraries/`.

## Usage
If you're just interested in using the board with a script or the app, you'll want
to run the `serial_binboard` sketch from the library's examples folder.

## Thresholds
Each photoresistor requires a threshold value which triggers when each square is occupied or not. There are two options you can use to set the threshold values for each square.

### Setting Threshold Mode
By default, Liboard is configured to use the Global threshold mode. If you want to change it Per-Square thresholds, then edit the following variable:

``` C
// !!! choose mode: 1 = global single value, 0 = per-square array !!!
#define USE_GLOBAL_THRESHOLD 1
```

### Option 1 - Global Threshold
Global Threshold mode applies the same threshold value to every photoresistor. If you need to change the sensitivity of the photoresistors, change the value of this variable:
```C
// Option 1 - Global Threshold (Applies to all photoresistors)
unsigned short THRESHOLD = 100;
```

### Option 2 - Per-square Thresholds
You can also set individual thresholds for each photoresisor. This is useful if not all your photoresistors are the same type. Per-square thresholds also has more accuracy. You can adjust each square threshold individually by editing each number.
```C
// Option 2 - Per-square threshold (Applies to each individual photoresistor)
unsigned short THRESHOLD[64] = {
  // A1..H1
  150, 150, 150, 150, 150, 150, 150, 150,
  // A2..H2
  150, 150, 150, 150, 150, 150, 150, 150,
  // A3..H3
  100, 100, 100, 100, 100, 100, 100, 100,
  // A4..H4
  100, 100, 100, 100, 100, 100, 100, 100,
  // A5..H5
  600, 600, 600, 600, 600, 600, 600, 600,
  // A6..H6
  600, 600, 600, 600, 600, 600, 600, 600,
  // A7..H7
  300, 300, 300, 300, 300, 300, 300, 300,
  // A8..H8
  300, 300, 300, 300, 300, 300, 300, 300
};
```
