#include "sysinfowindowsimp1.h"
#include <windows.h>

SysInfoWindowsImp1::SysInfoWindowsImp1() : SysInfo(), mCpuLoadLastValues()
{



}

void SysInfoWindowsImp1::init()
{
    mCpuLoadLastValues = cpuRawData();
}


double SysInfoWindowsImp1::memoryUsed()
{

    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);
    qulonglong memoryPhysicalUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;

    return (double)memoryPhysicalUsed / (double)memoryStatus.ullTotalPhys * 100.0;


}




QVector<qulonglong> SysInfoWindowsImp1::cpuRawData()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    QVector<qulonglong> rawData;

    rawData.append(convertFileTime(idleTime));
    rawData.append(convertFileTime(kernelTime));
    rawData.append(convertFileTime(userTime));


    return rawData;
}


qulonglong SysInfoWindowsImp1::convertFileTime(const FILETIME &filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;

    return largeInteger.QuadPart;
}


double SysInfoWindowsImp1::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    mCpuLoadLastValues = secondSample;


    qulonglong currentIdle = secondSample[0] - firstSample[0];
    qulonglong currentKernel = secondSample[1] - firstSample[1];
    qulonglong currentUser = secondSample[2] - firstSample[2];
    qulonglong currentSystem = currentKernel - currentUser;


    double percent = (currentSystem - currentIdle) * 100.0 / currentSystem;
    return qBound(0.0, percent, 100.0);
}
