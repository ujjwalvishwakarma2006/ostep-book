#ifndef __common_h__
#define __common_h__

#include <sys/time.h>   // For gettimeofday(), which gets the current time with microsecond precision
#include <sys/stat.h>   // Not used in this file (can be removed)
#include <assert.h>     // For assert(), used to check that gettimeofday() succeeded

// Returns the current time in seconds (with microsecond precision) as a double
double GetTime() {
    struct timeval t;                      // timeval struct holds seconds and microseconds
    int rc = gettimeofday(&t, NULL);      // gettimeofday fills 't' with current time
    assert(rc == 0);                      // Make sure gettimeofday succeeded (returns 0)
    // Convert seconds and microseconds to a single floating-point seconds value
    return (double) t.tv_sec + (double) t.tv_usec / 1e6;
}

// Spin function: busy-waits for approximately 'howlong' seconds
void Spin(int howlong) {
    double t = GetTime();  // Record start time
    // Keep looping until the elapsed time >= howlong seconds
    while ((GetTime() - t) < (double) howlong);
}

#endif

