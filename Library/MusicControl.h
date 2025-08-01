extern void MusSeqStart(uchar Group, ushort SeqID, uchar Interp);
extern void MusSeqStop(uchar Group, uchar Interp);
extern void MusSeqVolumeChange(uchar Group, uchar Volume, uchar Interp);
extern void MusSeqVolumeRecover(uchar Group, uchar Interp);
extern void MusSeqPitchChange(uchar Group, ushort Pitch, uchar Interp);
extern void MusSeqPitchRecover(uchar Group, uchar Interp);
extern void MusSeqTempoDirect(uchar Group, ushort Tempo, uchar Interp);
extern void MusSeqTempoAdd(uchar Group, ushort TempoAdd, uchar Interp);
extern void MusSeqTempoSub(uchar Group, ushort TempoSub, uchar Interp);
extern void MusSeqTempoPercent(uchar Group, ushort TempoPercent, uchar Interp);
extern void MusSeqTempoRecover(uchar Group, uchar Interp);
extern void MusSeqPreventNext(bool Disable);
extern void MusSeqSoundMode(uchar SoundMode);
extern short MusSeqGetCurrentID(uchar Group);
extern int MusSeqGetLoopCounter(uchar Group);
extern void MusSeqLoopImmediately(uchar Group);
extern void MusChanMute(uchar Group, uchar Channel, uchar Mute);
extern float MusChanGetVolume(uchar Group, uchar Channel);
extern void MusChanSetVolume(uchar Group, uchar Channel, float Volume);
extern float MusChanGetPitch(uchar Group, uchar Channel);
extern void MusChanSetPitch(uchar Group, uchar Channel, float Pitch);