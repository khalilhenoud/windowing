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
  uintptr_t handle;
  uintptr_t device_context;
} window_data_t;

typedef
struct win_rect_t {
  int64_t left;
  int64_t right;
  int64_t top;
  int64_t bottom;
} win_rect_t;

typedef
struct win_point_t {
  int64_t x;
  int64_t y;
} win_point_t;

typedef void(*update_func_t)(void);

WINDOWING_API
window_data_t
create_window(
  const char *win_class,
  const char *title,
  int32_t width, int32_t height);

WINDOWING_API
uint64_t
handle_message_loop_blocking(update_func_t func);

WINDOWING_API
void
destroy_window(window_data_t *data);

WINDOWING_API
int32_t
get_window_rect(uintptr_t window_handle, win_rect_t *rect);

WINDOWING_API
int32_t
screen_to_client(uintptr_t window_handle, win_point_t *point);

WINDOWING_API
int32_t
client_to_screen(uintptr_t window_handle, win_point_t *point);

#ifdef __cplusplus
}
#endif

#endif