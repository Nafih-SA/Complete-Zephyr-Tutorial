/*
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/i2c.h>
#include <stdio.h>
#include "bma_sensor.h"
#include "max30102.h"
#include "latchSensor.h"
#include "max30208.h"
#include "lightSensor.h"
#include "digitalPins.h"
#include "lcd.h"

/**
 * @file Enverse Smart Wearable Firmware
 */

// LCD values //
bool lcd_init = 0;
#define DISPLAY_MODE_BOOTING 0
#define DISPLAY_MODE_TIME 1
#define DISPLAY_MODE_OFF 2
#define DISPLAY_MODE_ON 3
#define DISPLAY_MODE_VALUES 4
int display_mode = DISPLAY_MODE_BOOTING;

#define SENSOR_MODE_IDLE 0
#define SENSOR_MODE_READ_ALL 1
int sensor_mode = SENSOR_MODE_IDLE;

/// Variable to store data ///
float temp_data = 0, light_data = 0;
u32_t red, ir;
int steps = 0;
int heart_rate, sp02;
bool valid_hr, valid_sp02;

//////////////////////////////
bool latch_status = true;

/// FSM variables  ///
int current_state_display = DISPLAY_MODE_BOOTING;

#define MAXIMUM_BRIGHTNESS 255
#define MINIMUM_BRIGHTNESS 50
int brightness_value = MAXIMUM_BRIGHTNESS;
int current_brightness = MAXIMUM_BRIGHTNESS;
int brightness_step = 15;
int logo_colour[] = {RED, BLUE, GREEN, WHITE};

#define LIGHT_BUFFER_COUNT 20

extern bool temperature_logo[50][50];
extern bool steps_logo[50][50];
extern bool heart_logo[50][50];
extern bool spio2_logo[50][50];

void main(void)
{
	printk("\n\n Booting Enverse Smart Watch \n\n");
	while (display_mode == DISPLAY_MODE_BOOTING)
	{
		k_msleep(1000);
	}
	while (1)
	{
		//display_mode = DISPLAY_MODE_TIME;
		//sensor_mode = SENSOR_MODE_IDLE;
		k_msleep(5000);
		sensor_mode = SENSOR_MODE_READ_ALL;
		display_mode = DISPLAY_MODE_VALUES;
		k_msleep(10000);
	}
}

void refresh_display()
{
	resetDisplay();
	k_msleep(1);
	LCD_Init();
	SetBrightness(current_brightness);
}
void display_task(void)
{
	LCD_Init();
	SetBrightness(255);
	while (1)
	{
		if (brightness_value > MAXIMUM_BRIGHTNESS)
			brightness_value = MAXIMUM_BRIGHTNESS;
		if (brightness_value < MINIMUM_BRIGHTNESS)
			brightness_value = MINIMUM_BRIGHTNESS;
		if (current_brightness < brightness_value)
			current_brightness += brightness_step;
		else if (current_brightness > brightness_value)
			current_brightness -= brightness_step;
		if (current_brightness > MAXIMUM_BRIGHTNESS)
			current_brightness = MAXIMUM_BRIGHTNESS;
		if (current_brightness < MINIMUM_BRIGHTNESS)
			current_brightness = MINIMUM_BRIGHTNESS;
		SetBrightness(current_brightness);
		//printf("brightness %d\n",current_brightness);
		switch (display_mode)
		{
		case DISPLAY_MODE_BOOTING:
			DispStr("BOOTING", 150, 150, WHITE, BLACK);
                        static int i = 0;
			DispLogo(logo_colour[i]);
			if (i >= (sizeof(logo_colour) / sizeof(int)))
				i = 0;
			else
				i++;
			current_state_display = DISPLAY_MODE_BOOTING;
			break;
		case DISPLAY_MODE_TIME:
			if (current_state_display != DISPLAY_MODE_TIME)
				refresh_display();
			DispStr("10 : 10", 150, 150, WHITE, BLACK);
			DispStr("11/11  Wed", 130, 200, WHITE, BLACK);
			current_state_display = DISPLAY_MODE_TIME;
			break;
		case DISPLAY_MODE_VALUES:
			if (current_state_display != DISPLAY_MODE_VALUES)
			{
				refresh_display();
				DispIcon(steps_logo, BLUE, 100, 100, 50, 50);
				DispStr("Steps", 90, 160, WHITE, BLACK);

				DispIcon(heart_logo, RED, 260, 100, 50, 50);
				DispStr("H R", 264, 160, WHITE, BLACK);

				DispIcon(temperature_logo, GREEN, 100, 280, 50, 50);
				DispStr("Temp", 94, 340, WHITE, BLACK);

				DispIcon(spio2_logo, RED, 260, 280, 50, 50);
				DispStr("Spo2", 250, 340, WHITE, BLACK);
			}

			char step_count[6];
			sprintf(step_count, "%d", steps);
			DispStr(step_count, 120, 190, WHITE, BLACK); //update step count

			if (valid_hr)
			{
				char hr[6];
				sprintf(hr, "%d  ", heart_rate);
				DispStr(hr, 270, 190, WHITE, BLACK); //update hr
			}

			char temperature_value[6];
			sprintf(temperature_value, "%.2f", temp_data);
			DispStr(temperature_value, 90, 370, WHITE, BLACK); //update temperature

			if (valid_sp02)
			{
				char sp[6];
				sprintf(sp, "%d  ", sp02);
				DispStr(sp, 260, 370, WHITE, BLACK); //update spo2
			}
			current_state_display = DISPLAY_MODE_VALUES;
			break;
		}
	}
}

void sensors_read_task(void)
{
	initialize_bma();
	stepCounterEnable();
	init_max30102();
	set_max30102_for_reading_data();
	first_data_read();
	init_max30208();
	configure_max30208();
	display_mode = DISPLAY_MODE_TIME;
	while (1)
	{
		switch (sensor_mode)
		{
		case SENSOR_MODE_IDLE:
			k_msleep(500);
			break;
		case SENSOR_MODE_READ_ALL:
			read_heart_rate_spio2(&heart_rate, &sp02, &valid_hr, &valid_sp02);
			max30208_read_temp(&temp_data);
			steps = getStepCounterOutput();
			printf("Steps= %d. Temperature = %.2f . Heart Rate = %d . SpO2 = %d \n", steps, temp_data, heart_rate, sp02);
			k_msleep(10);
			break;
		}
	}
}

void latch_sensor_task(void)
{
	init_latch();
	init_output();
	while (1)
	{
		latch_status = detect_latch();
		k_msleep(500);
	}
}

void vibration_task()
{
	while (1)
	{
		if (latch_status == false)
			toggle_motor(1);
		else
			toggle_motor(0);
		k_msleep(500);
	}
}

void buzzer_task()
{
	while (1)
	{
		if (latch_status == false)
			toggle_buzzer(1);
		k_msleep(500);
	}
}

void brightness_task()
{
	float light_data[LIGHT_BUFFER_COUNT];
	for (int i = 0; i < LIGHT_BUFFER_COUNT; i++)
		light_data[i] = AnalogRead(4);
	while (1)
	{
		float sum = 0;
		for (int i = 0; i < LIGHT_BUFFER_COUNT - 1; i++)
		{
			light_data[i] = light_data[i + 1];
			sum = sum + light_data[i];
		}
		light_data[LIGHT_BUFFER_COUNT - 1] = AnalogRead(4);
		sum = sum + light_data[LIGHT_BUFFER_COUNT - 1];
		float light_value = sum / LIGHT_BUFFER_COUNT;
		//printf("light =%f\n",light_value);
		brightness_value = 75.55 * light_value;
		k_msleep(100);
	}
}

K_THREAD_DEFINE(sensors_read_task_id, 512, sensors_read_task, NULL, NULL, NULL,
				0, 0, 10);
K_THREAD_DEFINE(latch_sensor_task_id, 300, latch_sensor_task, NULL, NULL, NULL,
				0, 0, 100);
K_THREAD_DEFINE(buzzer_task_id, 200, buzzer_task, NULL, NULL, NULL,
				0, 0, 100);
K_THREAD_DEFINE(vibration_task_id, 200, vibration_task, NULL, NULL, NULL,
				0, 0, 100);
K_THREAD_DEFINE(display_task_id, 512, display_task, NULL, NULL, NULL,
				0, 0, 1000);
K_THREAD_DEFINE(brightness_task_id, 400, brightness_task, NULL, NULL, NULL,
				0, 0, 2000);
