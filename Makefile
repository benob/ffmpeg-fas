CFLAGS+=-Wimplicit-function-declaration -I.
LDFLAGS+=-lavcodec -lavformat -lavutil -lswscale
OBJ+=ffmpeg_fas.o seek_indices.o

all: test/dump_frames test/dump_keyframes test/show_seek_table test/external_seek_test test/generate_seek_table

test/dump_frames: test/dump_frames.o $(OBJ)
test/dump_keyframes: test/dump_keyframes.o $(OBJ)
test/show_seek_table: test/show_seek_table.o $(OBJ)
test/external_seek_test: test/external_seek_test.o $(OBJ)
test/generate_seek_table: test/generate_seek_table.o $(OBJ)

clean:
	find . -name \*.o | xargs rm
