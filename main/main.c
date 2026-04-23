#include <stdio.h>
#include "driver/gpio.h"
#include "esp_attr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#define MOTION_SENSOR_PIN 13

static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR isr_handler(void* arg) {
    uint32_t pin_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &pin_num, NULL);
}

void app_main(void) {
    // config
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_ANYEDGE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << MOTION_SENSOR_PIN),
        .pull_down_en = 1,
        .pull_up_en = 0
    };

    gpio_config(&io_conf);
    gpio_install_isr_service(0); // installs gpio interrupt driver

    printf("Wait 30s for sensor to not bug out \n");
    vTaskDelay(pdMS_TO_TICKS(30000));

    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    gpio_isr_handler_add(MOTION_SENSOR_PIN, isr_handler, (void*) MOTION_SENSOR_PIN); // hooks pin to specific isr function

    printf("Waiting for Motion \n");

    uint32_t received_pin;
    while(1) {
        if (xQueueReceive(gpio_evt_queue, &received_pin, portMAX_DELAY)) {
            if (gpio_get_level(received_pin) == 1) {
                printf("Motion detected, interrupt on pin %lu \n", received_pin);
            } else {
                printf("Reset \n");
            }
        }
    }
}
