#include <ProTrinketMouse.h>

int startX = -10; // maths units
int startY = 10; // maths units
int i = startX; // maths units
int height = 20; // maths units
int width = 20; // maths units
int currentX = 0; // screen units
int currentY = 0; // screen units
float scaleFactor = 10.0;

void setup() {
  TrinketMouse.begin();
}

void loop() {
  if (i == startX) {
    int halfHeight = height / 2;
    int halfWidth = width / 2;
    drawNext(0, halfHeight);
    drawNext(0, halfHeight * -1);
    upCursor();
    drawNext(halfWidth * -1, 0);
    drawNext(halfWidth, 0);
    upCursor();
  }

  if (i <= (width - startX)) {
    drawNext(i*2, 10);
    drawNext(i*2, -10);
    upCursor();
    i++;
  } else {
    i = startX;
    resetCursor();
    delay(5000);
  }
  delay(50);
}

float compute(int x) {
  //return x;
  return pow(x,2);
}

void resetCursor() {
  TrinketMouse.move(0, 0, 0, 0); // reset button presses
  TrinketMouse.move((-1 * currentX), (-1 * currentY), 0, 0);
  currentX = 0;
  currentY = 0;
}

boolean checkValid(float x, float y) {
  int tempX = round(x) - startX;
  boolean testX = (tempX >= 0) && (tempX <= height);
  int tempY = round(y) + startY;
  boolean testY = (tempY >= 0) && (tempY <= height);
  return testX && testY;
}

void scaleCoords(float x, float y, int &resX, int &resY) {
  resX = round((x + startX) * scaleFactor);
  resY = round((y - startY) * scaleFactor * -1);
}

void deltaCoords(float x, float y, int &resX, int &resY) {
  resX = x - currentX;
  resY = y - currentY;
}

void calcCoords(float x, float y, int &resX, int &resY) {
  scaleCoords(x, y, resX, resY);
  deltaCoords(resX, resY, resX, resY);
  currentX = currentX + resX;
  currentY = currentY + resY;
}

void drawNext(float x, float y) {
  if (checkValid(x, y)) {
    int normX;
    int normY;
    calcCoords(x, y, normX, normY);
    TrinketMouse.move(normX, normY, 0, MOUSEBTN_LEFT_MASK);
  } else {
    TrinketMouse.move(0, 0, 0, 0); // don't draw, reset cursor
  }
}

void upCursor() {
  TrinketMouse.move(0, 0, 0, 0); // reset cursor
}
