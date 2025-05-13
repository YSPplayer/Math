/*
    Created by YSP on 2025-05-14.
*/
#pragma once
namespace ysp {
    class Util {
    public:
		template<typename T>
		static void ReleasePointer(T*& point, bool isArray = false) {
			if (point == nullptr) return;
			isArray ? delete[] point : delete point;
			point = nullptr;
		}

		template<typename T>
		static void ReleasePointer(void*& point, bool isArray = false) {
			if (point == nullptr) return;
			T* rpoint = static_cast<T*>(point);
			isArray ? delete[] rpoint : delete rpoint;
			point = nullptr;
		}
		static void ReleasePointer(void**& point, unsigned int size) {
			if (point == nullptr) return;
			for (unsigned int i = 0; i < size; ++i) ReleasePointer(point[i]);
			ReleasePointer(point, true);
		}
    }
}