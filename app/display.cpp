#include "display.h"

void display_clear(void) {
    // Clear the display
    lcd.cls();
}

void display_draw_hline(int y, int x_start, int x_end) {
    // Draw a horizontal line from x_start to x_end at position y
    
    if (x_start > x_end) {
        return; // Invalid line
    }

    if (x_end >= lcd.width()) {
        x_end = lcd.width() - 1; // Clamp to display width
    }

    for (int x = x_start; x <= x_end; ++x)
    {
        lcd.pixel(x, y, 1);
    }
}

void display_draw_vline(int x, int y_start, int y_end) {
    // Draw a vertical line from y_start to y_end at position x
    
    if (y_start > y_end) {
        return; // Invalid line
    }

    if (y_end >= lcd.height()) {
        y_end = lcd.height() - 1; // Clamp to display height
    }

    for (int y = y_start; y <= y_end; ++y)
    {
        lcd.pixel(x, y, 1);
    }
}

// Print the time in hh:mm:ss format at the top left
void display_print_time(int hour, int min, int sec)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hour, min, sec);
    lcd.locate(0, 0);
    lcd.printf("%s", buf);
}

// Print the alarm status (A: C T) in the middle left
void display_print_alarm_status(bool alarm_clock_enabled, bool temp_alarm_enabled)
{
    lcd.locate(0, 10); // Adjust Y as needed for your font/spacing
    lcd.printf("A: %c %c", alarm_clock_enabled ? 'C' : ' ', temp_alarm_enabled ? 'T' : ' ');
}

// Print the temperature in tt.t format at the bottom left
void display_print_temperature(float temp)
{
    lcd.locate(0, 20); // Adjust Y as needed for your font/spacing
    lcd.printf("T(C)= %.1f", temp);
}

// Print the bubble level value at the right
void display_print_bubble_level(int value_x, int value_y)
{   
    // based on value calculate position of bubble
    // needs to be tested and adjusted
    lcd.locate(100, 10);
    lcd.circle(100, 16, 2, 1); //center mark
    lcd.circle(100+value_x, 16+value_y, 5, 1);
}

void display_init(void) {
    // Initialize the C12832 LCD display
    display_clear();
    lcd.locate(0, 0);
    lcd.printf("Display Initialized");
}

// Print the full status screen
void display_print_screen(int hour, int min, int sec, bool alarm_clock_enabled, bool temp_alarm_enabled, float temp, int bubble_level_x,int bubble_level_y)
{
    display_clear();
    display_print_time(hour, min, sec);
    display_print_alarm_status(alarm_clock_enabled, temp_alarm_enabled);
    display_print_temperature(temp);
    display_print_bubble_level(bubble_level_x,bubble_level_y);
    display_draw_vline(96, 0, lcd.height());
}

void displayRGB(float t){
    if (t > thigh){ /*hot, make it red*/
        r = 0.0; g = 1.0; b = 1.0;
    }
    else if (t < tlow){ /*cold, make it blue*/
        r = 1.0; g = 1.0; b = 0.0;
    }
    else{
        r = 1.0 - ( (t-tlow)/(thigh-tlow) );
        g = 1.0;
        b = (t-tlow)/(thigh-tlow);
    }

}
