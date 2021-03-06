/*
 * file:	logger_test_task.c
 * author:	GAndaLF
 * brief:	Task for testing data logger.
 */

#include <stdio.h>

#include "logger_test_task.h"

#include "platform_specific.h"

/* Project includes */
#include "usart/usart.h"

#define LOGGER_TEST_TASK_STACKSIZE         (configMINIMAL_STACK_SIZE * 8)
#define LOGGER_TEST_TASK_PRIORITY          (tskIDLE_PRIORITY + 2)

#define BUF_SIZE        (4 * 1024)

static uint8_t test_buf[BUF_SIZE];

static void logger_test_task(void *params);

void logger_test_task_init(void)
{
    usart_init();

    rtos_task_create(logger_test_task, "loggert",
                     LOGGER_TEST_TASK_STACKSIZE, LOGGER_TEST_TASK_PRIORITY);
}

static void logger_test_task(void *params)
{
    (void) params;

    int32_t i;

    for (i = 0; i < BUF_SIZE; i++)
    {
        test_buf[i] = i;
    }

    while (1)
    {
        printf("Wlasny printf dziala!\r\n");
        printf("Jakis dodatkowy tekst dla wypelnienia\r\n");
        printf("I jeszcze jeden\r\n");
        printf("A teraz liczby: %d, %f, %X\r\n", 5, 0.5, 0xAAAAAAAA);
        rtos_delay(5000);

        //usart_send_buf(test_buf, BUF_SIZE);
        rtos_delay(5000);

    }
}
