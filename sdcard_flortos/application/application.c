/*
 * application.c
 *
 *  Created on: Apr 18, 2022
 *      Author: ftobler
 */

#include "application.h"
#include "scheduler.h"
#include "gpio_low_level.h"
#include "stm32f0xx_hal.h"
#include "ff.h"


static void taskFn0();
static void taskFn1();
static void taskFn2();
static uint8_t stack0[128];
static uint8_t stack1[400];
static uint8_t stack2[128];

static FATFS FatFs;		/* FatFs work area needed for each volume */
static FIL Fil;			/* File object needed for each open file */

volatile static uint32_t speed = 200;


void app_init() {
//	taskFn1();
	//idle task is the first task
	scheduler_addTask(0, taskFn0, stack0, 128);
	scheduler_addTask(1, taskFn1, stack1, 400);
	scheduler_addTask(2, taskFn2, stack2, 128);
	//highest priority task is the last task
}


static void taskFn0() {
	while (1) {
		__WFI();
	}
}

static void taskFn1() {
	UINT bw;
	volatile FRESULT fr;


	f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */

	fr = f_open(&Fil, "newfile3.txt", FA_WRITE | FA_CREATE_ALWAYS);	/* Create a file */
	if (fr == FR_OK) {
		f_write(&Fil, "It works :)!\r\n", 11, &bw);	/* Write data to the file */
		fr = f_close(&Fil);							/* Close the file */
		if (fr == FR_OK && bw == 11) {		/* Lights green LED if data written well */
			speed = 25;
		}
	}
	while (1) {
		scheduler_task_sleep(1);
	}
}
static void taskFn2() {
	while (1) {
		scheduler_task_sleep(speed);
		gpio_ll_set(GPIOA, GPIO_PIN_4);
		scheduler_task_sleep(speed);
		gpio_ll_reset(GPIOA, GPIO_PIN_4);
	}
}
