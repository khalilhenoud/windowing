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

window_data_t
create_window(const char *classname, const char *title)
{
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
    CW_USEDEFAULT, CW_USEDEFAULT, 
    CW_USEDEFAULT, CW_USEDEFAULT, 
    0, 0, GetModuleHandle(NULL), 0);

	ShowWindow((HANDLE)data.handle, SW_NORMAL);
	UpdateWindow((HANDLE)data.handle);

  data.device_context = (uint64_t)GetDC((HWND)data.handle);
  
  return data;
}

uint64_t
handle_message_loop_blocking(void)
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
	}

End:
	return (uint64_t)msg.wParam;
}

void
destroy_window(window_data_t *data)
{
  ReleaseDC((HWND)data->handle, (HDC)data->device_context);
}