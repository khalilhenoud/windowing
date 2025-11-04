/**
 * @file windowing.h
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2025-11-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef WINDOWING_HEADER_H
#define WINDOWING_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <windowing/internal/module.h>


typedef
struct window_data_t {
  uint64_t handle;
  uint64_t device_context;
} window_data_t;

WINDOWING_API
window_data_t
create_window(const char *classname, const char *title);

WINDOWING_API
uint64_t
handle_message_loop_blocking(void);

WINDOWING_API
void
destroy_window(window_data_t *data);

#ifdef __cplusplus
}
#endif

#endif