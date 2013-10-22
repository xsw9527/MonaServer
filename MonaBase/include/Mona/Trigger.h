/* 
	Copyright 2013 Mona - mathieu.poux[a]gmail.com
 
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License received along this program for more
	details (or else see http://www.gnu.org/licenses/).

	This file is a part of Mona.
*/

#pragma once

#include "Mona/Mona.h"
#include "Mona/Time.h"
#include "Mona/Exceptions.h"

namespace Mona {


class Trigger {
public:
	Trigger();
	virtual ~Trigger();

	bool raise(Exception& ex);
	void start();
	void reset();
	void stop();
private:
	Mona::Time		_timeInit;
	Mona::Int8		_cycle;
	Mona::UInt8		_time;
	bool			_running;

};

inline void Trigger::stop() {
	_running=false;
}


} // namespace Mona