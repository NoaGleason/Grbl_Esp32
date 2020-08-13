/*
    SerialSpindle.cpp

    This is a spindle that just sends its set RPM to the serial console.

    Part of Grbl_ESP32
    2020 -	Bart Dring

    Grbl is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Grbl.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "SpindleClass.h"

void SerialSpindle :: init() {
    is_reversable = false;
    use_delays = false;
    config_message();
}
uint32_t SerialSpindle :: set_rpm(uint32_t rpm) {
    sys.spindle_speed = rpm;
    print_uint32_base10(rpm);
    _last_sent = rpm;
    return rpm;
}
void SerialSpindle :: set_state(uint8_t state, uint32_t rpm) {

    if (state == SPINDLE_DISABLE) {
        set_rpm(0);
    } else {
        set_rpm(rpm);
    }
}
uint8_t SerialSpindle :: get_state() {
    if (_last_sent == 0) {
        return (SPINDLE_STATE_DISABLE);
    }
    return (SPINDLE_STATE_CW);
}
void SerialSpindle :: stop() {
    set_rpm(0);
}
void SerialSpindle :: config_message() {
    grbl_msg_sendf(CLIENT_SERIAL, MSG_LEVEL_INFO, "Serial spindle");
}
