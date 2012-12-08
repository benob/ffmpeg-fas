CFLAGS=-Wimplicit-function-declaration -I.
CXXFLAGS=-I. `pkg-config opencv --cflags`
LDFLAGS+=-lavcodec -lavformat -lavutil -lswscale 
OBJ+=ffmpeg_fas.o seek_indices.o

all: test/dump_frames test/dump_keyframes test/show_seek_table test/external_seek_test test/generate_seek_table test/opencv_example

test/dump_frames: test/dump_frames.o $(OBJ)
test/dump_keyframes: test/dump_keyframes.o $(OBJ)
test/show_seek_table: test/show_seek_table.o $(OBJ)
test/external_seek_test: test/external_seek_test.o $(OBJ)
test/generate_seek_table: test/generate_seek_table.o $(OBJ)

test/opencv_example: test/opencv_example.o $(OBJ)
	g++ -o $@ $^ $(LDFLAGS) `pkg-config opencv --libs`

clean:
	find . -name \*.o | xargs rm
