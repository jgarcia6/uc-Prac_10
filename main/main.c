#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include “myTimer.h”
#include “myUart.h”

// UART 0
#define PC_UART_PORT    (0)
#define PC_UART_RX_PIN  (3)
#define PC_UART_TX_PIN  (1)

void ADC1_Ch0_Ini(void);
uint16_t ADC1_Ch0_Read(void);
uint16_t ADC1_Ch0_Read_mV(void);

//#define ADC_CALIB_ENABLE
#ifdef ADC_CALIB_ENABLE
#include "esp_adc_cal.h"
static esp_adc_cal_characteristics_t adc1_chars;
bool cali_enable = false;
#endif

void ADC1_Ch0_Ini(void)
{
#ifdef ADC_CALIB_ENABLE
    esp_err_t ret;
    ret = esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF);
    if (ret == ESP_ERR_NOT_SUPPORTED) {
        printf("Calibration scheme not supported, skip software calibration\n");
    } else if (ret == ESP_ERR_INVALID_VERSION) {
        printf("eFuse not burnt, skip software calibration\n");
    } else if (ret == ESP_OK) {
        cali_enable = true;
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    } else {
        printf("Invalid arg\n");
    }
#endif
    //ADC1 config
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
}

uint16_t ADC1_Ch0_Read(void)
{
    return adc1_get_raw(ADC1_CHANNEL_0);
}

uint16_t ADC1_Ch0_Read_mV(void)
{
    // TODO
    //Make the appropiate convertion of the RAW ADC value to mV by calling ADC1_Ch0_Read()
    // No calibration needed
    return 0;
}

int app_main()
{
    uint16_t adc_raw;
    char str[20];
    // TODO: Board Init (GPIO, UART, Timers)
    ADC1_Ch0_Ini();

    while (1) {
        adc_raw = ADC1_Ch0_Read();
        uartPuts(PC_UART_PORT,"raw  data: ");
        myItoa(adc_raw, str, 10);
        uartPuts(PC_UART_PORT, str)
        uartPutchar(PC_UART_PORT, '\n');
#ifdef ADC_CALIB_ENABLE
        if (cali_enable) {
            uint32_t voltage = 0;
            voltage = esp_adc_cal_raw_to_voltage(adc_raw, &adc1_chars);
            printf("cali data: %d mV\n", voltage);
        }
#endif
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    return 0; 
}
