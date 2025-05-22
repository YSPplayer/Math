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
		static double NextPowerOfTen(double num) {
			if (num == 0) return 0;
			bool isNegative = num < 0;
			num = std::abs(num);
			// 计算当前数字的10的幂次
			int exponent = static_cast<int>(std::floor(std::log10(num)));
			double currentPower = std::pow(10, exponent);
			// 检查当前数字是否已经是10的幂次
			if (std::abs(num - currentPower) < 1e-10) {
				return isNegative ? -currentPower : currentPower;
			}
			// 否则返回下一个10的幂次
			double nextPower = std::pow(10, exponent + 1);
			return isNegative ? -nextPower : nextPower;
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

		template<typename... Args>
		static void** Packing(Args&&... args) {
			int size = sizeof...(args);
			//这里初始化了argsArray的内存
			void** argsArray = new void* [size];
			int index = 0;
			Pack(argsArray, index, std::forward<Args>(args)...);
			return argsArray;
		}
	private:
		static void Pack(void** arr, int& index) {
			// 无操作，用于终止递归
		}

		template<typename T, typename... Args>
		static void Pack(void** arr, int& index, T&& first, Args&&... rest) {
			arr[index++] = static_cast<void*>(first);//存储指针本身
			Pack(arr, index, std::forward<Args>(rest)...);
		}
	};
}