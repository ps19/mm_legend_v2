/*
 * file:	pid.c
 * author:	GAndaLF
 * brief:   PID controller.
 */

#include "platform_specific.h"
#include <math.h>

#include "pid.h"

/** Maximum influence of integral part on output signal in percent. */
#define MAX_I_PART      200

/**
 * Check anti windup of integral part.
 *
 * @param pid               PID controller object.
 */
static void anti_windup(pid_params_t pid);

int32_t pid_init(pid_params_t pid, float p, float i, float d)
{
    if (NULL == pid)
    {
        return -EINVAL;
    }

    pid->err_sum = 0;
    pid->err_last = 0;

    pid->p = p;
    pid->i = i;
    pid->d = d;

    return 0;
}

float pid_iter(pid_params_t pid, float setval, float output)
{
    float e;
    float de;
    float u;

    if (NULL == pid)
    {
        return -EINVAL;
    }

    e = setval - output;
    de = e - pid->err_last;
    pid->err_sum += e;

    anti_windup(pid);

    u = pid->p * e + pid->i * pid->err_sum + pid->d * de;
    pid->err_last = e;

    return u;
}

static void anti_windup(pid_params_t pid)
{
    float abs_i;

    abs_i = fabs(pid->i);

    /* Run anti windup only if I is not 0. */
    if (abs_i > 10e-5)
    {
        if (MAX_I_PART / abs_i < pid->err_sum)
        {
            pid->err_sum = MAX_I_PART / abs_i;
        }

        if (-MAX_I_PART  / abs_i > pid->err_sum)
        {
            pid->err_sum = -MAX_I_PART  / abs_i;
        }
    }
}
