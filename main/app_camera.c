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
#include "esp_system.h"
#include "esp_camera.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "app_settings.h"
#include "app_camera.h"

static const char *TAG = "Camera";

/*oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
void app_camera_reset_defaults() {
  sensor_t *s = esp_camera_sensor_get();
  if (s != NULL) {
    s->set_framesize(s,FRAMESIZE_CIF);
    s->set_quality(s,14);
    s->set_brightness(s,0);
    s->set_contrast(s,0);
    s->set_saturation(s,0);
    s->set_sharpness(s,0);
    s->set_denoise(s,1);
    s->set_special_effect(s,0);
    s->set_wb_mode(s,0);
    s->set_whitebal(s,1);
    s->set_awb_gain(s,1);
    s->set_exposure_ctrl(s,1);
    s->set_aec2(s,1);
    s->set_ae_level(s,1);
    s->set_aec_value(s,600);
    s->set_gain_ctrl(s,1);
    s->set_agc_gain(s,15);
    s->set_gainceiling(s,GAINCEILING_16X);
    s->set_bpc(s,1);
    s->set_wpc(s,1);
    s->set_raw_gma(s,0);
    s->set_lenc(s,1);
    s->set_hmirror(s,0);
    s->set_vflip(s,0);
    s->set_dcw(s,0);
    s->set_colorbar(s,0);
  }
}

/*oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
void app_camera_startup() {
  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size   = FRAMESIZE_SVGA;
  config.jpeg_quality = 16;
  config.fb_count     = 2;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
      ESP_LOGE(TAG, "§>Camera init failed with error 0x%x<§", err);
      return;
  }

  app_camera_reset_defaults();
  esp_camera_load_from_nvs("camera");
}

/*oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
void app_camera_shutdown() {
  esp_camera_deinit();
  ESP_LOGI(TAG,"Camera deinitialized");
}
