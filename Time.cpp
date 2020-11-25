#include "Time.h"


Time :: Time (string dtime) {date_time = dtime;}
string Time :: get_time () {return date_time;}
void Time :: set_dtime (string dt) {date_time = dt;}
