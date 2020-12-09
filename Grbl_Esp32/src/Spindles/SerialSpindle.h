//
// Created by Rye on 12/3/20.
//

#pragma once

#include "Spindle.h"
#include "../Serial.h"

namespace Spindles
{
// This is a spindle that just sends its set RPM to the serial console.
	class Serial : public Spindle {
	public:
		Serial() = default;

		Serial(const Serial&) = delete;
		Serial(Serial&&)      = delete;
		Serial& operator=(const Serial&) = delete;
		Serial& operator=(Serial&&) = delete;

		void         init() override;
		uint32_t     set_rpm(uint32_t rpm) override;
		void         set_state(SpindleState state, uint32_t rpm) override;
		SpindleState get_state() override;
		void         stop() override;
		void         config_message() override;

		virtual ~Serial() {}
	protected:
		uint32_t _last_sent;
	};
}
