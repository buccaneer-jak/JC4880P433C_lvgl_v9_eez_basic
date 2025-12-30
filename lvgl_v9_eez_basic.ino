// WORKS WITH ESP32 BOARD V3.1.2 and v3.1.1

#include <Arduino.h>
#include "lvgl.h"
#include "pins_config.h"
#include "lvgl_port_v9.h"

#include "src/ui.h"

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32P4 MIPI DSI LVGL - Minimal Setup");
  
  // Initialize LVGL and display
  lvgl_init();
  
  // Create UI elements
  //create_ui();
  if(lvgl_port_lock(-1)) {
    ui_init();
    lvgl_port_unlock();
  }
}
// ########################################################
void loop()
{
	  // Example: Update UI every 100msecs
  static uint32_t last_update = 0;
  if (millis() - last_update > 10000) {
    last_update = millis();

    // DON't call lv_timer_handler() here!
    // The lvgl_port already runs it in a dedicated FreeRTOS task.
    // lvgl_port_v9.c already creates a dedicated FreeRTOS task (lvgl_port_task)
    // that continuously calls lv_timer_handler().
    // Calling it here can interfere with touch handling and cause conflicts.
    //
    // Handle LVGL timer and screen updates
    if(lvgl_port_lock(-1))
    {
      // lv_timer_handler();	// DON't call lv_timer_handler() here!
      // Update your UI here
      // lv_label_set_text(my_label, "Updated!");
      lvgl_port_unlock();
    }
  }
	delay(5); // Small delay to prevent watchdog issues
}
// ########################################################
// Function to create the UI elements
void create_ui()
{
  if(lvgl_port_lock(-1))
  {
    // Create a text area widget
    lv_obj_t * textarea = lv_textarea_create(lv_screen_active());
    
    // Set size (width, height)
    lv_obj_set_size(textarea, 300, 100);
    
    // Center the text area on the screen
    lv_obj_center(textarea);
    
    // Set some initial text
    lv_textarea_set_text(textarea, "Hello LVGL!");
    
    // Optional: Set text alignment to center
    lv_textarea_set_align(textarea, LV_TEXT_ALIGN_CENTER);
    
    // Optional: Make it single line if you want
    // lv_textarea_set_one_line(textarea, true);
    
    lvgl_port_unlock();
  }
}