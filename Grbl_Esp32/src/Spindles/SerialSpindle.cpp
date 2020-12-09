//
// Created by Rye on 12/3/20.
//

#include "SerialSpindle.h"

namespace Spindles
{
	void Serial::init()
	{
		is_reversable = false;
		use_delays = false;
		config_message();
	}

	uint32_t Serial::set_rpm(uint32_t rpm)
	{
		sys.spindle_speed = rpm;
		if (_last_sent != rpm)
		{
			if (rpm == 0)
			{
				grbl_send(CLIENT_SERIAL, "0");
			} else
			{
				grbl_send(CLIENT_SERIAL, "1");
			}
		}
		_last_sent = rpm;
		return rpm;
	}

	void Serial::set_state(SpindleState state, uint32_t rpm)
	{
		_current_state = state;
		if (state == SpindleState::Disable)
		{
			set_rpm(0);
		} else
		{
			set_rpm(rpm);
		}
	}

	SpindleState Serial::get_state()
	{
		return _current_state;
	}

	void Serial::stop()
	{
		set_rpm(0);
	}

	void Serial::config_message()
	{
		grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Serial spindle");
	}
}