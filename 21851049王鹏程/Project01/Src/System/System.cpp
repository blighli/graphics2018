#include "System.h"

// 单例
apanoo::System* apanoo::System::m_Instance = NULL;
apanoo::System * apanoo::System::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new System;
	}
	return m_Instance;
}

std::string apanoo::System::GetSystemTime()
{
	time_t nowtime;
	struct tm *timeinfo;
	time(&nowtime);
	timeinfo = localtime(&nowtime);
	int year, month, day;  
	year = timeinfo->tm_year + 1900;  // 年
	month = timeinfo->tm_mon + 1;	  // 月
	day = timeinfo->tm_mday;		  // 日
	int hour, min, sec;
	hour = timeinfo->tm_hour;		  // 时
	min = timeinfo->tm_min;			  // 分
	sec = timeinfo->tm_sec;			  // 秒
	char time[100];
	sprintf(time, "%4d %02d %02d %02d %02d %02d", year, month, day, hour, min, sec);

	std::string str = time;
	return str;
}

