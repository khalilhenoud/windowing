/**
 * @file main.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdint.h>
#include <windowing/windowing.h>


int main(int argc, char *argv[])
{
  window_data_t data = create_window("test_window_setup", "test window setup");
  uint64_t result = handle_message_loop_blocking();
  destroy_window(&data);
  return result;
}