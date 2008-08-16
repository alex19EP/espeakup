/*
 *  espeakup - interface which allows speakup to use espeak
 *
 *  Copyright (C) 2008 William Hubbs
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "espeakup.h"

/* multipliers and offsets */
const int frequencyMultiplier = 11;
const int pitchMultiplier = 11;
const int rateMultiplier = 32;
const int rateOffset = 80;
const int volumeMultiplier = 11;

int SynthCallback(short *wav, int numsamples, espeak_EVENT *events)
{
	return 0;
}

espeak_ERROR set_frequency (struct synth_t *s)
{
	return (espeak_SetParameter(espeakRANGE, s->frequency * frequencyMultiplier, 0));
}

espeak_ERROR set_pitch (struct synth_t *s)
{
	return (espeak_SetParameter(espeakPITCH, s->pitch * pitchMultiplier, 0));
}

espeak_ERROR set_rate (struct synth_t *s)
{
	return (espeak_SetParameter(espeakRATE, s->rate * rateMultiplier + rateOffset, 0));
}

espeak_ERROR set_voice(struct synth_t *s)
{
	return (espeak_SetVoiceByName(s->voice));
}

espeak_ERROR set_volume (struct synth_t *s)
{
	return (espeak_SetParameter(espeakVOLUME, (s->volume+1) * volumeMultiplier, 0));
}

espeak_ERROR stop_speech(void)
{
	return (espeak_Cancel());
}

espeak_ERROR speak_text(struct synth_t *s)
{
	espeak_ERROR rc;

	rc = espeak_Synth(s->buf, s->len + 1, 0, POS_CHARACTER, 0, 0, NULL, NULL);
	return rc;
}