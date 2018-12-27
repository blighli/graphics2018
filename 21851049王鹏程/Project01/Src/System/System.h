#pragma once
#include <stdio.h>
#include <time.h>
#include <string>

namespace apanoo {
	class System
	{
	private:
		System() {};
		static System *m_Instance;  // 单例

		class CGarbo  // 在内部类的析构中注销system单例
		{
		public:
			~CGarbo() {
				if (System::m_Instance)
				{
					delete System::m_Instance;
				}
			}
		};
		static CGarbo Garbo;

	public:
		static System * GetInstance();  // Instance

		std::string GetSystemTime();
	};
}