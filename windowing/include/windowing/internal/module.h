#if !defined(WINDOWING_API)
	#define WINDOWING_API /* NOTHING */

	#if defined(WIN32) || defined(WIN64)
		#undef WINDOWING_API
		#if defined(windowing_EXPORTS)
			#define WINDOWING_API __declspec(dllexport)
		#else
			#define WINDOWING_API __declspec(dllimport)
		#endif
	#endif // defined(WIN32) || defined(WIN64)

#endif // !defined(WINDOWING_API)

