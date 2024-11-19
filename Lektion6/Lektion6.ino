  #include "U8glib.h"

  U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

int x = 0;
int y = 0;
int xSpeed = 4;
int ySpeed = 3;
int textWidth;
String text = "Bajs";

void setup() {
  textWidth = text.length() * 8;
  x = random(0, 128 - textWidth);
  y = random(0, 64 - 16);
  if (u8g.getMode() == U8G_MODE_R3G3B2) {
    u8g.setColorIndex(255);
  }
  else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
    u8g.setColorIndex(3);
  }
  else if (u8g.getMode() == U8G_MODE_BW) {
    u8g.setColorIndex(1);
  }
  else if (u8g.getMode() == U8G_MODE_HICOLOR) {
    u8g.setHiColorByRGB(0, 255, 5);
  }
}

void loop(void) {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(x, y + 16, text.c_str());
  } while (u8g.nextPage());

  x += xSpeed;
  y += ySpeed;

  if (x <= 0 || x + textWidth >= 128) {
    xSpeed = -xSpeed;
    x = constrain(x, 0, 128 - textWidth);
  }

  if (y <= 0 || y + 16 >= 64) {
    ySpeed = -ySpeed;
    y = constrain(y, 0, 64 - 16);
  }
  delay(1);


}




for(int i, i <= 10, i++;)
