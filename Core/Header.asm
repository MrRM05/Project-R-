.definelabel ok_target, RAM_END
.definelabel ok_source, ok_target + 4
.definelabel ok_pointer, ok_source + 4
.definelabel ok_tkmspace, ok_pointer + 4
.definelabel ok_freespace, ok_tkmspace + 0x4000