/**
 * @file windowing.c
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2025-11-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <windowing/windowing.h>
#include <Windows.h>


LRESULT 
CALLBACK 
WndProc(
  HWND g_hWnd, 
  UINT message, 
  WPARAM wParam, 
  LPARAM lParam)
{
	switch (message) {
    case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(g_hWnd, message, wParam, lParam);
	}

	return 0;
}

static
void 
ComputeWindowPosition(
  int32_t *x, 
  int32_t *y, 
  int32_t width, 
  int32_t height,
  int32_t screen_width,
  int32_t screen_height)
{
  (*x) = (*y) = 0;
	if (screen_width <= width || screen_width <= height)
    return;

	*x = (screen_width - width)/2;
	*y = (screen_height - height)/2;
}

window_data_t
create_window(
  const char *classname, 
  const char *title, 
  int32_t width, 
  int32_t height)
{
  int32_t screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
  int32_t screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	RECT r = { 0, 0, width, height };
  AdjustWindowRect(&r, WS_CAPTION, FALSE);
  int32_t x, y;
	ComputeWindowPosition(
    &x, &y, 
    width, height, 
    screenWidth, screenHeight);

  WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = classname;
	wcex.hIconSm = 0;
	RegisterClassEx(&wcex);

  window_data_t data;
  data.handle = (uint64_t)CreateWindowEx(
    0,
    classname, 
    title, 
    WS_CAPTION, 
    x, y, r.right - r.left, r.bottom - r.top, 
    0, 0, GetModuleHandle(NULL), 0);

	ShowWindow((HANDLE)data.handle, SW_NORMAL);
	UpdateWindow((HANDLE)data.handle);

  data.device_context = (uint64_t)GetDC((HWND)data.handle);
  
  return data;
}

uint64_t
handle_message_loop_blocking(update_func_t func)
{
  MSG msg;
	while (1) {
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				goto End;
			else
				DispatchMessage(&msg);
		}

    if (GetAsyncKeyState(VK_ESCAPE)) {
      PostQuitMessage(0);
      continue;
    }

    func();
	}

End:
	return (uint64_t)msg.wParam;
}

void
destroy_window(window_data_t *data)
{
  ReleaseDC((HWND)data->handle, (HDC)data->device_context);
}