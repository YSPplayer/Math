/*
    Created by YSP on 2025-05-14.
*/
#pragma once
#include <Windows.h>
#include <vector>
#include <codecvt>
#include <functional>
#include <string>
#include <cmath>
namespace ysp {
    class ListFilter {
    public:
        template <typename T>
        static int Count(const std::vector<T>& list, const std::function<bool(const T&)>& filter) {
            int count = 0;
            for (const T& item : list) {
                if (filter(item)) ++count;
            }
            return count;
        }

        template <typename T>
        static bool Any(const std::vector<T>& list, const std::function<bool(const T&)>& filter) {
            for (const T& item : list) {
                if (filter(item)) return true;
            }
            return false;
        }
        
        template <typename T>
        static bool All(const std::vector<T>& list, const std::function<bool(const T&)>& filter) {
            for (const T& item : list) {
                if (!filter(item)) return false;
            }
            return true;
        }

        template <typename T>
        static std::vector<T> Where(const std::vector<T>& list, const std::function<bool(const T&)>& filter) {
            std::vector<T> result;
            for (const T& item : list) {
                if (filter(item)) result.append(item);
            }
            return result;
        }

        /// <summary>
        /// 比较函数参数一是当前最大的数，参数二是我们需要比较的数，返回true表示我们需要比较的数较大，返回false表示需要比较的数小
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="list"></param>
        /// <param name="compare"></param>
        /// <returns></returns>
        template <typename T>
        static T Max(const std::vector<T>& list, const std::function<bool(const T&, const T&)>& compare) {
            if (list.count() <= 0) return T();
            T result = list[0];
            for (int i = 1; i < list.count(); ++i) {
                if (compare(result, list[i]))
                    result = list[i];
            }
            return result;
        }

        /// <summary>
        /// 比较函数参数一是当前最小的数，参数二是我们需要比较的数，返回true表示我们需要比较的数较小，返回false表示需要比较的数大
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="list"></param>
        /// <param name="compare"></param>
        /// <returns></returns>
        template <typename T>
        static T Min(const std::vector<T>& list, const std::function<bool(const T&, const T&)>& compare) {
            if (list.count() <= 0) return T();
            T result = list[0];
            for (int i = 1; i < list.count(); ++i) {
                if (compare(result, list[i])) {
                    result = list[i];
                }
            }
            return result;
        }

    };
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

         /// <summary>
        /// 获取当前程序运行的主目录
        /// </summary>
        /// <returns></returns>
        inline static std::wstring GetRootPath() {
            return rootPath;
        }

        static std::wstring StringToWString(const std::string& str) {
          /*  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.from_bytes(str);*/
            if (str.empty()) return std::wstring();
            int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(),
                (int)str.length(), NULL, 0);
            std::wstring wstr(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(),
                &wstr[0], size_needed);
            return wstr;
        }

        static std::string WStringToString(const std::wstring& wstr) {
         /*   std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
            return converter.to_bytes(wstr);*/
            if (wstr.empty()) return std::string();
            int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(),
                (int)wstr.length(), NULL, 0, NULL, NULL);
            std::string str(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(),
                &str[0], size_needed, NULL, NULL);
            return str;
        }

        static char* WStringToChar(const std::wstring& wstr) {
            const std::string& str = WStringToString(wstr);
            char* charPtr = new char[str.length() + 1]; //char内存需要手动管理释放
            strcpy_s(charPtr, str.length() + 1, str.c_str());
            return charPtr;
        }

        template<size_t N>
        static void StringWriterToBuffer(char(&buffer)[N], const std::string& str) {
            strncpy_s(buffer, str.c_str(), _TRUNCATE);
            buffer[N - 1] = '\0'; // 确保终止符
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
        static std::wstring rootPath;
        /// <summary>
        /// 初始化当前程序运行的主目录
        /// </summary>
        /// <returns></returns>
        static std::wstring InitPath() {
            wchar_t exePath[MAX_PATH];
            GetModuleFileNameW(NULL, exePath, MAX_PATH);
            // 从 exe 路径中提取出目录部分
            wchar_t* lastSlash = wcsrchr(exePath, L'\\');
            if (lastSlash) {
                *lastSlash = L'\0';
            }
            return  std::wstring(exePath) + L"\\";
        }
	};
}