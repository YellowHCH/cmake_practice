#pragma once
#include <thread>
#include <chrono>
#include <functional>

///
/*
-std=c++11
run task period(intervals/seconds)
intervals: second
times: operate times, set to 0 when no limit 
*/

class ThreadTimer{
 public:
  ThreadTimer(std::function<void()> task, int intervals = 0, int times = 0)
    : m_task(task), m_isRunning(false), m_interval(intervals * kMillisecondPerSecond), m_iTimesCnt(-1), m_iTimesLimit(times)
		      {

		      }

  ~ThreadTimer()
    {
      Stop();
    }

  void Stop(){ m_isRunning = false; }

  void Start()
  {
    m_isRunning = true;
    std::thread _thread(Run);
    _thread.detach();
    return;
  }

  std::function<void()> Run = [this]()
    {
     if(m_interval == std::chrono::milliseconds(0)){return;}
     while(m_isRunning && m_iTimesCnt < m_iTimesLimit)
       {
	if(m_task != nullptr)
	  m_task();
	std::this_thread::sleep_for(m_interval);
	if(m_iTimesLimit > 0)
	  ++m_iTimesCnt;
       }
    };

 private:
  std::function<void()> m_task = nullptr;
  bool m_isRunning;
  std::chrono::milliseconds m_interval;
  static const int kMillisecondPerSecond = 1000;
  int m_iTimesCnt;
  int m_iTimesLimit;
};
