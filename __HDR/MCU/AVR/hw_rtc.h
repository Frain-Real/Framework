#include "standard.h"

typedef struct{
    bool h24_12;
    u8 hours;
    u8 minutes;
    u8 seconds;
} time;

class RTC {
public:
    virtual ~RTC() {}

    // Get current time in a struct tm format
    virtual time get_time() = 0;

    // Set current time using a struct tm format
    virtual void set_time(time new_time) = 0;

    // Get current time in seconds since epoch
    virtual u32 get_time_in_seconds() = 0;

    // Get current timezone
    virtual i8 get_timezone() = 0;

    // Set current timezone
    virtual void set_timezone(i8 new_timezone) = 0;
    
    // Add other necessary methods for RTC module
};
