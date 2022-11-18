/* Test NTC library */
#include "../NTC_common.h"
#include "../models/Vishay10K.hpp"

#define NUM_OF_TESTS     50
#define TEST_SUCCESSFUL  1
#define TEST_FAILED      0

#ifdef TEST_ON_HOST_PC
#if defined(__linux)
#define HAVE_POSIX_TIMER
#include <time.h>
#ifdef CLOCK_MONOTONIC
#define CLOCKID CLOCK_MONOTONIC
#else
#define CLOCKID CLOCK_REALTIME
#endif /* monotonic clock */
#endif /* linux */

#include <unistd.h> // Sleep
#include <stdio.h>

/* Get current ns */
uint64_t now_ns() 
{
    static uint64_t is_init = 0;
#if defined(__linux)
    static struct timespec linux_rate;
    if (0 == is_init) {
        clock_getres(CLOCKID, &linux_rate);
        is_init = 1;
    }
    uint64_t now;
    struct timespec spec;
    clock_gettime(CLOCKID, &spec);
    now = spec.tv_sec * 1.0e9 + spec.tv_nsec;
    return now;
#endif
}

/* Wait next us */
uint64_t wait_next(uint64_t interval) 
{
  static uint64_t last_call = 0;
  uint64_t delta, delay;
  if (last_call == 0 || interval == 0) last_call = now_ns();
  while ((delta = now_ns() - last_call)) {
    if (delta >= interval) {
      delay = delta - interval;
      last_call = now_ns() - delay;
      return delay;
    }
  }
  return 0;
}
#endif /* TEST_ON_HOST_PC */

#include <stdint.h>

int main()
{
#ifdef TEST_ON_HOST_PC
    double t0 = 0, t = 0, dt = 0;
    struct timespec ts;
    int rc, i = 0;

    // Initialize the clock
    clock_gettime(CLOCK_MONOTONIC, &ts);
    t0 = ts.tv_sec + ts.tv_nsec / 1.0E9;
#endif /* TEST_ON_HOST_PC */

    /* Instantiate sensor */
    Vishay10K sens1 = Vishay10K();

    /* Test before main loop */
    uint32_t adc_value = 10000; /* 10K */
    int16_t value = sens1.GetTemperature(adc_value);

    /* Single check */
    if(value == 0) return TEST_FAILED;

    // CSV header
#ifdef TEST_ON_HOST_PC
    fprintf(stdout, "Init test\n");
    fprintf(stdout, "n, dt\n");
#endif /* TEST_ON_HOST_PC */

    /* Main loop */
    for (int i=0; i<NUM_OF_TESTS; i++)
    {
#ifdef TEST_ON_HOST_PC
        // Get time
        clock_gettime(CLOCK_MONOTONIC, &ts);
        t = ts.tv_sec + ts.tv_nsec / 1.0E9;
        dt = t - t0;
        t0 = t;

        int16_t value = sens1.GetTemperature(adc_value);
        if(value == 0) return TEST_FAILED;

        fprintf(stdout, "%d, %f\n", i, dt);
        
        wait_next(5e6);
#endif /* TEST_ON_HOST_PC */
    }


    return TEST_SUCCESSFUL;
}