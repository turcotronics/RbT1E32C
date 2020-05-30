/*
 Modified ESPRESSIF MIT License
 
 Copyright (c) <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
				Bond Keevil (bkeevil), https://github.com/bkeevil/esp32-cam
				Turco Rodolfo, Turcotronics, https://turcotronics.it/ 
 
 Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 it is free of charge, to any person obtaining a copy of this software and associated
 documentation files (the "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 to do so, subject to the following conditions:

 The names of Turcotronics, Robello and TuT may not be used to endorse or promote
 products derived from this software without specific prior written permission.
 
 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "driver/ledc.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "app_illuminator.h"

#ifdef CONFIG_LED_ILLUMINATOR_ENABLED    

static const char *TAG = "Illuminator";

/*oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
void app_illuminator_startup() {
  gpio_set_direction(CONFIG_LED_LEDC_PIN,GPIO_MODE_OUTPUT);
  ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_8_BIT,            // resolution of PWM duty
    .freq_hz         = 1000,                        // frequency of PWM signal
    .speed_mode      = LEDC_LOW_SPEED_MODE,  // timer mode
    .timer_num       = CONFIG_LED_LEDC_TIMER        // timer index
  };
  ledc_channel_config_t ledc_channel = {
    .channel    = CONFIG_LED_LEDC_CHANNEL,
    .duty       = 0,
    .gpio_num   = CONFIG_LED_LEDC_PIN,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = CONFIG_LED_LEDC_TIMER
  };
  #ifdef CONFIG_LED_LEDC_HIGH_SPEED_MODE
  ledc_timer.speed_mode = ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
  #endif
  switch (ledc_timer_config(&ledc_timer)) {
    case ESP_ERR_INVALID_ARG: ESP_LOGE(TAG, "§>ledc_timer_config() parameter error<§"); break;
    case ESP_FAIL: ESP_LOGE(TAG, "§>ledc_timer_config() Can not find a proper pre-divider number base on the given frequency and the current duty_resolution<§"); break;
    case ESP_OK: if (ledc_channel_config(&ledc_channel) == ESP_ERR_INVALID_ARG) {
        ESP_LOGE(TAG, "§>ledc_channel_config() parameter error<§");
      }
      break;
    default: break;
  }
}

/*oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
void app_illuminator_shutdown() {
  ledc_stop(LEDC_LOW_SPEED_MODE,CONFIG_LED_LEDC_CHANNEL,0);
}

/*oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
void app_illuminator_set_led_intensity(uint8_t duty) {      // Turn LED On or Off
    uint8_t _duty = (duty > CONFIG_LED_MAX_INTENSITY) ? CONFIG_LED_MAX_INTENSITY : duty;
    
    ledc_set_duty(CONFIG_LED_LEDC_SPEED_MODE, CONFIG_LED_LEDC_CHANNEL, _duty);
    ledc_update_duty(CONFIG_LED_LEDC_SPEED_MODE, CONFIG_LED_LEDC_CHANNEL);
    ESP_LOGI(TAG, "Set LED intensity to %d", _duty);
}
#endif
