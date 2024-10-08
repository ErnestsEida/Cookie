#pragma once

#include <functional>
#include <thread>
#include <chrono>

using namespace std;

namespace Utils
{
  /*
    Should be used with care as this thread gets detached
    If no safe execution of passed function is done
    can result in problematic resource allocation and freeing
  */
  void timeoutCallback(uint timeoutMilliseconds, function<void(void)> callback)
  {
    thread callbackThread(
        [timeoutMilliseconds, callback]
        {
          this_thread::sleep_for(chrono::milliseconds(timeoutMilliseconds));
          callback();
        });

    callbackThread.detach();
  }

  float constrainFloat(float min, float max, float value)
  {
    if (value < min)
      return min;
    else if (value > max)
      return max;
    else
      return value;
  }

  int constrainInt(int min, int max, int value)
  {
    if (value < min)
      return min;
    else if (value > max)
      return max;
    else
      return value;
  }
}