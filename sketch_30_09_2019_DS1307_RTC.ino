#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const char *monthName[12] = {
  "Styczen", "Luty", "Marzec", "Kwiecien", "Maj", "Czerwiec",
  "Lipiec", "Sierpien", "Wrzesien", "Pazdzie.", "Listopad", "Grudzien"
};

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.backlight();
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    lcd.setCursor (4,0);
    LCDprint2digits(tm.Hour);
    lcd.print(':');
    LCDprint2digits(tm.Minute);
    lcd.print(':');
    LCDprint2digits(tm.Second);
    lcd.setCursor (0,1);
    lcd.print(tm.Day);
    lcd.setCursor(3,1);
    lcd.print(monthName[tm.Month-1]);
    lcd.setCursor(12,1);
    lcd.print(tmYearToCalendar(tm.Year));
  }
  else {
    if (RTC.chipPresent()) {
      lcd.print("DS1307: SetTime");
    }
    else {
      lcd.print("DS1307: error");
    }
    delay(9000);
  }
  delay(1000);
}
  
void LCDprint2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);  
}
