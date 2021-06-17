#include "SysInfo.h"
#include <QtGlobal>

#include "SysInfowindowsImpl.h"

SysInfo& SysInfo::instance()
{

    static SysInfoWindowsImpl singleton;
    return singleton;
}


SysInfo::SysInfo()
{



}


SysInfo::~SysInfo()
{


}
