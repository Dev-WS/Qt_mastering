#include "sysinfo.h"
#include <QtGlobal>

#include "sysinfowindowsimp1.h"

SysInfo& SysInfo::instance()
{

    static SysInfoWindowsImp1 singleton;
    return singleton;
}


SysInfo::SysInfo()
{



}


SysInfo::~SysInfo()
{


}
