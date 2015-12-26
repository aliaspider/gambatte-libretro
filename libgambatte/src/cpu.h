//
//   Copyright (C) 2007 by sinamas <sinamas at users.sourceforge.net>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License version 2 for more details.
//
//   You should have received a copy of the GNU General Public License
//   version 2 along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

#ifndef CPU_H
#define CPU_H

#include "gambatte.h"
#include "gambatte-memory.h"
#include "savestate.h"

namespace gambatte {

class CPU {
public:
	CPU();
	long runFor(unsigned long cycles);
	void setStatePtrs(SaveState &state);
	void saveState(SaveState &state);
	void loadState(SaveState const &state);
#if 0
	void loadSavedata() { mem_.loadSavedata(); }
	void saveSavedata() { mem_.saveSavedata(); }
#endif

#ifdef __LIBRETRO__
   void *savedata_ptr() { return mem_.savedata_ptr(); }
   unsigned savedata_size() { return mem_.savedata_size(); }
   void *rtcdata_ptr() { return mem_.rtcdata_ptr(); }
   unsigned rtcdata_size() { return mem_.rtcdata_size(); }
   void clearCheats() { mem_.clearCheats(); }
#endif

	void setVideoBuffer(video_pixel_t *videoBuf, std::ptrdiff_t pitch) {
		mem_.setVideoBuffer(videoBuf, pitch);
	}

	void setInputGetter(InputGetter *getInput) {
		mem_.setInputGetter(getInput);
	}

	void setSaveDir(std::string const &sdir) {
		mem_.setSaveDir(sdir);
	}

	std::string const saveBasePath() const {
		return mem_.saveBasePath();
	}

	int load(const void *romdata, unsigned int romsize, bool forceDmg, bool multicartCompat) {
		return mem_.loadROM(romdata, romsize, forceDmg, multicartCompat);
	}

#if 0
	bool loaded() const { return mem_.loaded(); }
#endif
	void setSoundBuffer(uint_least32_t *buf) { mem_.setSoundBuffer(buf); }
	std::size_t fillSoundBuffer() { return mem_.fillSoundBuffer(cycleCounter_); }
	bool isCgb() const { return mem_.isCgb(); }

	void setDmgPaletteColor(int palNum, int colorNum, unsigned long rgb32) {
		mem_.setDmgPaletteColor(palNum, colorNum, rgb32);
	}

	void setGameGenie(std::string const &codes) { mem_.setGameGenie(codes); }
	void setGameShark(std::string const &codes) { mem_.setGameShark(codes); }

	Memory mem_;
private:
	unsigned long cycleCounter_;
	unsigned short pc_;
	unsigned short sp;
	unsigned hf1, hf2, zf, cf;
	unsigned char a_, b, c, d, e, /*f,*/ h, l;
	bool skip_;

	void process(unsigned long cycles);
};

struct GB::Priv {
   CPU cpu;
   int stateNo;
   bool gbaCgbMode;

   Priv() : stateNo(1), gbaCgbMode(false) {}

   void on_load_succeeded(unsigned flags);
};

}

#endif
